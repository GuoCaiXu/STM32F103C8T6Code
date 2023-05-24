# include "stm32f10x.h"
# include "./oled/OLED.h"
# include "./ad/bsp_ad.h"

uint16_t ADValue;
float Voltage;

/**
 *  @brief  延时函数
 *  @param  无
 *  @retval 无
*/
void delay(uint32_t z){

	while(z --);
}

/**
 *  @brief  主函数
 *  @param  无
 *  @retval 无
 */
int main(void){

	OLED_Init();
	AD_Init();

	OLED_ShowString(1, 1, "ADValue:");
	OLED_ShowString(2, 1, "Voltage:0.00V");

	while(1){

		ADValue = AD_GetValue();
		Voltage = (float)ADValue / 4095 * 3.3;

		OLED_ShowNum(1, 9, ADValue, 4);
		OLED_ShowNum(2, 9, Voltage, 1);
		OLED_ShowNum(2, 11, (uint16_t)(Voltage * 100) % 100, 2);
		delay(100);
	}
}
