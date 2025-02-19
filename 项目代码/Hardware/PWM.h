#ifndef __PWM_H
#define __PWM_H
#include "stm32f10x.h"

//接口

//PWM接口设置
#define PWMRCC RCC_APB1Periph_TIM2
#define PWMTIM TIM2
#define PWMGPIO GPIOA
#define PWMGPIORCC RCC_APB2Periph_GPIOA
#define PWMpin GPIO_Pin_0 // TIM2_CH1
//TIM设置
#define TIMClockDivision TIM_CKD_DIV1
#define TIMCounterMode TIM_CounterMode_Up
#define TIMARR 100-1
#define TIMPsc 72-1  //72 000 000 / 72 / 100 = 10000HZ
//OC设置
#define TIMOCMode TIM_OCMode_PWM2
#define TIMOCPolarity TIM_OCPolarity_High
#define TIMOCCRR 0
#define TIMOCInit TIM_OC1Init
void PWM_Init();
void PWM_SetCompare1(uint16_t Compare);
void PWM_SetCompare2(uint16_t Compare);
#endif