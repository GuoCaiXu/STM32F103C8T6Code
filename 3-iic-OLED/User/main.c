# include "stm32f10x.h"
# include "./oled/oled.h"

int main(void){

	OLED_Init();

	while(1){
		OLED_ShowString(1, 1, "Hello Wrold!");
	}
}
