# ifndef _BSP_USART_H
# define _BSP_USART_H

# include "stm32f10x.h"
# include <stdio.h>
# include <stdarg.h>

extern uint8_t Serial_TxPacket[];
extern uint8_t Serial_RxPacket[];

# define USARTx_BAUDRATE        9600

# define USARTx                 USART1
# define USARTx_CLK             RCC_APB2Periph_USART1

# define USART_TX_PIN           GPIO_Pin_9
# define USART_TX_CLK           RCC_APB2Periph_GPIOA
# define USART_TX_PORT          GPIOA

# define USART_RX_PIN           GPIO_Pin_10
# define USART_RX_CLK           RCC_APB2Periph_GPIOA
# define USART_RX_PORT          GPIOA

void USARTx_Init(void);
void Serial_SendByte(uint8_t Byte);
void Serial_SendArray(uint8_t *Array, uint8_t Length);
void Serial_SendString(char *String);
uint32_t Serial_Pow(uint32_t x, uint32_t y);
void Serial_SendNumber(uint32_t Number, uint8_t Lenght);
void Serial_Printf(char *format, ...);
void Reception_Data_Show_OLED(void);
void Serial_SendPacket(void);
uint8_t USARTx_GetRxFlag(void);

# endif /*_BSP_USART_H*/
