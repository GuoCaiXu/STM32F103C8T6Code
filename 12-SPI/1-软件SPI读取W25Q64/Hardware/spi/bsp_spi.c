# include "./spi/bsp_spi.h"

void MySPI_Init(void){

    RCC_APB2PeriphClockCmd(SS_CLK | SCK_CLK | MOSI_CLK | MISO_CLK, ENABLE);

    // 推挽输出
    GPIO_InitTypeDef    GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = SS_PIN | SCK_PIN | MOSI_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, & GPIO_InitStructure);

    // MISO 上拉输入
    GPIO_InitStructure.GPIO_Pin = MISO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, & GPIO_InitStructure);

    // SS 默认高电平
    SPI_SS_W(1);

    // SCK 默认低电平
    SPI_SCK_W(0);
}   

void MySPI_Start(void){

    SPI_SS_W(0);
}

void MySPI_Stop(void){

    SPI_SS_W(1);
}

uint8_t MySPI_SwapByte(uint8_t ByteSend){

    uint8_t i;

    for (i = 0; i < 8; i ++){

        SPI_MOSI_W((BitAction)(ByteSend & 0x80));
        ByteSend <<= 1;
        SPI_SCK_W(1);
        if (SPI_MISO_R() == 1) ByteSend |= 0x01;
        SPI_SCK_W(0);
    }

    return ByteSend;
}
