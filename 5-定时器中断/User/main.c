# include "stm32f10x.h"
# include "./oled/OLED.h"
# include "./delay/bsp_delay.h"
# include "./timer/bsp_timer.h"

volatile uint32_t Count = 0;

/**
 *  @brief  主函数
 *  @param  无
 *  @retval 无
 */
int main(void){

    OLED_Init();
    Timer_Init();

    OLED_ShowString(1, 1, "Count:");
    OLED_ShowString(2, 1, "CNT:");
    OLED_ShowString(3, 1, "PSC:");

    while(1){
        OLED_ShowNum(1, 7, Count, 5);
        OLED_ShowNum(2, 7, TIM_GetCounter(TIMx), 5);
        OLED_ShowNum(3, 7, TIM_GetPrescaler(TIMx), 5);
    }
}
