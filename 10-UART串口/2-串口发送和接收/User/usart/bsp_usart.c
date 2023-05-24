# include "./usart/bsp_usart.h"
# include "./oled/oled.h"

uint8_t RxData;
uint8_t Serial_RxFlag;

/**
 *  @brief  ���� GPIO ��ʼ��
 *  @param  ��
 *  @retval ��
 */
static void USART_GPIO_Config(void){

    RCC_APB2PeriphClockCmd(USART_TX_CLK, ENABLE);

    GPIO_InitTypeDef    GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = USART_TX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USART_TX_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = USART_RX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(USART_RX_PORT, &GPIO_InitStructure);
}

static void USARTx_NVIC_Config(void){

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef    NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);
}

/**
 *  @brief  ���ʹ��ڳ�ʼ��
 *  @param  ��
 *  @retval ��
 */
void USARTx_Init(void){

    USART_GPIO_Config();

    RCC_APB2PeriphClockCmd(USARTx_CLK, ENABLE);

    USART_InitTypeDef   USART_InitStructure;
    USART_InitStructure.USART_BaudRate = USARTx_BAUDRATE;       //���ò�����
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;     //Ӳ��������ѡ��
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;      //����ģʽ
    USART_InitStructure.USART_Parity = USART_Parity_No;     //ѡ���Ƿ�ʹ����żУ��λ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;  //ֹͣλ����
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;     //�����ֳ�
    USART_Init(USARTx, &USART_InitStructure);

    USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);   //���ڽ����ж���Ҫ�õ�

    USARTx_NVIC_Config();

    /*ʹ�ܴ���*/
    USART_Cmd(USARTx, ENABLE);
}

/**
 *  @brief  ���� 1 �ֽ�����
 *  @param  ��
 *  @retval ��
 */
void Serial_SendByte(uint8_t Byte){
    
    USART_SendData(USARTx, Byte);
    while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
}

/**
 *  @brief  ��������
 *  @param  ��
 *  @retval ��
 */
void Serial_SendArray(uint8_t *Array){

    uint16_t i, Length = sizeof(Array)/sizeof(uint8_t);
    for (i = 0; i < Length; i ++){
        Serial_SendByte(Array[i]);
    }
}

/**
 *  @brief  �����ַ���
 *  @param  ��
 *  @retval ��
 */
void Serial_SendString(char *String){

    uint8_t i;
    for (i = 0; String[i] != '\0'; i ++){
        Serial_SendByte(String[i]);
    }
}

/**
 *  @brief  ���ʹη�����
 *  @param  ��
 *  @retval ��
 */
uint32_t Serial_Pow(uint32_t x, uint32_t y){

    uint32_t Result = 1;
    while(y --){
        Result *= x;
    }

    return Result;
}

/**
 *  @brief  ����һ������
 *  @param  ��
 *  @retval ��
 */
void Serial_SendNumber(uint32_t Number, uint8_t Lenght){

    uint8_t i;
    for(i = 0; i < Lenght; i ++){

        Serial_SendByte(Number/Serial_Pow(10, Lenght-i-1) % 10 + '0');
    }
}

/**
 *  @brief  ��дprintf�е�fputc����
 *  @param  ��
 *  @retval ��
 */
int fputc(int ch, FILE *f){

    Serial_SendByte(ch);
    return ch;
}

/**
 *  @brief  ��װsprintf
 *  @param  ��
 *  @retval ��
 */
void Serial_Printf(char *format, ...){

    char String[100];
    va_list arg;
    va_start(arg, format);
    vsprintf(String, format, arg);
    va_end(arg);
    Serial_SendString(String);
}

/**
 *  @brief  �������ݴ�ӡ��OLED��
 *  @param  ��
 *  @retval ��
 */
void Reception_Data_Show_OLED(void){

    uint8_t RxData;

    if (USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == SET){
        RxData = USART_ReceiveData(USARTx);
        OLED_ShowHexNum(1, 1, RxData, 2);
    }
}

/**
 *  @brief  ��ȡ���ڽ����жϱ�־λ
 *  @param  ��
 *  @retval ��
 */
uint8_t USARTx_GetRxFlag(void){

    if (Serial_RxFlag == 1){
        Serial_RxFlag = 0;
        return 1;
    }

    return 0;
}

/**
 *  @brief  �����жϽ��յ�������
 *  @param  ��
 *  @retval ��
 */
uint8_t USARTx_RxData(void){
    return RxData;
}

/**
 *  @brief  �жϺ���
 *  @param  ��
 *  @retval ��
 */
void USART1_IRQHandler(void){
  if(USART_GetITStatus(USARTx, USART_IT_RXNE) == SET){
    RxData =  USART_ReceiveData(USARTx);
    Serial_RxFlag = 1;
    USART_ClearITPendingBit(USARTx, USART_IT_RXNE);
  }
}
