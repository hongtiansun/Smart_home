#ifndef __LIGHT_H
#define __LIGHT_H
#include "stm32f10x.h"

// �ӿڶ���
#define LightSensor_RCC RCC_APB2Periph_GPIOC
#define LightSensor_Pin GPIO_Pin_15
#define LightSensor_GPIO GPIOC
// ��������
void LightSensor_Init();
uint8_t LightSenor_Get();
#endif