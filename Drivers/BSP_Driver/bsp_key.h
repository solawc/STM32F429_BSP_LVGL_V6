#ifndef __bsp_key_h
#define __bsp_key_h

#include "main.h"

#define BSP_KEY1_GPIO   GPIOA
#define BSP_KEY1        GPIO_PIN_0
#define BSP_KEY2_GPIO   GPIOC
#define BSP_KEY2        GPIO_PIN_13





bool bsp_key_init(void);
uint8_t bsp_key_read(uint16_t bsp_key_x);
uint8_t bsp_key_scanf(void);

void bsp_key1_thread_callback(void);
void bsp_key2_thread_callback(void);
#endif
