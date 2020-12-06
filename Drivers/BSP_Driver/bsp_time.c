/***********************************************************************
*@Date: 2020-07-16 01:41:15
*@LastEditors: SOLA
*@LastEditTime: 2020-07-16 02:35:26
*@FilePath: \STM32F429_BSP\Drivers\BSP_Driver\bsp_time.c
***********************************************************************/
#include "bsp_time.h"

TIM_HandleTypeDef htim7; 
void bsp_time7_init(uint16_t arr,uint16_t psc)
{
    __HAL_RCC_TIM7_CLK_ENABLE();

    htim7.Instance=TIM7; 
    htim7.Init.Prescaler=psc; 
    htim7.Init.CounterMode=TIM_COUNTERMODE_UP; 
    htim7.Init.Period=arr; 
    htim7.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_Base_Init(&htim7);

    HAL_NVIC_SetPriority(TIM7_IRQn,1,3); 
    HAL_NVIC_EnableIRQ(TIM7_IRQn); 
    HAL_TIM_Base_Start_IT(&htim7);
}

void TIM7_IRQHandler(void)
{
    rt_interrupt_enter();
    if(__HAL_TIM_GET_FLAG(&htim7, TIM_FLAG_UPDATE) != RESET)
    {
        if(__HAL_TIM_GET_IT_SOURCE(&htim7, TIM_IT_UPDATE) !=RESET)
        {
            __HAL_TIM_CLEAR_IT(&htim7, TIM_IT_UPDATE);
            gizTimerMs();
        }
    }
    rt_interrupt_leave();
}

