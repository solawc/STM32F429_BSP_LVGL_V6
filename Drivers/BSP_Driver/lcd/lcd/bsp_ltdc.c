#include "bsp_ltdc.h"


_ltdc_dev lcdltdc;          //管理ltdc相关参数
LTDC_HandleTypeDef hltdc;   //LTDC句柄

uint32_t *ltdc_framebuf[2];

//根据不同的颜色格式,定义帧缓存数组
#if LCD_PIXFORMAT==LCD_PIXFORMAT_ARGB8888||LCD_PIXFORMAT==LCD_PIXFORMAT_RGB888
	uint32_t ltdc_lcd_framebuf[1280][800] __attribute__((at(LCD_FRAME_BUF_ADDR)));	//定义最大屏分辨率时,LCD所需的帧缓存数组大小
#else
	uint16_t ltdc_lcd_framebuf[1280][800] __attribute__((at(LCD_FRAME_BUF_ADDR)));	//定义最大屏分辨率时,LCD所需的帧缓存数组大小
#endif

static void bsp_ltdc_gpio_init(void)
{   
    GPIO_InitTypeDef GPIO_InitStruct;
  
  /* 使能LCD使用到的引脚时钟 */
                          //红色数据线
  LTDC_R0_GPIO_CLK_ENABLE();LTDC_R1_GPIO_CLK_ENABLE();LTDC_R2_GPIO_CLK_ENABLE();\
  LTDC_R3_GPIO_CLK_ENABLE();LTDC_R4_GPIO_CLK_ENABLE();LTDC_R5_GPIO_CLK_ENABLE();\
  LTDC_R6_GPIO_CLK_ENABLE();LTDC_R7_GPIO_CLK_ENABLE();LTDC_G0_GPIO_CLK_ENABLE();\
  LTDC_G1_GPIO_CLK_ENABLE();LTDC_G2_GPIO_CLK_ENABLE();LTDC_G3_GPIO_CLK_ENABLE();\
  LTDC_G3_GPIO_CLK_ENABLE();LTDC_G5_GPIO_CLK_ENABLE();LTDC_G6_GPIO_CLK_ENABLE();\
  LTDC_G7_GPIO_CLK_ENABLE();LTDC_B0_GPIO_CLK_ENABLE();LTDC_B1_GPIO_CLK_ENABLE();\
  LTDC_B2_GPIO_CLK_ENABLE();LTDC_B3_GPIO_CLK_ENABLE();LTDC_B4_GPIO_CLK_ENABLE();\
  LTDC_B5_GPIO_CLK_ENABLE();LTDC_B6_GPIO_CLK_ENABLE();LTDC_B7_GPIO_CLK_ENABLE();\
  LTDC_CLK_GPIO_CLK_ENABLE();LTDC_HSYNC_GPIO_CLK_ENABLE();LTDC_VSYNC_GPIO_CLK_ENABLE();\
  LTDC_DE_GPIO_CLK_ENABLE();LTDC_DISP_GPIO_CLK_ENABLE();LTDC_BL_GPIO_CLK_ENABLE();
/* GPIO配置 */

 /* 红色数据线 */                        
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Mode  = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  
  GPIO_InitStruct.Pin =   LTDC_R0_GPIO_PIN; 
  GPIO_InitStruct.Alternate = LTDC_R0_AF;
  HAL_GPIO_Init(LTDC_R0_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin =   LTDC_R1_GPIO_PIN; 
  GPIO_InitStruct.Alternate = LTDC_R1_AF;
  HAL_GPIO_Init(LTDC_R1_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin =   LTDC_R2_GPIO_PIN; 
  GPIO_InitStruct.Alternate = LTDC_R2_AF;
  HAL_GPIO_Init(LTDC_R2_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin =   LTDC_R3_GPIO_PIN; 
  GPIO_InitStruct.Alternate = LTDC_R3_AF;
  HAL_GPIO_Init(LTDC_R3_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin =   LTDC_R4_GPIO_PIN; 
  GPIO_InitStruct.Alternate = LTDC_R4_AF;
  HAL_GPIO_Init(LTDC_R4_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin =   LTDC_R5_GPIO_PIN; 
  GPIO_InitStruct.Alternate = LTDC_R5_AF;
  HAL_GPIO_Init(LTDC_R5_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin =   LTDC_R6_GPIO_PIN; 
  GPIO_InitStruct.Alternate = LTDC_R6_AF;
  HAL_GPIO_Init(LTDC_R6_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin =   LTDC_R7_GPIO_PIN; 
  GPIO_InitStruct.Alternate = LTDC_R7_AF;
  HAL_GPIO_Init(LTDC_R7_GPIO_PORT, &GPIO_InitStruct);
  
  //绿色数据线
  GPIO_InitStruct.Pin =   LTDC_G0_GPIO_PIN; 
  GPIO_InitStruct.Alternate = LTDC_G0_AF;
  HAL_GPIO_Init(LTDC_G0_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin =   LTDC_G1_GPIO_PIN; 
  GPIO_InitStruct.Alternate = LTDC_G1_AF;
  HAL_GPIO_Init(LTDC_G1_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin =   LTDC_G2_GPIO_PIN;
  GPIO_InitStruct.Alternate = LTDC_G2_AF;
  HAL_GPIO_Init(LTDC_G2_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin =   LTDC_G3_GPIO_PIN;
  GPIO_InitStruct.Alternate = LTDC_G3_AF;
  HAL_GPIO_Init(LTDC_G3_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin =   LTDC_G4_GPIO_PIN;
  GPIO_InitStruct.Alternate = LTDC_G4_AF;
  HAL_GPIO_Init(LTDC_G4_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin =   LTDC_G5_GPIO_PIN;
  GPIO_InitStruct.Alternate = LTDC_G5_AF;
  HAL_GPIO_Init(LTDC_G5_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin =   LTDC_G6_GPIO_PIN;
  GPIO_InitStruct.Alternate = LTDC_G6_AF;
  HAL_GPIO_Init(LTDC_G6_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin =   LTDC_G7_GPIO_PIN;
  GPIO_InitStruct.Alternate = LTDC_G7_AF;
  HAL_GPIO_Init(LTDC_G7_GPIO_PORT, &GPIO_InitStruct);
  
  //蓝色数据线
  GPIO_InitStruct.Pin =   LTDC_B0_GPIO_PIN;
  GPIO_InitStruct.Alternate = LTDC_B0_AF;
  HAL_GPIO_Init(LTDC_B0_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin =   LTDC_B1_GPIO_PIN;
  GPIO_InitStruct.Alternate = LTDC_B1_AF;
  HAL_GPIO_Init(LTDC_B1_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin =   LTDC_B2_GPIO_PIN;
  GPIO_InitStruct.Alternate = LTDC_B2_AF;
  HAL_GPIO_Init(LTDC_B2_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin =   LTDC_B3_GPIO_PIN;
  GPIO_InitStruct.Alternate = LTDC_B3_AF;
  HAL_GPIO_Init(LTDC_B3_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin =   LTDC_B4_GPIO_PIN;
  GPIO_InitStruct.Alternate = LTDC_B4_AF;
  HAL_GPIO_Init(LTDC_B4_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin =   LTDC_B5_GPIO_PIN;
  GPIO_InitStruct.Alternate = LTDC_B5_AF;
  HAL_GPIO_Init(LTDC_B5_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin =   LTDC_B6_GPIO_PIN;
  GPIO_InitStruct.Alternate = LTDC_B6_AF;
  HAL_GPIO_Init(LTDC_B6_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin =   LTDC_B7_GPIO_PIN;
  GPIO_InitStruct.Alternate = LTDC_B7_AF;
  HAL_GPIO_Init(LTDC_B7_GPIO_PORT, &GPIO_InitStruct);
  
  //控制信号线
  GPIO_InitStruct.Pin = LTDC_CLK_GPIO_PIN;
  GPIO_InitStruct.Alternate = LTDC_CLK_AF;
  HAL_GPIO_Init(LTDC_CLK_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin = LTDC_HSYNC_GPIO_PIN;
  GPIO_InitStruct.Alternate = LTDC_HSYNC_AF;
  HAL_GPIO_Init(LTDC_HSYNC_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin = LTDC_VSYNC_GPIO_PIN;
  GPIO_InitStruct.Alternate = LTDC_VSYNC_AF;
  HAL_GPIO_Init(LTDC_VSYNC_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin = LTDC_DE_GPIO_PIN;
  GPIO_InitStruct.Alternate = LTDC_DE_AF;
  HAL_GPIO_Init(LTDC_DE_GPIO_PORT, &GPIO_InitStruct);
  
  //背光BL 及液晶使能信号DISP
  HAL_GPIO_WritePin(LTDC_DISP_GPIO_PORT,LTDC_DISP_GPIO_PIN,GPIO_PIN_SET);
  HAL_GPIO_WritePin(LTDC_BL_GPIO_PORT,LTDC_BL_GPIO_PIN,GPIO_PIN_SET);
  GPIO_InitStruct.Pin = LTDC_DISP_GPIO_PIN;                             
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  
  HAL_GPIO_Init(LTDC_DISP_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin = LTDC_BL_GPIO_PIN; 
  HAL_GPIO_Init(LTDC_BL_GPIO_PORT, &GPIO_InitStruct);
}

static void bsp_ltdc_config(void)
{
    lcdltdc.pwidth=800;			    //面板宽度,单位:像素
    lcdltdc.pheight=480;		    //面板高度,单位:像素
    lcdltdc.hsw=1;				    //水平同步宽度
    lcdltdc.vsw=1;				    //垂直同步宽度
    lcdltdc.hbp=46;				    //水平后廊
    lcdltdc.vbp=23;				    //垂直后廊
    lcdltdc.hfp=22;			        //水平前廊
    lcdltdc.vfp=22;				    //垂直前廊
    //LTDC_Clk_Set(396,3,RCC_PLLSAIDIVR_4); //设置像素时钟 33M(如果开双显,需要降低DCLK到:18.75Mhz  300/4/4,才会比较好)
}


uint8_t bsp_ltdc_clk_set(uint32_t pllsain,uint32_t pllsair,uint32_t pllsaidivr)
{
    RCC_PeriphCLKInitTypeDef PeriphClkIniture;
	
	//LTDC输出像素时钟，需要根据自己所使用的LCD数据手册来配置！
    PeriphClkIniture.PeriphClockSelection=RCC_PERIPHCLK_LTDC;	//LTDC时钟 	
	PeriphClkIniture.PLLSAI.PLLSAIN=pllsain;    
	PeriphClkIniture.PLLSAI.PLLSAIR=pllsair;  
	PeriphClkIniture.PLLSAIDivR=pllsaidivr;
	if(HAL_RCCEx_PeriphCLKConfig(&PeriphClkIniture)==HAL_OK)    //配置像素时钟
    {
        return 0;   //成功
    }
    else return 1;  //失败 
}

void bsp_ltdc_init(void)
{
    __HAL_RCC_LTDC_CLK_ENABLE();
    __HAL_RCC_DMA2D_CLK_ENABLE();
    
    bsp_ltdc_gpio_init();                                   /* 初始化GPIO */
    bsp_ltdc_config();                                      /* 配置LTDC数据管理器 */
    if(bsp_ltdc_clk_set(192,5,RCC_PLLSAIDIVR_4))
    {
        DEBUG_PRINT("LTDC CLK SET FAILE!");
    }
    else 
    {
        DEBUG_PRINT("LTDC CLK SET SUCCEED!");
    }
                   /* 设置LTDC时钟 */

    lcddev.width=lcdltdc.pwidth;
	lcddev.height=lcdltdc.pheight;
    
#if LCD_PIXFORMAT==LCD_PIXFORMAT_ARGB8888||LCD_PIXFORMAT==LCD_PIXFORMAT_RGB888 
    ltdc_framebuf[0]=(uint32_t*)&ltdc_lcd_framebuf;
    lcdltdc.pixsize=4;				//每个像素占4个字节
#else 
    lcdltdc.pixsize=2;				//每个像素占2个字节
	ltdc_framebuf[0]=(uint32_t*)&ltdc_lcd_framebuf;
#endif 	


    hltdc.Instance = LTDC;  
    hltdc.Init.HorizontalSync =lcdltdc.hsw-1;
    hltdc.Init.VerticalSync = lcdltdc.vsw-1;
    hltdc.Init.AccumulatedHBP = lcdltdc.hsw+lcdltdc.hbp-1;
    hltdc.Init.AccumulatedVBP = lcdltdc.vsw+lcdltdc.vbp-1;
    hltdc.Init.AccumulatedActiveW = lcdltdc.hsw+lcdltdc.hbp+lcdltdc.pwidth-1;
    hltdc.Init.AccumulatedActiveH = lcdltdc.vsw+lcdltdc.vbp+lcdltdc.pheight-1;
    hltdc.Init.TotalWidth =lcdltdc.hsw+ lcdltdc.hbp+lcdltdc.pwidth + lcdltdc.hfp-1;
    hltdc.Init.TotalHeigh =lcdltdc.vsw+ lcdltdc.vbp+lcdltdc.pheight + lcdltdc.vfp-1;
    
    /* 初始化LCD的像素宽度和高度 */
    hltdc.LayerCfg->ImageWidth  = lcdltdc.pwidth;
    hltdc.LayerCfg->ImageHeight = lcdltdc.pheight;
    /* 设置LCD背景层的颜色，默认黑色 */
    hltdc.Init.Backcolor.Red = 0;
    hltdc.Init.Backcolor.Green = 0;
    hltdc.Init.Backcolor.Blue = 0;
    /* 极性配置 */
    hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;          /* 初始化行同步极性，低电平有效 */
    hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;          /* 初始化场同步极性，低电平有效 */
    hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;          /* 初始化数据有效极性，低电平有效 */   
    hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;         /* 初始化行像素时钟极性，同输入时钟 */
    HAL_LTDC_Init(&hltdc);

    //层配置
	LTDC_Layer_Parameter_Config(0,(uint32_t)ltdc_framebuf[0],LCD_PIXFORMAT,255,0,6,7,0X000000);//层参数配置
	LTDC_Layer_Window_Config(0,0,0,lcdltdc.pwidth,lcdltdc.pheight);	//层窗口配置,以LCD面板坐标系为基准,不要随便修改!

    bsp_ltdc_display_dir(1);
    bsp_ltdc_select_layer(0);
    bsp_ltdc_clear(0XFFFFFFFF);
}

void bsp_ltdc_switch(uint8_t sw)
{
    if(sw==1) __HAL_LTDC_ENABLE(&hltdc);
	else if(sw==0)__HAL_LTDC_DISABLE(&hltdc);
}

/*
开关指定层
layerx:层号,0,第一层; 1,第二层
sw:1 打开;0关闭
*/
void bsp_ltdc_layer_switch(uint8_t layerx,uint8_t sw)
{
    if(sw==1) __HAL_LTDC_LAYER_ENABLE(&hltdc,layerx);
	else if(sw==0) __HAL_LTDC_LAYER_DISABLE(&hltdc,layerx);
	__HAL_LTDC_RELOAD_CONFIG(&hltdc);
}

//选择层
//layerx:层号;0,第一层;1,第二层;
void bsp_ltdc_select_layer(uint8_t layerx)
{
	lcdltdc.activelayer=layerx;
}

//设置LCD显示方向
//dir:0,竖屏；1,横屏
void bsp_ltdc_display_dir(uint8_t dir)
{
    lcdltdc.dir=dir; 	//显示方向
	if(dir==0)			//竖屏
	{
		lcdltdc.width=lcdltdc.pheight;
		lcdltdc.height=lcdltdc.pwidth;	
	}else if(dir==1)	//横屏
	{
		lcdltdc.width=lcdltdc.pwidth;
		lcdltdc.height=lcdltdc.pheight;
	}
}

void bsp_ltdc_draw_point(uint16_t x,uint16_t y,uint32_t color)
{ 
#if LCD_PIXFORMAT==LCD_PIXFORMAT_ARGB8888||LCD_PIXFORMAT==LCD_PIXFORMAT_RGB888
	if(lcdltdc.dir)	//横屏
	{
        *(uint32_t*)((uint32_t)ltdc_framebuf[lcdltdc.activelayer]+lcdltdc.pixsize*(lcdltdc.pwidth*y+x))=color;
	}else 			//竖屏
	{
        *(uint32_t*)((uint32_t)ltdc_framebuf[lcdltdc.activelayer]+lcdltdc.pixsize*(lcdltdc.pwidth*(lcdltdc.pheight-x)+y))=color; 
	}
#else
	if(lcdltdc.dir)	//横屏
	{
        *(uint16_t*)((uint32_t)ltdc_framebuf[lcdltdc.activelayer]+lcdltdc.pixsize*(lcdltdc.pwidth*y+x))=color;
	}else 			//竖屏
	{
        *(uint16_t*)((uint32_t)ltdc_framebuf[lcdltdc.activelayer]+lcdltdc.pixsize*(lcdltdc.pwidth*(lcdltdc.pheight-x-1)+y))=color; 
	}
#endif
}

uint32_t bsp_ltdc_read_point(uint16_t x,uint16_t y)
{ 
#if LCD_PIXFORMAT==LCD_PIXFORMAT_ARGB8888||LCD_PIXFORMAT==LCD_PIXFORMAT_RGB888
	if(lcdltdc.dir)	//横屏
	{
		return *(uint32_t*)((uint32_t)ltdc_framebuf[lcdltdc.activelayer]+lcdltdc.pixsize*(lcdltdc.pwidth*y+x));
	}else 			//竖屏
	{
		return *(uint32_t*)((uint32_t)ltdc_framebuf[lcdltdc.activelayer]+lcdltdc.pixsize*(lcdltdc.pwidth*(lcdltdc.pheight-x)+y)); 
	}
#else
	if(lcdltdc.dir)	//横屏
	{
		return *(uint16_t*)((uint32_t)ltdc_framebuf[lcdltdc.activelayer]+lcdltdc.pixsize*(lcdltdc.pwidth*y+x));
	}else 			//竖屏
	{
		return *(uint16_t*)((uint32_t)ltdc_framebuf[lcdltdc.activelayer]+lcdltdc.pixsize*(lcdltdc.pwidth*(lcdltdc.pheight-x-1)+y)); 
	}
#endif 
}

void bsp_ltdc_fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint32_t color)
{ 
	uint32_t psx,psy,pex,pey;	//以LCD面板为基准的坐标系,不随横竖屏变化而变化
	uint32_t timeout=0; 
	uint16_t offline;
	uint32_t addr; 
	//坐标系转换
	if(lcdltdc.dir)	//横屏
	{
		psx=sx;psy=sy;
		pex=ex;pey=ey;
	}else			//竖屏
	{
		psx=sy;psy=lcdltdc.pheight-ex-1;
		pex=ey;pey=lcdltdc.pheight-sx-1;
	}
	offline=lcdltdc.pwidth-(pex-psx+1);
	addr=((uint32_t)ltdc_framebuf[lcdltdc.activelayer]+lcdltdc.pixsize*(lcdltdc.pwidth*psy+psx));
	__HAL_RCC_DMA2D_CLK_ENABLE();	//使能DM2D时钟
	DMA2D->CR&=~(DMA2D_CR_START);	//先停止DMA2D
	DMA2D->CR=DMA2D_R2M;			//寄存器到存储器模式
	DMA2D->OPFCCR=LCD_PIXFORMAT;	//设置颜色格式
	DMA2D->OOR=offline;				//设置行偏移 

	DMA2D->OMAR=addr;				//输出存储器地址
	DMA2D->NLR=(pey-psy+1)|((pex-psx+1)<<16);	//设定行数寄存器
	DMA2D->OCOLR=color;						//设定输出颜色寄存器 
	DMA2D->CR|=DMA2D_CR_START;				//启动DMA2D
	while((DMA2D->ISR&(DMA2D_FLAG_TC))==0)	//等待传输完成
	{
		timeout++;
		if(timeout>0X1FFFFF)break;	//超时退出
	} 
	DMA2D->IFCR|=DMA2D_FLAG_TC;		//清除传输完成标志 		
}

void bsp_ltdc_color_fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t *color)
{
	uint32_t psx,psy,pex,pey;	//以LCD面板为基准的坐标系,不随横竖屏变化而变化
	uint32_t timeout=0; 
	uint16_t offline;
	uint32_t addr; 
	//坐标系转换
	if(lcdltdc.dir)	//横屏
	{
		psx=sx;psy=sy;
		pex=ex;pey=ey;
	}else			//竖屏
	{
		psx=sy;psy=lcdltdc.pheight-ex-1;
		pex=ey;pey=lcdltdc.pheight-sx-1;
	}
	offline=lcdltdc.pwidth-(pex-psx+1);
	addr=((uint32_t)ltdc_framebuf[lcdltdc.activelayer]+lcdltdc.pixsize*(lcdltdc.pwidth*psy+psx));
	__HAL_RCC_DMA2D_CLK_ENABLE();	//使能DM2D时钟
	DMA2D->CR&=~(DMA2D_CR_START);	//先停止DMA2D
	DMA2D->CR=DMA2D_M2M;			//存储器到存储器模式
	DMA2D->FGPFCCR=LCD_PIXFORMAT;	//设置颜色格式
	DMA2D->FGOR=0;					//前景层行偏移为0
	DMA2D->OOR=offline;				//设置行偏移 

	DMA2D->FGMAR=(uint32_t)color;		//源地址
	DMA2D->OMAR=addr;				//输出存储器地址
	DMA2D->NLR=(pey-psy+1)|((pex-psx+1)<<16);	//设定行数寄存器 
	DMA2D->CR|=DMA2D_CR_START;					//启动DMA2D
	while((DMA2D->ISR&(DMA2D_FLAG_TC))==0)		//等待传输完成
	{
		timeout++;
		if(timeout>0X1FFFFF)break;	//超时退出
	} 
	DMA2D->IFCR|=DMA2D_FLAG_TC;				//清除传输完成标志  	
}  

void bsp_ltdc_clear(uint32_t color)
{
	bsp_ltdc_fill(0,0,lcdltdc.width-1,lcdltdc.height-1,color);
}

//LTDC,层颜窗口设置,窗口以LCD面板坐标系为基准
//注意:此函数必须在LTDC_Layer_Parameter_Config之后再设置.
//layerx:层值,0/1.
//sx,sy:起始坐标
//width,height:宽度和高度
void LTDC_Layer_Window_Config(uint8_t layerx,uint16_t sx,uint16_t sy,uint16_t width,uint16_t height)
{
    HAL_LTDC_SetWindowPosition(&hltdc,sx,sy,layerx);  //设置窗口的位置
    HAL_LTDC_SetWindowSize(&hltdc,width,height,layerx);//设置窗口大小    
}

//LTDC,基本参数设置.
//注意:此函数,必须在LTDC_Layer_Window_Config之前设置.
//layerx:层值,0/1.
//bufaddr:层颜色帧缓存起始地址
//pixformat:颜色格式.0,ARGB8888;1,RGB888;2,RGB565;3,ARGB1555;4,ARGB4444;5,L8;6;AL44;7;AL88
//alpha:层颜色Alpha值,0,全透明;255,不透明
//alpha0:默认颜色Alpha值,0,全透明;255,不透明
//bfac1:混合系数1,4(100),恒定的Alpha;6(101),像素Alpha*恒定Alpha
//bfac2:混合系数2,5(101),恒定的Alpha;7(111),像素Alpha*恒定Alpha
//bkcolor:层默认颜色,32位,低24位有效,RGB888格式
//返回值:无
void LTDC_Layer_Parameter_Config(uint8_t layerx,uint32_t bufaddr,uint8_t pixformat,uint8_t alpha,uint8_t alpha0,uint8_t bfac1,uint8_t bfac2,uint32_t bkcolor)
{
	LTDC_LayerCfgTypeDef pLayerCfg;
	
	pLayerCfg.WindowX0=0;                       //窗口起始X坐标
	pLayerCfg.WindowY0=0;                       //窗口起始Y坐标
	pLayerCfg.WindowX1=lcdltdc.pwidth;          //窗口终止X坐标
	pLayerCfg.WindowY1=lcdltdc.pheight;         //窗口终止Y坐标
	pLayerCfg.PixelFormat=pixformat;		    //像素格式
	pLayerCfg.Alpha=alpha;				        //Alpha值设置，0~255,255为完全不透明
	pLayerCfg.Alpha0=alpha0;			        //默认Alpha值
	pLayerCfg.BlendingFactor1=(uint32_t)bfac1<<8;    //设置层混合系数
	pLayerCfg.BlendingFactor2=(uint32_t)bfac2<<8;	//设置层混合系数
	pLayerCfg.FBStartAdress=bufaddr;	        //设置层颜色帧缓存起始地址
	pLayerCfg.ImageWidth=lcdltdc.pwidth;        //设置颜色帧缓冲区的宽度    
	pLayerCfg.ImageHeight=lcdltdc.pheight;      //设置颜色帧缓冲区的高度
	pLayerCfg.Backcolor.Red=(uint8_t)(bkcolor&0X00FF0000)>>16;   //背景颜色红色部分
	pLayerCfg.Backcolor.Green=(uint8_t)(bkcolor&0X0000FF00)>>8;  //背景颜色绿色部分
	pLayerCfg.Backcolor.Blue=(uint8_t)bkcolor&0X000000FF;        //背景颜色蓝色部分
	HAL_LTDC_ConfigLayer(&hltdc,&pLayerCfg,layerx);   //设置所选中的层
}  




