#ifndef __DS_TIMER_H
#define __DS_TIMER_H

#include "stm32f10x.h"
//定时器接口 //CNT = 72MHZ / (PSC +1) / (ARR + 1)
//TIM接口
#define TIMRCC RCC_APB2Periph_TIM1 //定时器1 高级定时器
#define TIM TIM1
#define TIMClockDivision TIM_CKD_DIV1 //可选参数 TIM_CKD_DIV2 TIM_CKD_DIV4 DIV1表示不分频
#define TIMCounterMode TIM_CounterMode_Up //可选参数 TIM_CounterMode_Down
#define TIMARR 10000-1
#define TIMPSC 72-1  //1s 72 000 000 / 7200 /10000
//NVIC接口
#define NVICGroup NVIC_PriorityGroup_2 //优先级组别
#define NVICIRQChannel TIM1_UP_IRQn //中断号
#define NVICChannelPreemptionPriority 2 //抢占优先级
#define NVICChannelSubPriority 1 //响应优先级

#define PWMGPIO GPIOA
#define PWMGPIORCC RCC_APB2Periph_GPIOA
#define PWMpin GPIO_Pin_8

#define TIMOCMode TIM_OCMode_PWM1
#define TIMOCPolarity TIM_OCPolarity_High
#define TIMOCCRR 0
#define TIMOCInit TIM_OC1Init //对通道二进行设置
//声明函数 变量
void MoterTimer_Init();
void Moter_PWM_SetCompare1(uint16_t Compare);

#endif