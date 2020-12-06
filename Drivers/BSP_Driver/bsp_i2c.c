#include "bsp_i2c.h"

I2C_HandleTypeDef hi2c1;

bool bsp_i2c1_init(void)
{
    GPIO_InitTypeDef GPIO_Init;
    HAL_StatusTypeDef I2C_INIT_STATUS = HAL_OK;

    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_I2C1_CLK_ENABLE();

    GPIO_Init.Alternate = GPIO_AF4_I2C1; 
    GPIO_Init.Mode = GPIO_MODE_AF_OD;
    GPIO_Init.Pull = GPIO_NOPULL;
    GPIO_Init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_Init.Pin = BSP_I2C1_SCL_PIN;
    HAL_GPIO_Init(BSP_I2C1_SCL_PORT, &GPIO_Init);

    GPIO_Init.Pin = BSP_I2C1_SDA_PIN;
    HAL_GPIO_Init(BSP_I2C1_SDA_PORT, &GPIO_Init);

    hi2c1.Instance = I2C1;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.ClockSpeed = 400000;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_16_9;
    hi2c1.Init.GeneralCallMode = DISABLE;
    hi2c1.Init.NoStretchMode = DISABLE;
    hi2c1.Init.OwnAddress1 = 0x00;
    hi2c1.Init.OwnAddress2 = 0x00;
    I2C_INIT_STATUS = HAL_I2C_Init(&hi2c1);
    if(I2C_INIT_STATUS != HAL_OK)
    {
        return false;
    }

    return true;
}

bool bsp_i2c1_disable(void)
{
    __HAL_RCC_I2C1_CLK_DISABLE();
    return true;
}

bool I2C_WriteByte(uint8_t salve_addr,uint8_t reg_addr,uint8_t *data)
{
    HAL_StatusTypeDef I2C_INIT_STATUS = HAL_OK;

    I2C_INIT_STATUS = HAL_I2C_Mem_Write(&hi2c1, salve_addr, reg_addr,I2C_MEMADD_SIZE_8BIT , data, 1, 100);

    if(I2C_INIT_STATUS != HAL_OK)
    {
        return false;
    }

    return true;
}

bool I2C_ReadBuffer(uint8_t salve_addr,uint8_t reg_addr,uint8_t *data,uint32_t num_of_byte)
{
    HAL_StatusTypeDef I2C_INIT_STATUS = HAL_OK;
    
    I2C_INIT_STATUS = HAL_I2C_Mem_Read(&hi2c1,salve_addr, reg_addr, I2C_MEMADD_SIZE_8BIT, data, num_of_byte, 1000);
    
    if(I2C_INIT_STATUS != HAL_OK)
    {
        return false;
    }

    return true;
}

