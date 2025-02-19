#include "stm32f10x.h"
/*
#define TIMRCC RCC_APB2Periph_TIM1 //定时器1 高级定时器
#define TIM TIM1
#define TIMClockDivision TIM_CKD_DIV1 //可选参数 TIM_CKD_DIV2 TIM_CKD_DIV4 DIV1表示不分频
#define TIMCounterMode TIM_CounterMode_Up //可选参数 TIM_CounterMode_Down
#define TIMARR 0xFFFF
#define TIMPSC 72  // 72000 000 72
//NVIC接口
#define NVICGroup NVIC_PriorityGroup_2 //优先级组别
#define NVICIRQChannel TIM1_UP_IRQn //中断号
#define NVICChannelPreemptionPriority 2 //抢占优先级
#define NVICChannelSubPriority 1 //响应优先级
//利用定时器实现Delay_ms
void Delay_Init(){
	//开启时钟 TIM2 挂载在APB1总线上
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	//选择时基时钟 内部时钟
	TIM_InternalClockConfig(TIM);

	//配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIMClockDivision;//采样频率分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIMCounterMode;//向上计数模式
	TIM_TimeBaseInitStructure.TIM_Period=TIMARR;//ARR自动重装寄存器
	TIM_TimeBaseInitStructure.TIM_Prescaler=TIMPSC;//PSC预分频器值 
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;//重复计数器的值 高级定时器才有
	TIM_TimeBaseInit(TIM,&TIM_TimeBaseInitStructure);
	TIM_Cmd(TIM,ENABLE);
}

void Delay_us(uint16_t us)
{
    TIM_SetCounter(TIM, 0);
    while (TIM_GetCounter(TIM) < us);
}*/

/**
  * @brief  微秒级延时
  * @param  xus 延时时长，范围：0~233015
  * @retval 无
  */
void Delay_us(uint32_t xus)
{
	SysTick->LOAD = 72 * xus;				//设置定时器重装值
	SysTick->VAL = 0x00;					//清空当前计数值
	SysTick->CTRL = 0x00000005;				//设置时钟源为HCLK，启动定时器
	while(!(SysTick->CTRL & 0x00010000));	//等待计数到0
	SysTick->CTRL = 0x00000004;				//关闭定时器
}

/**
  * @brief  毫秒级延时
  * @param  xms 延时时长，范围：0~4294967295
  * @retval 无
  */
void Delay_ms(uint32_t xms)
{
	while(xms--)
	{
		Delay_us(1000);
	}
}
 
/**
  * @brief  秒级延时
  * @param  xs 延时时长，范围：0~4294967295
  * @retval 无
  */
void Delay_s(uint32_t xs)
{
	while(xs--)
	{
		Delay_ms(1000);
	}
} 
