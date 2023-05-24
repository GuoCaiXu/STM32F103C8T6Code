# ifndef _BSP_MPU6050_H
# define _BSP_MPU6050_H

# include "stm32f10x.h"

/*MPU6050 写地址*/
# define MPU6050_W_ADDRESS        0xD0
/*MPU6050 读地址*/
# define MPU6050_R_ADDRESS        0xD1

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
