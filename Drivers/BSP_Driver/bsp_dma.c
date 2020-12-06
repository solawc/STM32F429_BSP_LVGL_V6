/*
 * @Author: your name
 * @Date: 2020-08-28 05:07:39
 * @LastEditTime: 2020-08-28 05:46:54
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \STM32F429_BSP_NO_OS\Drivers\BSP_Driver\bsp_dma.c
 */
#include "bsp_dma.h"


DMA_HandleTypeDef hdma2_usart1;
uint8_t bsp_usart1_dma2_init(void)
{	
	HAL_StatusTypeDef STATUS = HAL_ERROR; 
	//__HAL_RCC_DMA2_CLK_ENABLE();
	__DMA2_CLK_ENABLE();
	
	hdma2_usart1.Instance = DMA2_Stream7;
	hdma2_usart1.Init.Channel = DMA_CHANNEL_4;
	hdma2_usart1.Init.Direction = DMA_MEMORY_TO_PERIPH; //内存到外设
	hdma2_usart1.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	hdma2_usart1.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
	hdma2_usart1.Init.MemBurst = DMA_MBURST_SINGLE;
	hdma2_usart1.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;//1BYTE = 8BIT
	hdma2_usart1.Init.MemInc = DMA_MINC_ENABLE; //使能内存自增
	hdma2_usart1.Init.Mode = DMA_NORMAL;	//正常模式
	hdma2_usart1.Init.PeriphBurst = DMA_PBURST_SINGLE;
	hdma2_usart1.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hdma2_usart1.Init.PeriphInc = DMA_PINC_DISABLE;
	hdma2_usart1.Init.Priority = DMA_PRIORITY_MEDIUM;
	//HAL_DMA_DeInit(&hdma2_usart1);
	STATUS = HAL_DMA_Init(&hdma2_usart1);

	if(STATUS == HAL_OK)
	{
		__HAL_LINKDMA(&huart1,hdmatx,hdma2_usart1);
	}
	else
	{
		DEBUG_ERROR("DMA init error");
	}

	return SUCCESS;
}


