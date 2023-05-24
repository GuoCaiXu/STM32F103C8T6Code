# include "stm32f10x.h"
# include "./led/bsp_led.h" 
# include "./uart/bsp_uart.h"

//�����ʱ����
void delay(uint32_t count){

	while(count --);
}

int main(void){

	uint8_t temp;
	
	DEBUG_UART_Config();
	LED_GPIO_Config();
	
	printf("���С����!\n");
	
	while(1){

		temp = getchar();
		switch(temp){
			case '1':
			printf("���յ�����Ϊ��%c, ����LED1 С��!\n", temp);
			LED1_ON;
			break;
			case '2':
			printf("���յ�����Ϊ��%c, ����LED1 �ص�!\n", temp);
			LED1_OFF;
			break;
			case '3':
			printf("���յ�����Ϊ��%c, ����LED2 ����!\n", temp);
			LED2_ON;
			break;
			case '4':
			printf("���յ�����Ϊ��%c, ����LED2 �ص�!\n", temp);
			LED2_OFF;
			break;
			case '5':
			printf("���յ�����Ϊ��%c, ����LED3 ����!\n", temp);
			LED3_ON;
			break;
			case '6':
			printf("���յ�����Ϊ��%c, ����LED3 �ص�!\n", temp);
			LED3_OFF;
			break;
			case '7':
			printf("ȫ��С�ƹر�!\n");
			LED1_OFF;
			LED2_OFF;
			LED3_OFF;
			break;
			default:
			break;
		}
	}
}
