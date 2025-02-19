#ifndef __BUZZER_H
#define __BUZZER_H
#include "stm32f10x.h"

//�ӿڶ���
#define BeepGPIO_RCC RCC_APB2Periph_GPIOC //Beep GPIO �����������ʱ��
#define BeepGPIO GPIOC //Beep�������
#define BeepPin GPIO_Pin_13 //Beep������

//��������
void Buzzer_Init(void);
void Buzzer_ON();
void Buzzer_OFF();
#endif