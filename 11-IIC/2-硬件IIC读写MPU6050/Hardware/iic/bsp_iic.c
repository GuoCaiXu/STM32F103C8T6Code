# include "./iic/bsp_iic.h"
# include "./delay/bsp_delay.h"

/**
 *  @brief  IIC 初始化
 *  @param  无
 *  @retval 无
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

    /*默认把SDA和SCL拉高*/
    IIC_W_SCL(1);
    IIC_W_SDA(1);
}

/**
 *  @brief  IIC 起始信号
 *  @param  无
 *  @retval 无
 */
void IIC_Start(void){

    IIC_W_SDA(1);
    IIC_W_SCL(1);
    IIC_W_SDA(0);
    IIC_W_SCL(0);
}

/**
 *  @brief  IIC 终止条件
 *  @param  无
 *  @retval 无
 */
void IIC_Stop(void){

    IIC_W_SDA(0);
    IIC_W_SCL(1);
    IIC_W_SDA(1);
}

/**
 *  @brief  IIC 发送一个字节
 *  @param  无
 *  @retval 无
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
 *  @brief  IIC 接收一个字节
 *  @param  无
 *  @retval Byte: 返回一个字节
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
 *  @brief  IIC 发送应答
 *  @param  AckBit 发送应答信号可以写以下两个参数
 *      @arg 1: 非应答
 *      @arg 0: 应答
 *  @retval 无
 */
void IIC_SendACK(uint8_t AckBit){

    IIC_W_SDA(AckBit);
    IIC_W_SCL(1);
    IIC_W_SCL(0);
}

/**
 *  @brief  IIC 接收应答
 *  @param  无
 *  @retval AckBit: 返回应答
 */
uint8_t IIC_ReceiveACK(void){

    uint8_t AckBit;

    IIC_W_SDA(1);
    IIC_W_SCL(1);
    AckBit = IIC_R_SDA;     // 1 非应答     0 应答
    IIC_W_SCL(0);

    return AckBit;
}
