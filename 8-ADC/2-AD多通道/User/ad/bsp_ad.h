# ifndef _BSP_AD_H
# define _BSP_AD_H

# include "stm32f10x.h"

# define ADCx                       ADC1
# define ADCx_APBxClock_FUN          RCC_APB2PeriphClockCmd
# define ADCx_CLK                    RCC_APB2Periph_ADC1

/*ADC 通道 1*/
# define ADCx_IN1_GPIO_CLK         RCC_APB2Periph_GPIOA
# define ADCx_IN1_PORT             GPIOA
# define ADCx_IN1_PIN              GPIO_Pin_0

/*ADC 通道 2*/
# define ADCx_IN2_GPIO_CLK         RCC_APB2Periph_GPIOA
# define ADCx_IN2_PORT             GPIOA
# define ADCx_IN2_PIN              GPIO_Pin_1

/*ADC 通道 3*/
# define ADCx_IN3_GPIO_CLK         RCC_APB2Periph_GPIOA
# define ADCx_IN3_PORT             GPIOA
# define ADCx_IN3_PIN              GPIO_Pin_2

/*ADC 通道 4*/
# define ADCx_IN4_GPIO_CLK         RCC_APB2Periph_GPIOA
# define ADCx_IN4_PORT             GPIOA
# define ADCx_IN4_PIN              GPIO_Pin_3

/*--------------函数定义--------------*/
//AD初始化
void AD_Init(void);
/*获取ADC的结果*/
uint16_t AD_GetValue(uint8_t ADC_Channel);

# endif /*_BSP_AD_H*/
