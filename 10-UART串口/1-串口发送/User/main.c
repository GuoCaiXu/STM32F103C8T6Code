# include "stm32f10x.h"
# include "./oled/OLED.h"
# include "./delay/bsp_delay.h"
# include "./usart/bsp_usart.h"

/**
 *  @brief  ������
 *  @param  ��
 *  @retval ��
 */
int main(void){

	OLED_Init();
	Serial_Init();

	// Serial_SendString("Hello Wrold\n");

	// Serial_SendNumber(12345, 5);
	// Serial_SendString("\n");

	// printf("Num = %d\r\n", 666);
	// printf("Hello Wrold\r\n");

	// char String[100];
	// sprintf(String, "Num = %d\r\n", 666);
	// Serial_SendString(String);

	// Serial_Printf("Num = %d\r\n", 666);
	printf("��� ����\r\n");

	while(1){

	}
}
