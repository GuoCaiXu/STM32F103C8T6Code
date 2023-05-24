# include "stm32f10x.h"
# include "./oled/OLED.h"
# include "./delay/bsp_delay.h"
# include "./usart/bsp_usart.h"
# include "./led/bsp_led.h"
# include "./key/bsp_key.h"
# include <string.h>

/**
 *  @brief  主函数
 *  @param  无
 *  @retval 无
 */
int main(void){

	OLED_Init();
	USARTx_Init();
	LED_Init();

	OLED_ShowString(1, 1, "TxPacket");
	OLED_ShowString(3, 1, "RxPacket");

	while(1){

		if (USARTx_GetRxFlag() == 1){

			OLED_ShowString(4, 1, "                ");
			OLED_ShowString(4, 1, Serial_RxPacket);

			if (strcmp(Serial_RxPacket, "LED_ON") == 0){
				LED_ON;
				Serial_SendString("LED_ON_OK\r\n");
				OLED_ShowString(2, 1, "                ");
				OLED_ShowString(2, 1, "LED_ON_OK");
			}
			else if (strcmp(Serial_RxPacket, "LED_OFF") == 0){
				LED_OFF;
				Serial_SendString("LED_OFF_OK\r\n");
				OLED_ShowString(2, 1, "                ");
				OLED_ShowString(2, 1, "LED_OFF_OK");
			}
			else{
				Serial_SendString("ERROR_COMMAND\r\n");
				OLED_ShowString(2, 1, "                ");
				OLED_ShowString(2, 1, "ERROR_COMMAND");
			}
		}
	}
}
