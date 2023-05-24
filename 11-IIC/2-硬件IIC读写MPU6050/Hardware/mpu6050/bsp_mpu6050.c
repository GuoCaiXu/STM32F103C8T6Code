# include "./mpu6050/bsp_mpu6050.h"
# include "./mpu6050/mpu6050_reg.h"

/**
 *  @brief  �ȴ���־λ
 *  @param  RegAddress: д��ļĴ�����ַ
 *  @param  Data: д�������
 *  @retval ��
 */
static void MPU6050_WritEvent(uint32_t I2C_EVENT){

    uint32_t Timeout = 1000;

    while(I2C_CheckEvent(IICx, I2C_EVENT) != SUCCESS){

        Timeout --;
        if (Timeout == 0){
            return;
        }
    }

}

/**
 *  @brief  д���ݵ��Ĵ���
 *  @param  RegAddress: д��ļĴ�����ַ
 *  @param  Data: д�������
 *  @retval ��
 */
void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data){

    // IIC_Start();
    // IIC_SendByte(MPU6050_W_ADDRESS);
    // IIC_ReceiveACK();
    // IIC_SendByte(RegAddress);
    // IIC_ReceiveACK();
    // IIC_SendByte(Data);
    // IIC_ReceiveACK();
    // IIC_Stop();

    I2C_GenerateSTART(IICx, ENABLE);
    MPU6050_WritEvent(I2C_EVENT_MASTER_MODE_SELECT);

    I2C_Send7bitAddress(IICx, MPU6050_ADDRESS, I2C_Direction_Transmitter);
    MPU6050_WritEvent(I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);

    I2C_SendData(IICx, RegAddress);
    MPU6050_WritEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTING);

    I2C_SendData(IICx, Data);
    MPU6050_WritEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTED);

    I2C_GenerateSTOP(IICx, ENABLE);
}

/**
 *  @brief  ��ָ����ַ��ʱ��
 *  @param  ��
 *  @retval ��
 */
uint8_t MPU6050_ReadReg(uint8_t RegAddress){
    
    uint8_t Data;

    // IIC_Start();
    // IIC_SendByte(MPU6050_W_ADDRESS);
    // IIC_ReceiveACK();
    // IIC_SendByte(RegAddress);
    // IIC_ReceiveACK();
    
    // IIC_Start();
    // IIC_SendByte(MPU6050_R_ADDRESS);
    // IIC_ReceiveACK();
    // Data = IIC_ReceiveByte();
    // IIC_SendACK(1);
    // IIC_Stop();

    I2C_GenerateSTART(IICx, ENABLE);
    MPU6050_WritEvent(I2C_EVENT_MASTER_MODE_SELECT);

    I2C_Send7bitAddress(IICx, MPU6050_ADDRESS, I2C_Direction_Transmitter);
    MPU6050_WritEvent(I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);

    I2C_SendData(IICx, RegAddress);
    MPU6050_WritEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTING);

    I2C_GenerateSTART(IICx, ENABLE);
    MPU6050_WritEvent(I2C_EVENT_MASTER_MODE_SELECT);

    I2C_Send7bitAddress(IICx, MPU6050_ADDRESS, I2C_Direction_Receiver);
    MPU6050_WritEvent(I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED);

    I2C_AcknowledgeConfig(IICx, DISABLE);
    I2C_GenerateSTOP(IICx, ENABLE);

    MPU6050_WritEvent(I2C_EVENT_MASTER_BYTE_RECEIVED);

    Data = I2C_ReceiveData(IICx);

    I2C_AcknowledgeConfig(IICx, ENABLE);

    return Data;
}

/**
 *  @brief  MPU6050 ��ʼ��
 *  @param  ��
 *  @retval ��
 */
void MPU6050_Init(void){

    RCC_APB1PeriphClockCmd(IIC_CLK, ENABLE);
    RCC_APB2PeriphClockCmd(IIC_GPIO_CLK, ENABLE);

    GPIO_InitTypeDef    GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = IIC_SCL_GPIO_PIN | IIC_SDA_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(IIC_PORT, &GPIO_InitStructure);

    I2C_InitTypeDef     I2C_InitStructure;
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;      // IIC ģʽ
    I2C_InitStructure.I2C_ClockSpeed = 50000;       // IICʱ��Ƶ��
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;      // ռ�ձ�
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;             // Ӧ��λ����
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;   // �ӻ���Ӧ��λ�ĵ�ַ
    I2C_InitStructure.I2C_OwnAddress1 = 0x00;                                   // �ӻ������ַ
    I2C_Init(IICx, &I2C_InitStructure);

    I2C_Cmd(IICx, ENABLE);

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
