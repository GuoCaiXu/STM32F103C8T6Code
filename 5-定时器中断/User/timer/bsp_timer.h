# ifndef _BSP_TIMER_H
# define _BSP_TIMER_H

# include "stm32f10x.h"

# define TIMx                           TIM2
# define TIMx_APBxPeriph_FUN            RCC_APB1PeriphClockCmd
# define TIMx_CLK                       RCC_APB1Periph_TIM2

# define TIMx_ARR_Period                (10000-1)
# define TIMx_PSC_Prescaler             (7200-1)

# define TIMx_IRQn                      TIM2_IRQn
# define TIMx_IRQHandler                TIM2_IRQHandler

/*-------------------函数定义-------------------*/
void Timer_Init(void);      //定时器中断初始化

# endif /*_BSP_TIMER_H*/
