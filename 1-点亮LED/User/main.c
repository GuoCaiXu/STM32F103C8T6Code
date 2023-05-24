# include "stm32f10x.h"
# include "./led/bsp_led.h" 

//Èí¼þÑÓÊ±º¯Êý
void delay(uint32_t count){

	while(count --);
}

int main(void){

	LED_GPIO_Config();
	
	while(1){

		LED1_ON;
		delay(0xfffff);
		LED2_ON;
		LED1_OFF;
		delay(0xfffff);
		LED3_ON;
		LED2_OFF;
		delay(0xfffff);
		LED1_ON;
		LED3_OFF;
		delay(0xfffff);

	}
}
