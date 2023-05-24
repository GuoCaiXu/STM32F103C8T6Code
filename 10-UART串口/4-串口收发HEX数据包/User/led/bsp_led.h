# ifndef _BSP_LED_H
# define _BSP_LED_H

# include "stm32f10x.h"

# define LED_PIN           GPIO_Pin_1
# define LED_PORT          GPIOA
# define LED_CLK           RCC_APB2Periph_GPIOA

# define LED_ON            GPIO_SetBits(LED_PORT, LED_PIN)
# define LED_OFF           GPIO_ResetBits(LED_PORT, LED_PIN)   

void LED_Init(void);

# endif /*_BSP_LED_H*/
