# include "./key/bsp_key.h"
# include "./delay/bsp_delay.h"

void KEY_Init(void){

    RCC_APB2PeriphClockCmd(KEY1_GPIO_CLK, ENABLE);

    GPIO_InitTypeDef    GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = KEY1_GPIO_PIN | KEY2_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStructure);
}

uint8_t Key_GetNum(void){

    uint8_t KeyNum = 0;
    if (KEY1_Get_Bit == 0){
        Delay_ms(20);
        while(KEY1_Get_Bit == 0);
        Delay_ms(20);
        KeyNum = 1;
    }
    else if (KEY2_Get_Bit == 0){
        Delay_ms(20);
        while(KEY2_Get_Bit == 0);
        Delay_ms(20);
        KeyNum = 2;
    }

    return KeyNum;
}
