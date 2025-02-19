#include "Motor.h"


void Motor_Init(void)
{
	RCC_APB2PeriphClockCmd(MOTORCC, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = MOTORPIN1|MOTORPIN2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MOTORGPIO, &GPIO_InitStructure);
	
	MoterTimer_Init();
}

void Motor_SetSpeed(int16_t Speed)
{
	if (Speed >= 0)
	{
		GPIO_SetBits(MOTORGPIO, MOTORPIN1);
		GPIO_ResetBits(MOTORGPIO, MOTORPIN2);
		Moter_PWM_SetCompare1(Speed);
	}
	else
	{
		GPIO_ResetBits(MOTORGPIO, MOTORPIN1);
		GPIO_SetBits(MOTORGPIO, MOTORPIN2);
		Moter_PWM_SetCompare1(-Speed);
	}
}
