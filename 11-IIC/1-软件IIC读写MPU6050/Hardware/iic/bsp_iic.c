# include "./iic/bsp_iic.h"
# include "./delay/bsp_delay.h"

/**
 *  @brief  IIC ��ʼ��
 *  @param  ��
 *  @retval ��
 */
void IIC_Init(void){

    RCC_APB2PeriphClockCmd(IIC_SCL_CLK | IIC_SDA_CLK, ENABLE);

    GPIO_InitTypeDef    GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = IIC_SCL_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(IIC_SCL_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = IIC_SDA_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_Init(IIC_SDA_PORT, &GPIO_InitStructure);

    /*Ĭ�ϰ�SDA��SCL����*/
    IIC_W_SCL(1);
    IIC_W_SDA(1);
}

/**
 *  @brief  IIC ��ʼ�ź�
 *  @param  ��
 *  @retval ��
 */
void IIC_Start(void){

    IIC_W_SDA(1);
    IIC_W_SCL(1);
    IIC_W_SDA(0);
    IIC_W_SCL(0);
}

/**
 *  @brief  IIC ��ֹ����
 *  @param  ��
 *  @retval ��
 */
void IIC_Stop(void){

    IIC_W_SDA(0);
    IIC_W_SCL(1);
    IIC_W_SDA(1);
}

/**
 *  @brief  IIC ����һ���ֽ�
 *  @param  ��
 *  @retval ��
 */
void IIC_SendByte(uint8_t Byte){

    uint8_t i;

    for (i = 0; i < 8; i ++){

        IIC_W_SDA(Byte & (0x80 >> i));
        IIC_W_SCL(1);
        IIC_W_SCL(0);
    }
}

/**
 *  @brief  IIC ����һ���ֽ�
 *  @param  ��
 *  @retval Byte: ����һ���ֽ�
 */
uint8_t IIC_ReceiveByte(void){

    uint8_t Byte = 0x00, i;

    IIC_W_SDA(1);
    for (i = 0; i < 8; i ++){
        IIC_W_SCL(1);
        if (IIC_R_SDA == 1) Byte |= (0x80 >> i);
        IIC_W_SCL(0);
    }

    return Byte;
}

/**
 *  @brief  IIC ����Ӧ��
 *  @param  AckBit ����Ӧ���źſ���д������������
 *      @arg 1: ��Ӧ��
 *      @arg 0: Ӧ��
 *  @retval ��
 */
void IIC_SendACK(uint8_t AckBit){

    IIC_W_SDA(AckBit);
    IIC_W_SCL(1);
    IIC_W_SCL(0);
}

/**
 *  @brief  IIC ����Ӧ��
 *  @param  ��
 *  @retval AckBit: ����Ӧ��
 */
uint8_t IIC_ReceiveACK(void){

    uint8_t AckBit;

    IIC_W_SDA(1);
    IIC_W_SCL(1);
    AckBit = IIC_R_SDA;     // 1 ��Ӧ��     0 Ӧ��
    IIC_W_SCL(0);

    return AckBit;
}
