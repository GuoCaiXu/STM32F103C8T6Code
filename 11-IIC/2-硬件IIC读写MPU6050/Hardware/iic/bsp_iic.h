# ifndef _BSP_IIC_H
# define _BSP_IIC_H

# include "stm32f10x.h"

# define IIC_SCL_PIN        GPIO_Pin_10
# define IIC_SCL_PORT       GPIOB
# define IIC_SCL_CLK        RCC_APB2Periph_GPIOB

# define IIC_SDA_PIN        GPIO_Pin_11
# define IIC_SDA_PORT       GPIOB
# define IIC_SDA_CLK        RCC_APB2Periph_GPIOB

# define IIC_W_SCL(x)       GPIO_WriteBit(IIC_SCL_PORT, IIC_SCL_PIN, (BitAction)(x))
# define IIC_W_SDA(x)       GPIO_WriteBit(IIC_SDA_PORT, IIC_SDA_PIN, (BitAction)(x))

# define IIC_R_SCL          GPIO_ReadInputDataBit(IIC_SCL_PORT, IIC_SCL_PIN)
# define IIC_R_SDA          GPIO_ReadInputDataBit(IIC_SDA_PORT, IIC_SDA_PIN)

void IIC_Init(void);
void IIC_Start(void);
void IIC_Stop(void);
void IIC_SendByte(uint8_t Byte);
uint8_t IIC_ReceiveByte(void);
void IIC_SendACK(uint8_t AckBit);
uint8_t IIC_ReceiveACK(void);

# endif /*_BSP_IIC_H*/
