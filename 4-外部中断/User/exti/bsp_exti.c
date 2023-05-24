# include "./exti/bsp_exti.h"

/**
 *  @brief  GPIO初始化
 *  @param  无
 *  @retval 无
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
 *  @brief  EXTI初始化
 *  @param  无
 *  @retval 无
 */
static void EXTI_Config(void){

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

  GPIO_EXTILineConfig(KEY1_EXTI_GPIO_PORTSOURCE, KEY1_EXTI_GPIO_PINSOURCE);


  EXTI_InitTypeDef    EXTI_InitStructure;

  EXTI_InitStructure.EXTI_Line = KEY1_EXTI_LINE;          //启用的EXTI通道
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;               //使能EXTI
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;     //中断触发
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
  EXTI_Init(&EXTI_InitStructure);

  GPIO_EXTILineConfig(KEY2_EXTI_GPIO_PORTSOURCE, KEY2_EXTI_GPIO_PINSOURCE);
  EXTI_InitStructure.EXTI_Line = KEY2_EXTI_LINE;          //启用的EXTI通道
  EXTI_Init(&EXTI_InitStructure);
}

/**
 *  @brief  中断初始化
 *  @param  无
 *  @retval 无
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
 *  @brief  外部中断初始化
 *  @param  无
 *  @retval 无
 */
void EXTI_KEY_Init(void){

  GPIO_Config();
  EXTI_Config();
  NVIC_Config();
}
