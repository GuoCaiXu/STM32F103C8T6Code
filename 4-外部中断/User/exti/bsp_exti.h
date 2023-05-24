# ifndef _BSP_EXTI_H
# define _BSP_EXTI_H

# include "stm32f10x.h"

# define KEY_GPIO_CLK                       RCC_APB2Periph_GPIOB
# define KEY_GPIO_PORT                      GPIOB

# define KEY1_GPIO_PIN                      GPIO_Pin_11
# define KEY1_EXTI_GPIO_PORTSOURCE          GPIO_PortSourceGPIOB
# define KEY1_EXTI_GPIO_PINSOURCE           GPIO_PinSource11
# define KEY1_EXTI_LINE                     EXTI_Line11
# define KEY1_EXTI_IRQ                      EXTI15_10_IRQn

# define KEY2_GPIO_PIN                      GPIO_Pin_1
# define KEY2_EXTI_GPIO_PORTSOURCE          GPIO_PortSourceGPIOB
# define KEY2_EXTI_GPIO_PINSOURCE           GPIO_PinSource1
# define KEY2_EXTI_LINE                     EXTI_Line1
# define KEY2_EXTI_IRQ                      EXTI1_IRQn

void EXTI_KEY_Init(void);       //外部中断初始化

# endif /*_BSP_EXTI_H*/
