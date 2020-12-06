#include "mylcd.h"

_lcd_dev lcddev;
//LCD�Ļ�����ɫ�ͱ���ɫ	   
uint32_t POINT_COLOR=0xFF000000;		//������ɫ
uint32_t BACK_COLOR =0xFFFFFFFF;  	//����ɫ 

void bsp_lcd_display_on(void)
{


}

void bsp_lcd_display_off(void)
{


}

uint32_t bsp_lcd_readpoint(uint16_t x,uint16_t y)
{
	if(x>=lcddev.width||y>=lcddev.height)return 0;	//�����˷�Χ,ֱ�ӷ���

	return bsp_ltdc_read_point(x,y);
}

void bsp_lcd_drawPoint(uint16_t x,uint16_t y)
{
	bsp_ltdc_draw_point(x,y,POINT_COLOR);
}

void bsp_lcd_fast_drawpoint(uint16_t x,uint16_t y,uint32_t color)
{	   
	if(lcdltdc.pwidth!=0)//�����RGB��
	{
		bsp_ltdc_draw_point(x,y,color);
		return;
	}	 
}	
 
void bsp_lcd_display_Dir(uint8_t dir)
{
    lcddev.dir=dir;         //����/����

    bsp_ltdc_display_dir(dir);
    lcddev.width=lcdltdc.width;
    lcddev.height=lcdltdc.height;
    return;
}

void bsp_lcd_clear(uint32_t color)
{
	bsp_ltdc_clear(color);
}  

void bsp_lcd_fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint32_t color)
{          
	bsp_ltdc_fill(sx,sy,ex,ey,color);
}  

void bsp_lcd_color_fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t *color)
{  
	bsp_ltdc_color_fill(sx,sy,ex,ey,color);
}  

//����
//x1,y1:�������
//x2,y2:�յ�����  
void bsp_lcd_drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	uint16_t t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //���õ������� 
	else if(delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//������� 
	{  
		bsp_lcd_drawPoint(uRow,uCol);//���� 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
} 

void bsp_lcd_init(void)
{
    bsp_ltdc_init();
    bsp_lcd_display_Dir(1);		//Ĭ��Ϊ����
	bsp_lcd_clear(LCD_COLOR_BLUE);
}

