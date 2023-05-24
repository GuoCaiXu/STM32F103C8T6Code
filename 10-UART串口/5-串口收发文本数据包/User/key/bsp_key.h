# ifndef _BSP_KEY_H
# define _BSP_KEY_H

# include "stm32f10x.h"

# define KEY_PIN        GPIO_Pin_1
# define KEY_PORT       GPIOB
# define KEY_CLK        RCC_APB2Periph_GPIOB

void KEY_Init(void);
uint8_t KEY_GeyFlag(void);

# endif /*_BSP_KEY_H*/
