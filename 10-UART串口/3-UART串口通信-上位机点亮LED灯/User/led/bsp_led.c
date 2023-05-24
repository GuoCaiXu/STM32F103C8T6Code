# include "./led/bsp_led.h"     //�������ħ���������ͷ�ļ�������������

//��ʼ��GPIO ����
void LED_GPIO_Config(void){

    GPIO_InitTypeDef GPIO_InitStruct;

    //��һ�����������ʱ��
    RCC_APB2PeriphClockCmd(LED_GPIO_CLK, ENABLE);   //ENABLE ��ʾ���ò���

    //�ڶ��������������ʼ���ṹ��
    GPIO_InitStruct.GPIO_Pin = LED1_GPIO_PIN;
    //����ģʽ���������
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    //�����ٶȣ�10MHz
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;

    //�����������������ʼ�������������úõĽṹ���Աд���Ĵ�������
    GPIO_Init(LED1_PORT, &GPIO_InitStruct);


    //�ڶ���led ��
     GPIO_InitStruct.GPIO_Pin = LED2_GPIO_PIN;
    GPIO_Init(LED2_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = LED3_GPIO_PIN;
    GPIO_Init(LED3_PORT, &GPIO_InitStruct);
}
