# include "./timer/bsp_timer.h"

/**
 *  @brief  TIM 初始化
 *  @param  无
 *  @retval 无
 */
static void TIM_Config(void){

    TIMx_APBxPeriph_FUN(TIMx_CLK, ENABLE);

    TIM_InternalClockConfig(TIMx);

    TIM_TimeBaseInitTypeDef     TIM_TimeBaseStructure;

    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_Period = TIMx_ARR_Period;
    TIM_TimeBaseStructure.TIM_Prescaler = TIMx_PSC_Prescaler;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);

    TIM_ClearFlag(TIMx, TIM_FLAG_Update);
    TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE);
}

/**
 *  @brief  NVIC 初始化
 *  @param  无
 *  @retval 无
 */
static void NVIC_Config(void){

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef    NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIMx_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIMx, ENABLE);
}

/**
 *  @brief  定时器中断初始化
 *  @param  无
 *  @retval 无
 */
void Timer_Init(void){

    TIM_Config();
    NVIC_Config();
}
