# include "./ad/bsp_ad.h"

 uint16_t AD_Value[4];

/**
 *  @brief  DMA 初始化
 *  @param  AddrA: 外设站点地址
 *  @param  AddrB: 储存器站点地址
 *  @param  Size:  传输次数
 *  @retval 无
 */
static void MyDMA_Init(void){

    DMAx_AHBPeriph_FUN(DMAx_CLK, ENABLE);

    DMA_InitTypeDef     DMA_InitStructure;
    /*外设站点的 起始地址，数据宽度，是否自增*/
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    /*存储器站点的 起始地址，数据宽度，是否自增*/
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)AD_Value;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;

    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;           //传输方向     DMA_DIR_PeripheralSRC 外设站点为源头(外设站点到储存器)  DMA_DIR_PeripheralDST 外设站点为目的地(储存器站点到外设站点)
    DMA_InitStructure.DMA_BufferSize = 4;                        //缓冲区大小
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;              //是否使用自动重装     是否循环模式
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                 //是否使用软件触发
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;        //选择优先级
    DMA_Init(DMAx_CHANNELx, &DMA_InitStructure);

    DMA_Cmd(DMAx_CHANNELx, ENABLE);
}

/**
 *  @brief  AD GPIO 初始化
 *  @param  无
 *  @retval 无
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
 *  @brief  AD 初始化
 *  @param  无
 *  @retval 无
 */
void AD_Init(void){

    ADCx_APBxClock_FUN(ADCx_CLK, ENABLE);

    RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //6 分频

    AD_GPIO_Config();

    ADC_RegularChannelConfig(ADCx, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADCx, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADCx, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADCx, ADC_Channel_3, 4, ADC_SampleTime_55Cycles5);
    
    ADC_InitTypeDef     ADC_InitStructure;
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;      //配置外部触发源
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;        //选择连续转化模式还是单次转化模式
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;      //选择扫描模式还是非扫描模式
    ADC_InitStructure.ADC_NbrOfChannel = 4;     //选择用到的通道数目
    ADC_Init(ADCx, &ADC_InitStructure);
    
    MyDMA_Init();

    /*ADC DMA 使能*/
    ADC_DMACmd(ADCx, ENABLE);

    /*使能ADC*/
    ADC_Cmd(ADCx, ENABLE);

    /*ADC校准*/
    ADC_ResetCalibration(ADCx);     //复位校准
    while(ADC_GetResetCalibrationStatus(ADCx) == SET);    //等待复位校准完成
    ADC_StartCalibration(ADCx);     //开始校准
    while(ADC_GetCalibrationStatus(ADCx) == SET);     //等待校准完成
}

/**
 *  @brief  获取ADC的结果
 *  @param  无
 *  @retval 无
 */
void AD_GetValue(void){

    DMA_Cmd(DMAx_CHANNELx, DISABLE);
    DMA_SetCurrDataCounter(DMAx_CHANNELx, 4);
    DMA_Cmd(DMAx_CHANNELx, ENABLE);

    ADC_SoftwareStartConvCmd(ADCx, ENABLE);     //软件触发转化

    while(DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);
    DMA_ClearFlag(DMA1_FLAG_TC1);
}
