#ifndef __bsp_led_h
#define __bsp_led_h

#include "main.h"

// YH bsp led 
#define BSP_LED_R_GPIO              GPIOH
#define BSP_LED_R                   GPIO_PIN_10
#define BSP_LED_G_GPIO              GPIOH
#define BSP_LED_G                   GPIO_PIN_11
#define BSP_LED_B_GPIO              GPIOH
#define BSP_LED_B                   GPIO_PIN_12


bool bsp_led_init(void);
void bsp_led_on(uint16_t bsp_led_x);
void bsp_led_off(uint16_t bsp_led_x);
void bsp_led_toggle(uint16_t bsp_led_x);
void bsp_led_pwm_mode_init(void);
void bsp_led_pwm_set(uint16_t bsp_led_x,uint32_t duty);
void bsp_rgb_set(uint32_t r_duty,uint32_t g_duty,uint32_t b_duty);

#endif
