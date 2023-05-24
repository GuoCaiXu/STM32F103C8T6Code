# include "./led/bsp_led.h"     //�������ħ���������ͷ�ļ�������������

//��ʼ��GPIO ����
void LED_GPIO_Config(void){

    GPIO_InitTypeDef GPIO_InitStructure;

    //��һ�����������ʱ��
    RCC_APB2PeriphClockCmd(LED1_GPIO_CLK, ENABLE);   //ENABLE ��ʾ���ò���

    //�ڶ��������������ʼ���ṹ��
    GPIO_InitStructure.GPIO_Pin = LED1_GPIO_PIN;
    //����ģʽ���������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    //�����ٶȣ�50MHz
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    //�����������������ʼ�������������úõĽṹ���Աд���Ĵ�������
    GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);


    //�ڶ���led ��
    GPIO_InitStructure.GPIO_Pin = LED2_GPIO_PIN;
    GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = LED3_GPIO_PIN;
    GPIO_Init(LED3_GPIO_PORT, &GPIO_InitStructure);

    LED1_OFF;
    LED2_OFF;
    LED3_OFF;
}
