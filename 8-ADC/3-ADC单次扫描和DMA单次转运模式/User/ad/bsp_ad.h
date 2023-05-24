# ifndef _BSP_AD_H
# define _BSP_AD_H

# include "stm32f10x.h"

/*DMA �궨��*/
# define DMAx                       DMA1
# define DMAx_AHBPeriph_FUN         RCC_AHBPeriphClockCmd
# define DMAx_CLK                   RCC_AHBPeriph_DMA1

# define DMAx_CHANNELx              DMA1_Channel1

/*ADC �궨��*/
# define ADCx                       ADC1
# define ADCx_APBxClock_FUN         RCC_APB2PeriphClockCmd
# define ADCx_CLK                   RCC_APB2Periph_ADC1

/*ADC ͨ�� 1*/
# define ADCx_IN1_GPIO_CLK         RCC_APB2Periph_GPIOA
# define ADCx_IN1_PORT             GPIOA
# define ADCx_IN1_PIN              GPIO_Pin_0

/*ADC ͨ�� 2*/
# define ADCx_IN2_GPIO_CLK         RCC_APB2Periph_GPIOA
# define ADCx_IN2_PORT             GPIOA
# define ADCx_IN2_PIN              GPIO_Pin_1

/*ADC ͨ�� 3*/
# define ADCx_IN3_GPIO_CLK         RCC_APB2Periph_GPIOA
# define ADCx_IN3_PORT             GPIOA
# define ADCx_IN3_PIN              GPIO_Pin_2

/*ADC ͨ�� 4*/
# define ADCx_IN4_GPIO_CLK         RCC_APB2Periph_GPIOA
# define ADCx_IN4_PORT             GPIOA
# define ADCx_IN4_PIN              GPIO_Pin_3

/*--------------��������--------------*/
//AD��ʼ��
void AD_Init(void);
/*��ȡADC�Ľ��*/
void AD_GetValue(void);

# endif /*_BSP_AD_H*/
