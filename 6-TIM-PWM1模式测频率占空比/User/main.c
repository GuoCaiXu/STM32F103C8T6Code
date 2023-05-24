# include "stm32f10x.h"
# include "./general/bsp_general.h"
# include "./oled/OLED.h"
# include "./ic/bsp_ic.h"

//软件延时函数
void delay(uint32_t count){

	while(count --);
}

int main(void){

	OLED_Init();
	GENERAL_TIM_Init();
	IC_Init();

	OLED_ShowString(1, 1, "Freq:00000Hz");
	OLED_ShowString(2, 1, "Duty:00%");

	/*频率1000MHz	占空比50%*/
	// PWM_SetPrescaler(720 - 1);			//Freq = 72M / (PSC + 1) / 100
	// PWM_SetCompare1(50);				//Duty = CRR / 100

	/*频率100MHz	占空比80%*/
	PWM_SetPrescaler(720 - 1);			//Freq = 72M / (PSC + 1) / 100
	PWM_SetCompare1(80);				//Duty = CRR / 100


	while(1){
		OLED_ShowNum(1, 6, IC_GetFreq(), 5);
		OLED_ShowNum(2, 6, IC_GetDuty(), 2);
	}
}
