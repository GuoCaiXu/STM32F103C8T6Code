# include "./ad/bsp_ad.h"

/**
 *  @brief  AD GPIO ��ʼ��
 *  @param  ��
 *  @retval ��
 */
void AD_GPIO_Config(void){

    RCC_APB2PeriphClockCmd(ADCx_IN1_GPIO_CLK, ENABLE);

    GPIO_InitTypeDef    GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = ADCx_IN1_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(ADCx_IN1_PORT, &GPIO_InitStructure);
}

/**
 *  @brief  AD ģʽ��ʼ��
 *  @param  ��
 *  @retval ��
 */
void AD_Mode_Config(void){

    ADCx_APBxClock_FUN(ADCx_CLK, ENABLE);

    RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //6 ��Ƶ

    /*�����������ͨ��*/
    ADC_RegularChannelConfig(ADCx, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
    
    ADC_InitTypeDef     ADC_InitStructure;
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;      //�����ⲿ����Դ
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;        //ѡ������ת��ģʽ���ǵ���ת��ģʽ
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;      //ѡ��ɨ��ģʽ���Ƿ�ɨ��ģʽ
    ADC_InitStructure.ADC_NbrOfChannel = 1;     //ѡ���õ���ͨ����Ŀ
    ADC_Init(ADCx, &ADC_InitStructure);

    /*ʹ��ADC*/
    ADC_Cmd(ADCx, ENABLE);

    /*ADCУ׼*/
    ADC_ResetCalibration(ADCx);     //��λУ׼
    while(ADC_GetResetCalibrationStatus(ADCx) == SET);    //�ȴ���λУ׼���
    ADC_StartCalibration(ADCx);     //��ʼУ׼
    while(ADC_GetCalibrationStatus(ADCx) == SET);     //�ȴ�У׼���

    ADC_SoftwareStartConvCmd(ADCx, ENABLE);     //�������ת��
}

/**
 *  @brief  AD��ʼ��
 *  @param  ��
 *  @retval ��
 */
void AD_Init(void){

    AD_GPIO_Config();
    AD_Mode_Config();
}

/**
 *  @brief  ��ȡADC�Ľ��
 *  @param  ��
 *  @retval ��
 */
uint16_t AD_GetValue(void){

    while(ADC_GetFlagStatus(ADCx, ADC_FLAG_STRT) == RESET);        //��ȡ��־λ
    
    return ADC_GetConversionValue(ADCx);
}
