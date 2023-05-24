# include "stm32f10x.h"
# include "./oled/OLED.h"
# include "./delay/bsp_delay.h"
# include "./usart/bsp_usart.h"

uint8_t temp_RxData;

/**
 *  @brief  ������
 *  @param  ��
 *  @retval ��
 */
int main(void){

	OLED_Init();
	USARTx_Init();

	OLED_ShowString(1, 1, "RxData:");

	while(1){

		if (USARTx_GetRxFlag() == 1){
			temp_RxData = USARTx_RxData();
			OLED_ShowHexNum(1, 8, temp_RxData, 2);
			printf("%hX", temp_RxData);
		}
	}
}
