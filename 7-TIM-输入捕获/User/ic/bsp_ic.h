# ifndef _BSP_IC_H
# define _BSP_IC_H

# include "stm32f10x.h"

/*��ʱ������*/
# define IC_TIM                TIM3
# define IC_TIM_APBxClock_FUN  RCC_APB1PeriphClockCmd
# define IC_TIM_CLK            RCC_APB1Periph_TIM3

/*����ARR �� PSC*/
# define IC_Period             (65536-1)    //ARR
# define IC_Prescaler          (72 - 1)    //PSC

/*���벶��ͨ�� 1*/
# define IC_TIM_CH1_GPIO_CLK   RCC_APB2Periph_GPIOA
# define IC_TIM_CH1_PORT       GPIOA
# define IC_TIM_CH1_PIN        GPIO_Pin_6

/*------------------��������------------------*/
/*���벶���ʼ��*/
void IC_Init(void);
/*��ȡCCR(Ƶ��)*/
uint32_t IC_GetFreq(void);

# endif /*_BSP_IC_H*/
