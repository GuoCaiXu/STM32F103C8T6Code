# ifndef _BSP_MPU6050_H
# define _BSP_MPU6050_H

# include "stm32f10x.h"

# define IICx                    I2C2
# define IIC_CLK                 RCC_APB1Periph_I2C2                     

# define IIC_GPIO_CLK            RCC_APB2Periph_GPIOB
# define IIC_PORT                GPIOB
# define IIC_SCL_GPIO_PIN        GPIO_Pin_10
# define IIC_SDA_GPIO_PIN        GPIO_Pin_11

/*MPU6050 地址*/
# define MPU6050_ADDRESS        0xD0

/*MPU6050 六轴初始化数据*/
typedef struct{
    
    int16_t AccX;
    int16_t AccY;
    int16_t AccZ;
    int16_t GyroX;
    int16_t GyroY;
    int16_t GyroZ;
}MPU6050_SixAxisData;

void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data);
uint8_t MPU6050_ReadReg(uint8_t RegAddress);
void MPU6050_Init(void);
uint8_t MPU6050_GetID(void);
void MPU6050_GetData(MPU6050_SixAxisData *Data);

# endif /*_BSP_MPU6050*/
