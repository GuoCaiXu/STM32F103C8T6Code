# ifndef _BSP_SPI_H
# define _BSP_SPI_H

# include "stm32f10x.h"

# define SS_PIN                 GPIO_Pin_4
# define SS_PORT                GPIOA
# define SS_CLK                 RCC_APB2Periph_GPIOA

# define SCK_PIN                GPIO_Pin_5
# define SCK_PORT               GPIOA
# define SCK_CLK                RCC_APB2Periph_GPIOA

# define MOSI_PIN               GPIO_Pin_7
# define MOSI_PORT              GPIOA
# define MOSI_CLK               RCC_APB2Periph_GPIOA

# define MISO_PIN               GPIO_Pin_6
# define MISO_PORT              GPIOA
# define MISO_CLK               RCC_APB2Periph_GPIOA

# define SPI_SS_W(x)            GPIO_WriteBit(SS_PORT, SS_PIN, (BitAction)x)

void MySPI_Init(void);
void MySPI_Start(void);
void MySPI_Stop(void);
uint8_t MySPI_SwapByte(uint8_t ByteSend);

# endif /*_BSP_SPI_H*/
