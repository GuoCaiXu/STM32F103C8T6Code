# include "./ad/bsp_ad.h"

 uint16_t AD_Value[4];

/**
 *  @brief  DMA ��ʼ��
 *  @param  AddrA: ����վ���ַ
 *  @param  AddrB: ������վ���ַ
 *  @param  Size:  �������
 *  @retval ��
 */
static void MyDMA_Init(void){

    DMAx_AHBPeriph_FUN(DMAx_CLK, ENABLE);

    DMA_InitTypeDef     DMA_InitStructure;
    /*����վ��� ��ʼ��ַ�����ݿ�ȣ��Ƿ�����*/
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    /*�洢��վ��� ��ʼ��ַ�����ݿ�ȣ��Ƿ�����*/
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)AD_Value;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;

    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;           //���䷽��     DMA_DIR_PeripheralSRC ����վ��ΪԴͷ(����վ�㵽������)  DMA_DIR_PeripheralDST ����վ��ΪĿ�ĵ�(������վ�㵽����վ��)
    DMA_InitStructure.DMA_BufferSize = 4;                        //��������С
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;              //�Ƿ�ʹ���Զ���װ     �Ƿ�ѭ��ģʽ
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                 //�Ƿ�ʹ���������
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;        //ѡ�����ȼ�
    DMA_Init(DMAx_CHANNELx, &DMA_InitStructure);

    DMA_Cmd(DMAx_CHANNELx, ENABLE);
}

/**
 *  @brief  AD GPIO ��ʼ��
 *  @param  ��
 *  @retval ��
 */
static void AD_GPIO_Config(void){

    RCC_APB2PeriphClockCmd(ADCx_IN1_GPIO_CLK, ENABLE);

    GPIO_InitTypeDef    GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = ADCx_IN1_PIN | ADCx_IN2_PIN | ADCx_IN3_PIN | ADCx_IN4_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(ADCx_IN1_PORT, &GPIO_InitStructure);
}

/**
 *  @brief  AD ��ʼ��
 *  @param  ��
 *  @retval ��
 */
void AD_Init(void){

    ADCx_APBxClock_FUN(ADCx_CLK, ENABLE);

    RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //6 ��Ƶ

    AD_GPIO_Config();

    ADC_RegularChannelConfig(ADCx, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADCx, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADCx, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADCx, ADC_Channel_3, 4, ADC_SampleTime_55Cycles5);
    
    ADC_InitTypeDef     ADC_InitStructure;
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;      //�����ⲿ����Դ
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;        //ѡ������ת��ģʽ���ǵ���ת��ģʽ
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;      //ѡ��ɨ��ģʽ���Ƿ�ɨ��ģʽ
    ADC_InitStructure.ADC_NbrOfChannel = 4;     //ѡ���õ���ͨ����Ŀ
    ADC_Init(ADCx, &ADC_InitStructure);
    
    MyDMA_Init();

    /*ADC DMA ʹ��*/
    ADC_DMACmd(ADCx, ENABLE);

    /*ʹ��ADC*/
    ADC_Cmd(ADCx, ENABLE);

    /*ADCУ׼*/
    ADC_ResetCalibration(ADCx);     //��λУ׼
    while(ADC_GetResetCalibrationStatus(ADCx) == SET);    //�ȴ���λУ׼���
    ADC_StartCalibration(ADCx);     //��ʼУ׼
    while(ADC_GetCalibrationStatus(ADCx) == SET);     //�ȴ�У׼���

    ADC_SoftwareStartConvCmd(ADCx, ENABLE);     //�������ת��
}
