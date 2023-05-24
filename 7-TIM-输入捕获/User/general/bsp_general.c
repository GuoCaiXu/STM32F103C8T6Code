# include "./general/bsp_general.h"

/**
 *  @brief  ͨ��GPIO��ʼ��
 *  @param  ��
 *  @retval ��
 */
static void GENERAL_TIM_GPIO_Config(void){

    RCC_APB2PeriphClockCmd(GENERAL_TIM_CH1_GPIO_CLK, ENABLE);

    GPIO_InitTypeDef    GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GENERAL_TIM_CH1_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GENERAL_TIM_CH1_PORT, &GPIO_InitStructure);
}

/**
 *  @brief  TIM��ʱ��ģʽ����
 *  @param  ��
 *  @retval ��
 */
static void GENERAL_TIM_Mode_Config(void){

    GENERAL_TIM_APBxClock_FUN(GENERAL_TIM_CLK, ENABLE);

    /*ʱ������*/
    TIM_TimeBaseInitTypeDef     TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Period = GENERAL_TIM_Period;
    TIM_TimeBaseStructure.TIM_Prescaler = GENERAL_TIM_Prescaler;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(GENERAL_TIM, &TIM_TimeBaseStructure);

    /*����Ƚ�����*/
    TIM_OCInitTypeDef       TIM_OCInitStructure;
    TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;

    /*TIM ͨ��1����*/
    TIM_OCInitStructure.TIM_Pulse = 0;      //CCR1
    TIM_OC1Init(GENERAL_TIM, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(GENERAL_TIM, TIM_OCPreload_Enable);

    /*������ʱ��*/
    TIM_Cmd(GENERAL_TIM, ENABLE);
}

/**
 *  @brief  TIM ��ʼ��
 *  @param  ��
 *  @retval ��
 */
void GENERAL_TIM_Init(void){

    GENERAL_TIM_GPIO_Config();
    GENERAL_TIM_Mode_Config();
}

/**
 *  @brief  PWM ռ�ձȵ���
 *  @param  ��
 *  @retval ��
 */
void PWM_SetCompare1(uint16_t Compare){

    TIM_SetCompare1(GENERAL_TIM, Compare);
}

/**
 *  @brief  �޸�PSC
 *  @param  ��
 *  @retval ��
 */
void PWM_SetPrescaler(uint16_t Prescaler){

    TIM_PrescalerConfig(GENERAL_TIM, GENERAL_TIM_Prescaler, TIM_PSCReloadMode_Update);
}
