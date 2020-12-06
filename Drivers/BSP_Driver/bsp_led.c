#include "bsp_led.h"

bool bsp_led_init(void)
{
    GPIO_InitTypeDef BSP_LED_GPIO_Init;

    __HAL_RCC_GPIOH_CLK_ENABLE();

    HAL_GPIO_WritePin(BSP_LED_R_GPIO,BSP_LED_R,GPIO_PIN_SET);
    HAL_GPIO_WritePin(BSP_LED_G_GPIO,BSP_LED_G,GPIO_PIN_SET);
    HAL_GPIO_WritePin(BSP_LED_B_GPIO,BSP_LED_B,GPIO_PIN_SET);

    BSP_LED_GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
    BSP_LED_GPIO_Init.Pull = GPIO_NOPULL;
    BSP_LED_GPIO_Init.Speed = GPIO_SPEED_FREQ_LOW;

    BSP_LED_GPIO_Init.Pin = BSP_LED_R;
    HAL_GPIO_Init(BSP_LED_R_GPIO, &BSP_LED_GPIO_Init);
    BSP_LED_GPIO_Init.Pin = BSP_LED_G;
    HAL_GPIO_Init(BSP_LED_G_GPIO, &BSP_LED_GPIO_Init);
    BSP_LED_GPIO_Init.Pin = BSP_LED_B;
    HAL_GPIO_Init(BSP_LED_B_GPIO, &BSP_LED_GPIO_Init);

    return true;
}


void bsp_led_on(uint16_t bsp_led_x)
{
    GPIO_TypeDef *LED_GPIO;

    switch (bsp_led_x)
    {
        case BSP_LED_R:LED_GPIO = BSP_LED_R_GPIO; break;
        case BSP_LED_G:LED_GPIO = BSP_LED_G_GPIO; break;
        case BSP_LED_B:LED_GPIO = BSP_LED_B_GPIO; break;
    }

    HAL_GPIO_WritePin(LED_GPIO,bsp_led_x,GPIO_PIN_RESET);
}

void bsp_led_off(uint16_t bsp_led_x)
{
    GPIO_TypeDef *LED_GPIO;

    switch (bsp_led_x)
    {
        case BSP_LED_R:LED_GPIO = BSP_LED_R_GPIO; break;
        case BSP_LED_G:LED_GPIO = BSP_LED_G_GPIO; break;
        case BSP_LED_B:LED_GPIO = BSP_LED_B_GPIO; break;
    }

    HAL_GPIO_WritePin(LED_GPIO,bsp_led_x,GPIO_PIN_SET);
}

void bsp_led_toggle(uint16_t bsp_led_x)
{
    GPIO_TypeDef *LED_GPIO;

    switch (bsp_led_x)
    {
        case BSP_LED_R:LED_GPIO = BSP_LED_R_GPIO; break;
        case BSP_LED_G:LED_GPIO = BSP_LED_G_GPIO; break;
        case BSP_LED_B:LED_GPIO = BSP_LED_B_GPIO; break;
    }

    HAL_GPIO_TogglePin(LED_GPIO,bsp_led_x);
}

TIM_HandleTypeDef htim5;
void bsp_led_pwm_mode_init(void)
{
    GPIO_InitTypeDef GPIO_Init;
    TIM_OC_InitTypeDef sConfig;
    
    __HAL_RCC_TIM5_CLK_ENABLE();

    GPIO_Init.Alternate = GPIO_AF2_TIM5;
    GPIO_Init.Mode = GPIO_MODE_AF_PP;
    GPIO_Init.Pull = GPIO_NOPULL;
    GPIO_Init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_Init.Pin = BSP_LED_R;
    HAL_GPIO_Init(BSP_LED_R_GPIO, &GPIO_Init);

    GPIO_Init.Pin = BSP_LED_G;
    HAL_GPIO_Init(BSP_LED_G_GPIO, &GPIO_Init);

    GPIO_Init.Pin = BSP_LED_B;
    HAL_GPIO_Init(BSP_LED_B_GPIO, &GPIO_Init);

     
    htim5.Instance = TIM5;
    htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim5.Init.Period = 255-1;
    htim5.Init.Prescaler = 90-1;
    HAL_TIM_PWM_Init(&htim5);


    sConfig.OCMode = TIM_OCMODE_PWM1;
    sConfig.OCPolarity = TIM_OCPOLARITY_LOW; //low leve active
    sConfig.Pulse = 100;
    HAL_TIM_PWM_ConfigChannel(&htim5,&sConfig,TIM_CHANNEL_1);
    HAL_TIM_PWM_ConfigChannel(&htim5,&sConfig,TIM_CHANNEL_2);
    HAL_TIM_PWM_ConfigChannel(&htim5,&sConfig,TIM_CHANNEL_3);

    HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_3);

}


void bsp_led_pwm_set(uint16_t bsp_led_x,uint32_t duty)
{
    switch (bsp_led_x)
    {
        case BSP_LED_R:  htim5.Instance->CCR1 = duty;   break;
        case BSP_LED_G:  htim5.Instance->CCR2 = duty;   break;
        case BSP_LED_B:  htim5.Instance->CCR3 = duty;   break;
    }
}

void bsp_rgb_set(uint32_t r_duty,uint32_t g_duty,uint32_t b_duty)
{
    bsp_led_pwm_set(BSP_LED_R,r_duty);
    bsp_led_pwm_set(BSP_LED_G,g_duty);
    bsp_led_pwm_set(BSP_LED_B,b_duty);
}
