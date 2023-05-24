# include "./ic/bsp_ic.h"

/**
 *  @brief  GPIO 初始化
 *  @param  无
 *  @retval 无
 */
void IC_GPIO_Config(void){

    RCC_APB2PeriphClockCmd(IC_TIM_CH1_GPIO_CLK, ENABLE);

    /*配置GPIO 结构体   上拉输入*/
    GPIO_InitTypeDef   GPIOInitStructure;

    GPIOInitStructure.GPIO_Pin = IC_TIM_CH1_PIN;
    GPIOInitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIOInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(IC_TIM_CH1_PORT, &GPIOInitStructure);

    GPIOInitStructure.GPIO_Pin = IC_TIM_CH2_PIN;
    GPIO_Init(IC_TIM_CH2_PORT, &GPIOInitStructure);
}

/**
 *  @brief  输入捕获模式配置
 *  @param  无
 *  @retval 无
 */
void IC_Mode_Config(void){

    IC_TIM_APBxClock_FUN(IC_TIM_CLK, ENABLE);

    /*--------------时基配置--------------*/
    TIM_InternalClockConfig(IC_TIM);        //选择内部时钟
    TIM_TimeBaseInitTypeDef     TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_Period = IC_Period;
    TIM_TimeBaseStructure.TIM_Prescaler = IC_Prescaler;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(IC_TIM, &TIM_TimeBaseStructure);


    /*--------------初始化输入捕获单元--------------*/
    /*通道1 直连输入    上升沿触发*/
    TIM_ICInitTypeDef       TIM_ICInitStructure;
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICFilter = 0xF;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_PWMIConfig(IC_TIM, &TIM_ICInitStructure);

    TIM_SelectInputTrigger(IC_TIM, TIM_TS_TI1FP1);   //配置TRGI的触发源为TI1FP1
    TIM_SelectSlaveMode(IC_TIM, TIM_SlaveMode_Reset);      //配置从模式

    TIM_Cmd(IC_TIM, ENABLE);      //使能定时器
}

/**
 *  @brief  输入捕获的初始化
 *  @param  无
 *  @retval 无
 */
void IC_Init(void){
    
    IC_GPIO_Config();
    IC_Mode_Config();
}

/**
 *  @brief  读取CCR(频率)
 *  @param  无
 *  @retval 无
 */
uint32_t IC_GetFreq(void){

    return 1000000 / (TIM_GetCapture1(IC_TIM)+1);
}

/**
 *  @brief  获取占空比
 *  @param  无
 *  @retval 无
 */
uint32_t IC_GetDuty(void){

    return (TIM_GetCapture2(IC_TIM)+1) * 100 / (TIM_GetCapture1(IC_TIM)+1);
}
