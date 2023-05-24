# include "./uart/bsp_uart.h"

/*���Դ�������*/
void DEBUG_UART_Config(void){

    GPIO_InitTypeDef    GPIO_InitStructure;
    USART_InitTypeDef    USART_InitStructure;

    /*��һ������ʼ��GPIO*/
    /*��GPIO �˿ڵ�ʱ��*/
    DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);

    /*��UART Tx ��GPIO ����Ϊ���츴��ģʽ*/
    GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
    /*����ģʽ �������*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);

    /*��UART Rx ��GPIO ����Ϊ��������ģʽ*/
    GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
    /*��������ģʽ*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init( DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);


    /*�ڶ��������ô��ڵĳ�ʼ���ṹ��*/
    /*�򿪴�������ʱ��*/
    DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_CLK, ENABLE);
    
    // ���ô��ڵĹ�������
	// ���ò�����
	USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;
	// ���� �������ֳ�
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// ����ֹͣλ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// ����У��λ
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// ����Ӳ��������
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	// ���ù���ģʽ���շ�һ��
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// ��ɴ��ڵĳ�ʼ������
	USART_Init(DEBUG_USARTx, &USART_InitStructure);

    /*��������ʹ�ܴ���*/
    USART_Cmd(DEBUG_USARTx, ENABLE);	    
}

/*�ض���c �⺯��printf �����ڣ��ض�����ʹ��printf*/
int fputc(int ch, FILE *f){

    /*����һ���ֽ����ݵ�����*/
    USART_SendData(DEBUG_USARTx, (uint8_t) ch);

    /*�ȴ��������*/
    while(USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);

    return (ch);
}

/*�ض���c �⺯��scanf �����ڣ���д���ʹ��scanf �� getchar �Ⱥ���*/
int fgetc(FILE* f){

    /*�ȴ�������������*/
    while(USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_RXNE) == RESET);

    return (uint8_t)USART_ReceiveData(DEBUG_USARTx);
}
