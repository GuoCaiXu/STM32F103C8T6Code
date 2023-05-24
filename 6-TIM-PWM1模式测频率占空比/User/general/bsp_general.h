# ifndef _BSP_GENERAL_H
# define _BSP_GENERAL_H

# include "stm32f10x.h"

/*定时器定义*/
# define GENERAL_TIM                TIM2
# define GENERAL_TIM_APBxClock_FUN  RCC_APB1PeriphClockCmd
# define GENERAL_TIM_CLK            RCC_APB1Periph_TIM2

/*ARR 和 PSC 配置*/
# define GENERAL_TIM_Period         (100-1)   //ARR
# define GENERAL_TIM_Prescaler      (720-1)      //PSC

/*TIM3 输出比较通道 1*/
# define GENERAL_TIM_CH1_GPIO_CLK   RCC_APB2Periph_GPIOA
# define GENERAL_TIM_CH1_PORT       GPIOA
# define GENERAL_TIM_CH1_PIN        GPIO_Pin_0

/*--------------------------函数定义--------------------------*/
//TIM 初始化
void GENERAL_TIM_Init(void);
//PWM 占空比调节
void PWM_SetCompare1(uint16_t Compare);
//修改PSC
void PWM_SetPrescaler(uint16_t Prescaler);

# endif /*_BSP_GENERAL_H*/
