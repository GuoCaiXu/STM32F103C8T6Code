# include "stm32f10x.h"
# include "./oled/OLED.h"
# include "./delay/bsp_delay.h"
# include "./usart/bsp_usart.h"
# include "./led/bsp_led.h"
# include "./key/bsp_key.h"

/**
 *  @brief  主函数
 *  @param  无
 *  @retval 无
 */
int main(void){

	OLED_Init();
	USARTx_Init();
	LED_Init();
	KEY_Init();

	OLED_ShowString(1, 1, "TxPacket");
	OLED_ShowString(3, 1, "RxPacket");

	Serial_TxPacket[0] = 0x01;
	Serial_TxPacket[1] = 0x02;
	Serial_TxPacket[2] = 0x03;
	Serial_TxPacket[3] = 0x04;

	Serial_SendPacket();
	while(1){

		if (KEY_GeyFlag() == 0){

			Delay_ms(100);
			if (KEY_GeyFlag() == 0){
				Serial_TxPacket[0] ++;
				Serial_TxPacket[1] ++;
				Serial_TxPacket[2] ++;
				Serial_TxPacket[3] ++;

				Serial_SendPacket();

				OLED_ShowHexNum(2, 1, Serial_TxPacket[0], 2);
				OLED_ShowHexNum(2, 4, Serial_TxPacket[1], 2);
				OLED_ShowHexNum(2, 7, Serial_TxPacket[2], 2);
				OLED_ShowHexNum(2, 10, Serial_TxPacket[3], 2);
			}
		}

		if (USARTx_GetRxFlag() == 1){

			OLED_ShowHexNum(4, 1, Serial_RxPacket[0], 2);
			OLED_ShowHexNum(4, 4, Serial_RxPacket[1], 2);
			OLED_ShowHexNum(4, 7, Serial_RxPacket[2], 2);
			OLED_ShowHexNum(4, 10, Serial_RxPacket[3], 2);
		}

	}
}
