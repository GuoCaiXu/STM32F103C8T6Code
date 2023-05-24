# include "stm32f10x.h"
# include "./led/bsp_led.h" 
# include "./uart/bsp_uart.h"

//软件延时函数
void delay(uint32_t count){

	while(count --);
}

int main(void){

	uint8_t temp;
	
	DEBUG_UART_Config();
	LED_GPIO_Config();
	
	printf("点灯小程序!\n");
	
	while(1){

		temp = getchar();
		switch(temp){
			case '1':
			printf("接收的命令为：%c, 开启LED1 小灯!\n", temp);
			LED1_ON;
			break;
			case '2':
			printf("接收的命令为：%c, 开启LED1 关灯!\n", temp);
			LED1_OFF;
			break;
			case '3':
			printf("接收的命令为：%c, 开启LED2 开灯!\n", temp);
			LED2_ON;
			break;
			case '4':
			printf("接收的命令为：%c, 开启LED2 关灯!\n", temp);
			LED2_OFF;
			break;
			case '5':
			printf("接收的命令为：%c, 开启LED3 开灯!\n", temp);
			LED3_ON;
			break;
			case '6':
			printf("接收的命令为：%c, 开启LED3 关灯!\n", temp);
			LED3_OFF;
			break;
			case '7':
			printf("全部小灯关闭!\n");
			LED1_OFF;
			LED2_OFF;
			LED3_OFF;
			break;
			default:
			break;
		}
	}
}
