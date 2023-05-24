# include "./usart/bsp_usart.h"

/**
 *  @brief  串口 GPIO 初始化
 *  @param  无
 *  @retval 无
 */
static void USART_GPIO_Config(void){

    RCC_APB2PeriphClockCmd(USART_TX_CLK, ENABLE);

    GPIO_InitTypeDef    GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = USART_TX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USART_TX_PORT, &GPIO_InitStructure);
}

/**
 *  @brief  发送串口初始化
 *  @param  无
 *  @retval 无
 */
void Serial_Init(void){

    USART_GPIO_Config();

    RCC_APB2PeriphClockCmd(USARTx_CLK, ENABLE);

    USART_InitTypeDef   USART_InitStructure;
    USART_InitStructure.USART_BaudRate = USARTx_BAUDRATE;       //配置波特率
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;     //硬件流控制选择
    USART_InitStructure.USART_Mode = USART_Mode_Tx;      //串口模式
    USART_InitStructure.USART_Parity = USART_Parity_No;     //选择是否使用奇偶校验位
    USART_InitStructure.USART_StopBits = USART_StopBits_1;  //停止位长度
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;     //配置字长
    USART_Init(USARTx, &USART_InitStructure);

    /*使能串口*/
    USART_Cmd(USARTx, ENABLE);
}

/**
 *  @brief  发送 1 字节数据
 *  @param  无
 *  @retval 无
 */
void Serial_SendByte(uint8_t Byte){
    
    USART_SendData(USARTx, Byte);
    while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
}

/**
 *  @brief  发送数组
 *  @param  无
 *  @retval 无
 */
void Serial_SendArray(uint8_t *Array){

    uint16_t i, Length = sizeof(Array)/sizeof(uint8_t);
    for (i = 0; i < Length; i ++){
        Serial_SendByte(Array[i]);
    }
}

/**
 *  @brief  发送字符串
 *  @param  无
 *  @retval 无
 */
void Serial_SendString(char *String){

    uint8_t i;
    for (i = 0; String[i] != '\0'; i ++){
        Serial_SendByte(String[i]);
    }
}

/**
 *  @brief  发送次方函数
 *  @param  无
 *  @retval 无
 */
uint32_t Serial_Pow(uint32_t x, uint32_t y){

    uint32_t Result = 1;
    while(y --){
        Result *= x;
    }

    return Result;
}

/**
 *  @brief  发送一个数字
 *  @param  无
 *  @retval 无
 */
void Serial_SendNumber(uint32_t Number, uint8_t Lenght){

    uint8_t i;
    for(i = 0; i < Lenght; i ++){

        Serial_SendByte(Number/Serial_Pow(10, Lenght-i-1) % 10 + '0');
    }
}

/**
 *  @brief  重写printf中的fputc函数
 *  @param  无
 *  @retval 无
 */
int fputc(int ch, FILE *f){

    Serial_SendByte(ch);
    return ch;
}

/**
 *  @brief  封装sprintf
 *  @param  无
 *  @retval 无
 */
void Serial_Printf(char *format, ...){

    char String[100];
    va_list arg;
    va_start(arg, format);
    vsprintf(String, format, arg);
    va_end(arg);
    Serial_SendString(String);
}
