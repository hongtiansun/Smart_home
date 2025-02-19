#include "stm32f10x.h"                  // Device header

void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_SetBits(GPIOC, GPIO_Pin_14);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB, GPIO_Pin_10);
	GPIO_ResetBits(GPIOB, GPIO_Pin_11);
}

void LED1_ON(void)
{
	GPIO_ResetBits(GPIOC, GPIO_Pin_14);
}

void LED1_OFF(void)
{
	GPIO_SetBits(GPIOC, GPIO_Pin_14);
}

void LED1_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_14) == 0)
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_14);
	}
	else
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_14);
	}
}
void LED2_OFF(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_10);
}

void LED2_ON(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_10);
}
void LED3_OFF(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_11);
}

void LED3_ON(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_11);
}