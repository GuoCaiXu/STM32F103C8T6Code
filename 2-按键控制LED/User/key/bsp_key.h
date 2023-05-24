# ifndef _BSP_KEY_H
# define _BSP_KEY_H

# include "stm32f10x.h"

# define KEY1_GPIO_CLK          RCC_APB2Periph_GPIOB
# define KEY1_GPIO_PORT         GPIOB
# define KEY1_GPIO_PIN          GPIO_Pin_11

# define KEY2_GPIO_CLK          RCC_APB2Periph_GPIOB
# define KEY2_GPIO_PORT         GPIOB
# define KEY2_GPIO_PIN          GPIO_Pin_1

# define KEY1_Get_Bit           GPIO_ReadInputDataBit(KEY1_GPIO_PORT, KEY1_GPIO_PIN)
# define KEY2_Get_Bit           GPIO_ReadInputDataBit(KEY2_GPIO_PORT, KEY2_GPIO_PIN)

void KEY_Init(void);
uint8_t Key_GetNum(void);

# endif /*_BSP_KEY_H*/
