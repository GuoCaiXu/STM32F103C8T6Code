# include "stm32f10x.h"
# include "./oled/OLED.h"
# include "./delay/bsp_delay.h"
# include "./mpu6050/bsp_mpu6050.h"

MPU6050_SixAxisData	Data;
uint8_t ID;
 
/**
 *  @brief  主函数
 *  @param  无
 *  @retval 无
 */
int main(void){ 

	OLED_Init();
	MPU6050_Init();

	OLED_ShowString(1, 1, "ID:");
	ID = MPU6050_GetID();
	OLED_ShowHexNum(1, 4, ID, 2);

	while(1){

		MPU6050_GetData(&Data);
		OLED_ShowSignedNum(2, 1, Data.AccX, 5);
		OLED_ShowSignedNum(3, 1, Data.AccY, 5);
		OLED_ShowSignedNum(4, 1, Data.AccZ, 5);
		OLED_ShowSignedNum(2, 8, Data.GyroX, 5);
		OLED_ShowSignedNum(3, 8, Data.GyroY, 5);
		OLED_ShowSignedNum(4, 8, Data.GyroZ, 5);
	}
}
