# include "stm32f10x.h"
# include "./oled/OLED.h"
# include "./delay/bsp_delay.h"
# include "./exti/bsp_exti.h"

volatile int count = 0;

/**
 *  @brief  ������
 *  @param  ��
 *  @retval ��
 */
int main(void){

    OLED_Init();
	EXTI_KEY_Init();

    OLED_ShowString(1, 1, "Count:");
    while(1){
        OLED_ShowNum(1, 7, count, 5);
    }
}
