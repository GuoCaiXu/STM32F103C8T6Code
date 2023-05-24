# ifndef _BSP_DMA_H
# define _BSP_DMA_H

# define DMAx                   DMA1
# define DMAx_AHBPeriph_FUN     RCC_AHBPeriphClockCmd
# define DMAx_CLK               RCC_AHBPeriph_DMA1

# define DMAx_CHANNELx          DMA1_Channel1

# include "stm32f10x.h"

/*-----------------º¯Êý¶¨Òå-----------------*/
void MyDMA_Init(uint32_t AddrA, uint32_t AddrB, uint16_t Size);
void MyDMA_Transfer(void);

# endif /*_BSP_DMA_H*/
