# ifndef _BSP_GENERAL_H
# define _BSP_GENERAL_H

# include "stm32f10x.h"

/*��ʱ������*/
# define GENERAL_TIM                TIM2
# define GENERAL_TIM_APBxClock_FUN  RCC_APB1PeriphClockCmd
# define GENERAL_TIM_CLK            RCC_APB1Periph_TIM2

/*ARR �� PSC ����*/
# define GENERAL_TIM_Period         (100-1)   //ARR
# define GENERAL_TIM_Prescaler      (720-1)      //PSC

/*TIM3 ����Ƚ�ͨ�� 1*/
# define GENERAL_TIM_CH1_GPIO_CLK   RCC_APB2Periph_GPIOA
# define GENERAL_TIM_CH1_PORT       GPIOA
# define GENERAL_TIM_CH1_PIN        GPIO_Pin_0

/*--------------------------��������--------------------------*/
//TIM ��ʼ��
void GENERAL_TIM_Init(void);
//PWM ռ�ձȵ���
void PWM_SetCompare1(uint16_t Compare);
//�޸�PSC
void PWM_SetPrescaler(uint16_t Prescaler);

# endif /*_BSP_GENERAL_H*/
