# include "stm32f10x.h"
# include "./oled/OLED.h"
# include "./delay/bsp_delay.h"
# include "./key/bsp_key.h"
# include "./led/bsp_led.h"

/**
 *  @brief  主函数
 *  @param  无
 *  @retval 无
 */
int main(void){

	OLED_Init();
	LED_Init();
	KEY_Init();

	OLED_ShowString(1, 1, "Light up applet");
	OLED_ShowString(3, 1, "LED1 light OFF");
	OLED_ShowString(4, 1, "LED2 light OFF");

	while(1){

		uint8_t KeyNum = 0;
		KeyNum = Key_GetNum();
		if (KeyNum == SET){
			if (LED1_GetBit == RESET){
				OLED_ShowString(3, 1, "LED1 light ON ");
			}
			else{
				OLED_ShowString(3, 1, "LED1 light OFF");
			}
			LED1_TOGGLE;
		}
		else if (KeyNum == 2){
			if (LED2_GetBit == RESET){
				OLED_ShowString(4, 1, "LED2 light ON ");
			}
			else {
				OLED_ShowString(4, 1, "LED2 light OFF");
			}
			LED2_TOGGLE;
		}
	}
}
