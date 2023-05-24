# include "./mpu6050/bsp_mpu6050.h"
# include "./mpu6050/mpu6050_reg.h"
# include "./iic/bsp_iic.h"

/**
 *  @brief  д���ݵ��Ĵ���
 *  @param  RegAddress: д��ļĴ�����ַ
 *  @param  Data: д�������
 *  @retval ��
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
 *  @brief  ��ָ����ַ��ʱ��
 *  @param  ��
 *  @retval ��
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
 *  @brief  MPU6050 ��ʼ��
 *  @param  ��
 *  @retval ��
 */
void MPU6050_Init(void){

    IIC_Init();
    MPU6050_WriteReg(MPU6050_PWR_WGMT_1, 0x01);     // ѡ��������ʱ��
    MPU6050_WriteReg(MPU6050_PWR_WGMT_2, 0x00);     // 6�᲻��Ҫ���� 
    MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09);     // 10 ��Ƶ 
    MPU6050_WriteReg(MPU6050_CONFIG, 0x06);
    MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);
    MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18);
}

/**
 *  @brief  �鿴 MPU6050 ��ID ��
 *  @param  ��
 *  @retval ���� MPU6050 ID��
 */
uint8_t MPU6050_GetID(void){


    return MPU6050_ReadReg(MPU6050_WHO_AM_I);
}

/**
 *  @brief  MPU6050 ��ȡ����
 *  @param  ��
 *  @retval ��
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
