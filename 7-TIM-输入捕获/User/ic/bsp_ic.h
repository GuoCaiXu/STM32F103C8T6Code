# ifndef _BSP_IC_H
# define _BSP_IC_H

# include "stm32f10x.h"

/*定时器定义*/
# define IC_TIM                TIM3
# define IC_TIM_APBxClock_FUN  RCC_APB1PeriphClockCmd
# define IC_TIM_CLK            RCC_APB1Periph_TIM3

/*配置ARR 和 PSC*/
# define IC_Period             (65536-1)    //ARR
# define IC_Prescaler          (72 - 1)    //PSC

/*输入捕获通道 1*/
# define IC_TIM_CH1_GPIO_CLK   RCC_APB2Periph_GPIOA
# define IC_TIM_CH1_PORT       GPIOA
# define IC_TIM_CH1_PIN        GPIO_Pin_6

/*------------------函数定义------------------*/
/*输入捕获初始化*/
void IC_Init(void);
/*读取CCR(频率)*/
uint32_t IC_GetFreq(void);

# endif /*_BSP_IC_H*/
