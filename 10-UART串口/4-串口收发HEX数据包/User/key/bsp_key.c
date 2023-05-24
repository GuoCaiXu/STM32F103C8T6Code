# include "./key/bsp_key.h"

/**
 *  @brief  KEY GPIO��ʼ��
 *  @param  ��
 *  @retval ��
 */
void KEY_Init(void){

    RCC_APB2PeriphClockCmd(KEY_CLK, ENABLE);

    GPIO_InitTypeDef    GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = KEY_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(KEY_PORT, &GPIO_InitStructure);
}

/**
 *  @brief  �ж�KEY �Ƿ���
 *  @param  ��
 *  @retval ��
 */
uint8_t KEY_GeyFlag(void){

    return GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN);
}
