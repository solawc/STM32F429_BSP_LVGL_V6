/*
 * @Author: your name
 * @Date: 2020-08-28 04:57:38
 * @LastEditTime: 2020-08-28 06:32:02
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \STM32F429_BSP_NO_OS\Drivers\BSP_Driver\debug_usart.h
 */
#ifndef __debug_usart_h
#define __debug_usart_h

#include "main.h"
#include "stdio.h"


#define DEBUG_SWITCH                      1

                            
#if DEBUG_SWITCH
#define DEBUG_ERROR(fmt,arg...)        do{printf("<<-ERROR->> [%d]"fmt"\r\n",__LINE__, ##arg);}while(0)
#define DEBUG_PRINT(fmt,arg...)        do{printf("<<-DEBUG->> [%d]"fmt"\r\n",__LINE__, ##arg);}while(0)   
#else
#define DEBUG_ERROR(fmt,arg...)
#define DEBUG_PRINT(fmt,arg...)
#endif 




#define RINGBUF_LENGTH              10000
typedef struct 
{
    uint32_t head;
    uint32_t tail;
    uint8_t buff[RINGBUF_LENGTH];
    uint32_t len;
}ringbuff_t;


extern ringbuff_t debug_ringbuf;



void bsp_debug_usart_init(void);
void debug_dma_printf(uint8_t *str);
bool ringbuffer_init(void);
bool ringbuffer_write(uint8_t data);
bool ringbuffer_read(uint8_t *data);





#endif
