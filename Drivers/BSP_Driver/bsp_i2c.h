#ifndef __bsp_i2c_h
#define __bsp_i2c_h

#include "main.h"


#define BSP_I2C1_SCL_PIN        GPIO_PIN_6
#define BSP_I2C1_SCL_PORT       GPIOB
#define BSP_I2C1_SDA_PIN        GPIO_PIN_7
#define BSP_I2C1_SDA_PORT       GPIOB


bool bsp_i2c1_init(void);
bool I2C_WriteByte(uint8_t salve_addr,uint8_t reg_addr,uint8_t *data);
bool I2C_ReadBuffer(uint8_t salve_addr,uint8_t reg_addr,uint8_t *data,uint32_t num_of_byte);

#endif 
