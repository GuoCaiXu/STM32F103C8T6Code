# include "./ad/bsp_ad.h"

/**
 *  @brief  AD GPIO 初始化
 *  @param  无
 *  @retval 无
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
 *  @brief  AD 模式初始化
 *  @param  无
 *  @retval 无
 */
void AD_Mode_Config(void){

    ADCx_APBxClock_FUN(ADCx_CLK, ENABLE);

    RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //6 分频

    /*规则组的输入通道*/
    ADC_RegularChannelConfig(ADCx, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
    
    ADC_InitTypeDef     ADC_InitStructure;
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;      //配置外部触发源
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;        //选择连续转化模式还是单次转化模式
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;      //选择扫描模式还是非扫描模式
    ADC_InitStructure.ADC_NbrOfChannel = 1;     //选择用到的通道数目
    ADC_Init(ADCx, &ADC_InitStructure);

    /*使能ADC*/
    ADC_Cmd(ADCx, ENABLE);

    /*ADC校准*/
    ADC_ResetCalibration(ADCx);     //复位校准
    while(ADC_GetResetCalibrationStatus(ADCx) == SET);    //等待复位校准完成
    ADC_StartCalibration(ADCx);     //开始校准
    while(ADC_GetCalibrationStatus(ADCx) == SET);     //等待校准完成

    ADC_SoftwareStartConvCmd(ADCx, ENABLE);     //软件触发转化
}

/**
 *  @brief  AD初始化
 *  @param  无
 *  @retval 无
 */
void AD_Init(void){

    AD_GPIO_Config();
    AD_Mode_Config();
}

/**
 *  @brief  获取ADC的结果
 *  @param  无
 *  @retval 无
 */
uint16_t AD_GetValue(void){

    while(ADC_GetFlagStatus(ADCx, ADC_FLAG_STRT) == RESET);        //获取标志位
    
    return ADC_GetConversionValue(ADCx);
}
