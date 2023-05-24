# include "stm32f10x.h"
# include "./oled/OLED.h"
# include "./delay/bsp_delay.h"
# include "./dma/bsp_dma.h"

uint8_t DataA[] = {0x01, 0x02, 0x03, 0x04};
uint8_t DataB[] = {0, 0, 0, 0};

/**
 *  @brief  主函数
 *  @param  无
 *  @retval 无
 */
int main(void){

    OLED_Init();

    OLED_ShowString(1, 1, "DataA");
    OLED_ShowString(3, 1, "DataA");
    OLED_ShowHexNum(1, 8, (uint32_t)DataA, 8);
    OLED_ShowHexNum(3, 8, (uint32_t)DataB, 8);

    OLED_ShowHexNum(2, 1, DataA[0], 2);
    OLED_ShowHexNum(2, 4, DataA[1], 2);
    OLED_ShowHexNum(2, 7, DataA[2], 2);
    OLED_ShowHexNum(2, 10, DataA[3], 2);

    OLED_ShowHexNum(4, 1, DataB[0], 2);
    OLED_ShowHexNum(4, 4, DataB[1], 2);
    OLED_ShowHexNum(4, 7, DataB[2], 2);
    OLED_ShowHexNum(4, 10, DataB[3], 2);

    MyDMA_Init((uint32_t)DataA, (uint32_t)DataB, 4);

    while(1){

        DataA[0] ++;
        DataA[1] ++;
        DataA[2] ++;
        DataA[3] ++;

        OLED_ShowHexNum(2, 1, DataA[0], 2);
        OLED_ShowHexNum(2, 4, DataA[1], 2);
        OLED_ShowHexNum(2, 7, DataA[2], 2);
        OLED_ShowHexNum(2, 10, DataA[3], 2);

        OLED_ShowHexNum(4, 1, DataB[0], 2);
        OLED_ShowHexNum(4, 4, DataB[1], 2);
        OLED_ShowHexNum(4, 7, DataB[2], 2);
        OLED_ShowHexNum(4, 10, DataB[3], 2);

        Delay_s(1);

        MyDMA_Transfer();

        OLED_ShowHexNum(2, 1, DataA[0], 2);
        OLED_ShowHexNum(2, 4, DataA[1], 2);
        OLED_ShowHexNum(2, 7, DataA[2], 2);
        OLED_ShowHexNum(2, 10, DataA[3], 2);

        OLED_ShowHexNum(4, 1, DataB[0], 2);
        OLED_ShowHexNum(4, 4, DataB[1], 2);
        OLED_ShowHexNum(4, 7, DataB[2], 2);
        OLED_ShowHexNum(4, 10, DataB[3], 2);

        Delay_s(1);
    }
}
