# ifndef _BSP_LED_H
# define _BSP_LED_H

# include "stm32f10x.h"

# define LED_GPIO_CLK           RCC_APB2Periph_GPIOC

# define LED1_GPIO_PIN          GPIO_Pin_15
# define LED1_PORT              GPIOC

# define LED2_GPIO_PIN          GPIO_Pin_14
# define LED2_PORT              GPIOC

# define LED3_GPIO_PIN          GPIO_Pin_13
# define LED3_PORT              GPIOC

# define digitalTOGGLE(p, i)    {p->ODR ^= i;}
# define LED1_TOGGLE            digitalTOGGLE(LED1_PORT, LED1_GPIO_PIN)
# define LED2_TOGGLE            digitalTOGGLE(LED2_PORT, LED2_GPIO_PIN)
# define LED3_TOGGLE            digitalTOGGLE(LED3_PORT, LED3_GPIO_PIN)

# define LED1_ON                GPIO_SetBits(LED1_PORT, LED1_GPIO_PIN)
# define LED1_OFF               GPIO_ResetBits(LED1_PORT, LED1_GPIO_PIN)

# define LED2_ON                GPIO_SetBits(LED2_PORT, LED2_GPIO_PIN)
# define LED2_OFF               GPIO_ResetBits(LED2_PORT, LED2_GPIO_PIN)

# define LED3_ON                GPIO_SetBits(LED3_PORT, LED3_GPIO_PIN)
# define LED3_OFF               GPIO_ResetBits(LED3_PORT, LED3_GPIO_PIN)

//³õÊ¼»¯GPIO º¯Êý
void LED_GPIO_Config(void);

# endif /*_BSP_LED_H*/
