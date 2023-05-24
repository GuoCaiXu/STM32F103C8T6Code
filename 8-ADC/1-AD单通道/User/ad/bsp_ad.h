# ifndef _BSP_AD_H
# define _BSP_AD_H

# include "stm32f10x.h"

# define ADCx                       ADC1
# define ADCx_APBxClock_FUN          RCC_APB2PeriphClockCmd
# define ADCx_CLK                    RCC_APB2Periph_ADC1

# define ADCx_IN1_GPIO_CLK         RCC_APB2Periph_GPIOA
# define ADCx_IN1_PORT             GPIOA
# define ADCx_IN1_PIN              GPIO_Pin_0

/*--------------函数定义--------------*/
//AD初始化
void AD_Init(void);
/*获取ADC的结果*/
uint16_t AD_GetValue(void);

# endif /*_BSP_AD_H*/
