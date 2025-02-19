#include "DS_Timer.h"

void MoterTimer_Init(){
	//开启时钟 TIM2 挂载在APB1总线上
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	//选择时基时钟 内部时钟
	TIM_InternalClockConfig(TIM);

	//配置PWM引脚输出
	//配置GPIOA引脚 PWM输出
	RCC_APB2PeriphClockCmd(PWMGPIORCC,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=PWMpin;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(PWMGPIO,&GPIO_InitStructure);

	//配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIMClockDivision;//采样频率分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIMCounterMode;//向上计数模式
	TIM_TimeBaseInitStructure.TIM_Period=TIMARR;//ARR自动重装寄存器
	TIM_TimeBaseInitStructure.TIM_Prescaler=TIMPSC;//PSC预分频器值 
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;//重复计数器的值 高级定时器才有
	TIM_TimeBaseInit(TIM,&TIM_TimeBaseInitStructure);
	TIM_ClearFlag(TIM,TIM_FLAG_Update);//初始化完对中断标志位清零，防止复位时立即进入中断

	//配置中断输出
	//TIM_ITConfig(TIM,TIM_IT_Update,ENABLE);

	//配置NVIC
	NVIC_PriorityGroupConfig(NVICGroup);
	NVIC_InitTypeDef NVIC_InitTypeDefStructure;
	NVIC_InitTypeDefStructure.NVIC_IRQChannel=NVICIRQChannel;
	NVIC_InitTypeDefStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitTypeDefStructure.NVIC_IRQChannelPreemptionPriority=NVICChannelPreemptionPriority;
	NVIC_InitTypeDefStructure.NVIC_IRQChannelSubPriority=NVICChannelSubPriority;
	NVIC_Init(&NVIC_InitTypeDefStructure);
	//配置PWM OC输出
	//配置输出比较单元
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);///变量太多 赋初值 
	TIM_OCInitStructure.TIM_OCMode=TIMOCMode; //设置模式
	TIM_OCInitStructure.TIM_OCPolarity=TIMOCPolarity;  //设置极性
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//设置输出使能
	TIM_OCInitStructure.TIM_Pulse=TIMOCCRR;  // 设置CRR
	TIMOCInit(TIM,&TIM_OCInitStructure);

	// 5. 使能TIM1输出比较通道1的预装载寄存器
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable); //防止CRR瞬时变化造成的PWM波形抖动(CRR下一个更新中断进行更新)
	//启动定时器
	TIM_Cmd(TIM,ENABLE);
	// 7. 使能TIM1主输出，使PWM信号可以输出到引脚
	TIM_CtrlPWMOutputs(TIM1, ENABLE); // 高级定时器，需要主动输出PWM

}

void Moter_PWM_SetCompare1(uint16_t Compare){ //设置通道1比较值
	TIM_SetCompare1(TIM,Compare);
}

