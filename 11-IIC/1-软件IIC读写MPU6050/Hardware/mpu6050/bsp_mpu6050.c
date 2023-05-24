# include "./mpu6050/bsp_mpu6050.h"
# include "./mpu6050/mpu6050_reg.h"
# include "./iic/bsp_iic.h"

/**
 *  @brief  写数据到寄存器
 *  @param  RegAddress: 写入的寄存器地址
 *  @param  Data: 写入的数据
 *  @retval 无
 */
void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data){

    IIC_Start();
    IIC_SendByte(MPU6050_W_ADDRESS);
    IIC_ReceiveACK();
    IIC_SendByte(RegAddress);
    IIC_ReceiveACK();
    IIC_SendByte(Data);
    IIC_ReceiveACK();
    IIC_Stop();
}

/**
 *  @brief  读指定地址的时序
 *  @param  无
 *  @retval 无
 */
uint8_t MPU6050_ReadReg(uint8_t RegAddress){
    
    uint8_t Data;

    IIC_Start();
    IIC_SendByte(MPU6050_W_ADDRESS);
    IIC_ReceiveACK();
    IIC_SendByte(RegAddress);
    IIC_ReceiveACK();
    
    IIC_Start();
    IIC_SendByte(MPU6050_R_ADDRESS);
    IIC_ReceiveACK();
    Data = IIC_ReceiveByte();
    IIC_SendACK(1);
    IIC_Stop();

    return Data;
}

/**
 *  @brief  MPU6050 初始化
 *  @param  无
 *  @retval 无
 */
void MPU6050_Init(void){

    IIC_Init();
    MPU6050_WriteReg(MPU6050_PWR_WGMT_1, 0x01);     // 选择陀螺仪时钟
    MPU6050_WriteReg(MPU6050_PWR_WGMT_2, 0x00);     // 6轴不需要待机 
    MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09);     // 10 分频 
    MPU6050_WriteReg(MPU6050_CONFIG, 0x06);
    MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);
    MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18);
}

/**
 *  @brief  查看 MPU6050 的ID 号
 *  @param  无
 *  @retval 返回 MPU6050 ID号
 */
uint8_t MPU6050_GetID(void){


    return MPU6050_ReadReg(MPU6050_WHO_AM_I);
}

/**
 *  @brief  MPU6050 获取数据
 *  @param  无
 *  @retval 无
 */
void MPU6050_GetData(MPU6050_SixAxisData *Data){

    uint8_t DataH, DataL;

    DataH = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);
    DataL = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
    Data->AccX = (DataH << 8) | DataL;

    DataH = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
    DataL = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
    Data->AccY = (DataH << 8) | DataL;

    DataH = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
    DataL = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
    Data->AccZ = (DataH << 8) | DataL;

    DataH = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
    DataL = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
    Data->GyroX = (DataH << 8) | DataL;

    DataH = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
    DataL = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
    Data->GyroY = (DataH << 8) | DataL;

    DataH = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
    DataL = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
    Data->GyroZ = (DataH << 8) | DataL;
}
