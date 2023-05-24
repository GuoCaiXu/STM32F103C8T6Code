# include "./exti/bsp_exti.h"

/**
 *  @brief  GPIO��ʼ��
 *  @param  ��
 *  @retval ��
 */
static void GPIO_Config(void){

  RCC_APB2PeriphClockCmd(KEY_GPIO_CLK, ENABLE);

  GPIO_InitTypeDef    GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = KEY1_GPIO_PIN | KEY2_GPIO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(KEY_GPIO_PORT, &GPIO_InitStructure);
}

/**
 *  @brief  EXTI��ʼ��
 *  @param  ��
 *  @retval ��
 */
static void EXTI_Config(void){

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

  GPIO_EXTILineConfig(KEY1_EXTI_GPIO_PORTSOURCE, KEY1_EXTI_GPIO_PINSOURCE);


  EXTI_InitTypeDef    EXTI_InitStructure;

  EXTI_InitStructure.EXTI_Line = KEY1_EXTI_LINE;          //���õ�EXTIͨ��
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;               //ʹ��EXTI
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;     //�жϴ���
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
  EXTI_Init(&EXTI_InitStructure);

  GPIO_EXTILineConfig(KEY2_EXTI_GPIO_PORTSOURCE, KEY2_EXTI_GPIO_PINSOURCE);
  EXTI_InitStructure.EXTI_Line = KEY2_EXTI_LINE;          //���õ�EXTIͨ��
  EXTI_Init(&EXTI_InitStructure);
}

/**
 *  @brief  �жϳ�ʼ��
 *  @param  ��
 *  @retval ��
 */
static void NVIC_Config(void){

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

  NVIC_InitTypeDef    NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = KEY1_EXTI_IRQ;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = KEY2_EXTI_IRQ;
  NVIC_Init(&NVIC_InitStructure);
}

/**
 *  @brief  �ⲿ�жϳ�ʼ��
 *  @param  ��
 *  @retval ��
 */
void EXTI_KEY_Init(void){

  GPIO_Config();
  EXTI_Config();
  NVIC_Config();
}
