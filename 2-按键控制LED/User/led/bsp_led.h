# ifndef _BSP_LED_H
# define _BSP_LED_H

# include "stm32f10x.h"

# define LED1_GPIO_CLK              RCC_APB2Periph_GPIOC
# define LED1_GPIO_PORT             GPIOC
# define LED1_GPIO_PIN              GPIO_Pin_15

# define LED2_GPIO_CLK              RCC_APB2Periph_GPIOC
# define LED2_GPIO_PORT             GPIOC
# define LED2_GPIO_PIN              GPIO_Pin_14

# define LED1_OFF                   GPIO_ResetBits(LED1_GPIO_PORT, LED1_GPIO_PIN)
# define LED1_ON                    GPIO_SetBits(LED1_GPIO_PORT, LED1_GPIO_PIN)

# define LED2_OFF                   GPIO_ResetBits(LED2_GPIO_PORT, LED2_GPIO_PIN)
# define LED2_ON                    GPIO_SetBits(LED2_GPIO_PORT, LED2_GPIO_PIN)

# define digitalHi(p, i)    {p->BSRR = i;}
# define digitalLo(p, i)    {p->BRR = i;}
# define digitalTOGGLE(p, i)    {p->ODR ^= i;}

# define LED1_TOGGLE            digitalTOGGLE(LED1_GPIO_PORT, LED1_GPIO_PIN)
# define LED2_TOGGLE            digitalTOGGLE(LED2_GPIO_PORT, LED2_GPIO_PIN)

# define LED1_GetBit            GPIO_ReadOutputDataBit(LED1_GPIO_PORT, LED1_GPIO_PIN)
# define LED2_GetBit            GPIO_ReadOutputDataBit(LED2_GPIO_PORT, LED2_GPIO_PIN)

void LED_Init(void);

# endif /*_BSP_LED_H*/
