# include "./ic/bsp_ic.h"

/**
 *  @brief  GPIO ��ʼ��
 *  @param  ��
 *  @retval ��
 */
void IC_GPIO_Config(void){

    RCC_APB2PeriphClockCmd(IC_TIM_CH1_GPIO_CLK, ENABLE);

    /*����GPIO �ṹ��   ��������*/
    GPIO_InitTypeDef   GPIOInitStructure;

    GPIOInitStructure.GPIO_Pin = IC_TIM_CH1_PIN;
    GPIOInitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIOInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(IC_TIM_CH1_PORT, &GPIOInitStructure);

    GPIOInitStructure.GPIO_Pin = IC_TIM_CH2_PIN;
    GPIO_Init(IC_TIM_CH2_PORT, &GPIOInitStructure);
}

/**
 *  @brief  ���벶��ģʽ����
 *  @param  ��
 *  @retval ��
 */
void IC_Mode_Config(void){

    IC_TIM_APBxClock_FUN(IC_TIM_CLK, ENABLE);

    /*--------------ʱ������--------------*/
    TIM_InternalClockConfig(IC_TIM);        //ѡ���ڲ�ʱ��
    TIM_TimeBaseInitTypeDef     TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_Period = IC_Period;
    TIM_TimeBaseStructure.TIM_Prescaler = IC_Prescaler;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(IC_TIM, &TIM_TimeBaseStructure);


    /*--------------��ʼ�����벶��Ԫ--------------*/
    /*ͨ��1 ֱ������    �����ش���*/
    TIM_ICInitTypeDef       TIM_ICInitStructure;
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICFilter = 0xF;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_PWMIConfig(IC_TIM, &TIM_ICInitStructure);

    TIM_SelectInputTrigger(IC_TIM, TIM_TS_TI1FP1);   //����TRGI�Ĵ���ԴΪTI1FP1
    TIM_SelectSlaveMode(IC_TIM, TIM_SlaveMode_Reset);      //���ô�ģʽ

    TIM_Cmd(IC_TIM, ENABLE);      //ʹ�ܶ�ʱ��
}

/**
 *  @brief  ���벶��ĳ�ʼ��
 *  @param  ��
 *  @retval ��
 */
void IC_Init(void){
    
    IC_GPIO_Config();
    IC_Mode_Config();
}

/**
 *  @brief  ��ȡCCR(Ƶ��)
 *  @param  ��
 *  @retval ��
 */
uint32_t IC_GetFreq(void){

    return 1000000 / (TIM_GetCapture1(IC_TIM)+1);
}

/**
 *  @brief  ��ȡռ�ձ�
 *  @param  ��
 *  @retval ��
 */
uint32_t IC_GetDuty(void){

    return (TIM_GetCapture2(IC_TIM)+1) * 100 / (TIM_GetCapture1(IC_TIM)+1);
}
