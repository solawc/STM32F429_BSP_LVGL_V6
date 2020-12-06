/*
 * @Author: your name
 * @Date: 2020-08-28 04:57:39
 * @LastEditTime: 2020-08-28 07:41:19
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * 
 * @FilePath: \STM32F429_BSP_NO_OS\Drivers\BSP_Driver\lcd\lcd\bsp_ltdc.h
 */
#ifndef __BSP_LTDC_H
#define __BSP_LTDC_H

#include "main.h"

extern uint32_t *ltdc_framebuf[2];

#define LCD_PIXEL_FORMAT_ARGB8888       0X00    
#define LCD_PIXEL_FORMAT_RGB888         0X01    
#define LCD_PIXEL_FORMAT_RGB565         0X02       
#define LCD_PIXEL_FORMAT_ARGB1555       0X03      
#define LCD_PIXEL_FORMAT_ARGB4444       0X04     
#define LCD_PIXEL_FORMAT_L8             0X05     
#define LCD_PIXEL_FORMAT_AL44           0X06     
#define LCD_PIXEL_FORMAT_AL88           0X07      

#define LCD_PIXFORMAT				LCD_PIXEL_FORMAT_RGB565	
//定义默认背景层颜色
#define LTDC_BACKLAYERCOLOR			0X00000000	
//LCD帧缓冲区首地址,这里定义在SDRAM里面.
#define LCD_FRAME_BUF_ADDR			0XD0000000  


typedef struct  
{							 
	uint32_t pwidth;		//LCD面板的宽度,固定参数,不随显示方向改变,如果为0,说明没有任何RGB屏接入
	uint32_t pheight;		//LCD面板的高度,固定参数,不随显示方向改变
	uint16_t hsw;			//水平同步宽度
	uint16_t vsw;			//垂直同步宽度
	uint16_t hbp;			//水平后廊
	uint16_t vbp;			//垂直后廊
	uint16_t hfp;			//水平前廊
	uint16_t vfp;			//垂直前廊 
	uint8_t activelayer;	//当前层编号:0/1	
	uint8_t dir;			//0,竖屏;1,横屏;
	uint16_t width;			//LCD宽度
	uint16_t height;		//LCD高度
	uint32_t pixsize;		//每个像素所占字节数
}_ltdc_dev; 
extern _ltdc_dev lcdltdc;          //管理ltdc相关参数



void bsp_ltdc_init(void);
uint8_t bsp_ltdc_clk_set(uint32_t pllsain,uint32_t pllsair,uint32_t pllsaidivr);
void bsp_ltdc_switch(uint8_t sw);
void bsp_ltdc_layer_switch(uint8_t layerx,uint8_t sw);
void bsp_ltdc_select_layer(uint8_t layerx);
void bsp_ltdc_display_dir(uint8_t dir);
void bsp_ltdc_clear(uint32_t color);
void bsp_ltdc_draw_point(uint16_t x,uint16_t y,uint32_t color);
uint32_t bsp_ltdc_read_point(uint16_t x,uint16_t y);
void bsp_ltdc_fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint32_t color);
void bsp_ltdc_color_fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t *color);
void bsp_ltdc_clear(uint32_t color);

void LTDC_Layer_Window_Config(uint8_t layerx,uint16_t sx,uint16_t sy,uint16_t width,uint16_t height);
void LTDC_Layer_Parameter_Config(uint8_t layerx,uint32_t bufaddr,uint8_t pixformat,uint8_t alpha,uint8_t alpha0,uint8_t bfac1,uint8_t bfac2,uint32_t bkcolor);
#endif
