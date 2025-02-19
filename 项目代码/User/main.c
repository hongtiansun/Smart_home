#include "stm32f10x.h" // Device header
#include "freertos.h"
#include "task.h"
#include "Delay.h"
#include "Serial.h"
#include "OLED.h"
#include "LED.h"
#include "string.h"
#include "PWM.h"
#include "Encoder.h"
#include "Timer.h"
#include "LightSensor.h"
#include "BUZZER.h"
#include "DS18B20.h"
#include "Motor.h"
#include "AD.h"

float Temp;
uint8_t LEDFlag = 0;
uint8_t LEDNUM = 0;
uint8_t LightNUM = 0;
uint8_t FANFlag = 0;
uint8_t FANMode = 0;
uint16_t Voice = 0;
uint16_t Fire = 0;
uint16_t FireFlag = 0;
void ASRPRO(void *arg) //语音识别模块
{
	while (1)
	{
		if (Serial_RxFlag == 1)
		{
			if (strcmp(Serial_RxPacket, "LED_ON") == 0)
			{
				LEDFlag = 1;		   // 开启灯光控制
				TIM_Cmd(TIM3, ENABLE); // 启动旋转编码器
				if (LEDNUM == 0)
				{
					NUM = 50;
					TIM_SetCounter(TIM3, NUM * 4); // 修改Encode的计数值 采用的是上下边沿都计数故而要乘4倍
					LEDNUM = 1;
				}
			}
			else if (strcmp(Serial_RxPacket, "LED_OFF") == 0)
			{
				LEDFlag = 0;			// 关闭灯光控制
				TIM_Cmd(TIM3, DISABLE); // 关闭旋转编码器
			}
			else if (strcmp(Serial_RxPacket, "LED_UP") == 0)
			{
				if (LEDFlag == 1)
				{
					if (NUM < 70)
					{
						NUM = NUM + 30;				   // 修改置位PWM的值
						TIM_SetCounter(TIM3, NUM * 4); // 修改Encode的计数值
					}
					else
					{
						NUM = 100;					   // 修改置位PWM的值
						TIM_SetCounter(TIM3, NUM * 4); // 修改Encode的计数值
					}
				}
			}
			else if (strcmp(Serial_RxPacket, "LED_DOWN") == 0)
			{
				if (LEDFlag == 1)
				{
					if (NUM > 30)
					{
						NUM = NUM - 30;				   // 修改置位PWM的值
						TIM_SetCounter(TIM3, NUM * 4); // 修改Encode的计数值
					}
					else
					{
						NUM = 0;					   // 修改置位PWM的值
						TIM_SetCounter(TIM3, NUM * 4); // 修改Encode的计数值
					}
				}
			}
			else if (strcmp(Serial_RxPacket, "FAN_ACT") == 0)
			{
				if(FANFlag == 1){ //防止风扇运行中翻转
					continue;
				}
				FANMode = 0;
			}
			else if (strcmp(Serial_RxPacket, "FAN_POC") == 0)
			{
				if(FANFlag == 1){ //防止风扇运行中翻转
					continue;
				}
				FANMode = 1;
			}
			else if (strcmp(Serial_RxPacket, "FAN_MODE") == 0)
			{
				if(FANMode == 1){
					Serial_SendString("FAN_ACT");
				}else{
					Serial_SendString("FAN_POC");
				}
			}
			else if (strcmp(Serial_RxPacket, "FAN_ON") == 0)
			{
				FANFlag = 1;
				if(FANMode == 0){
					Motor_SetSpeed(3333);//设置一档风速
				}else{
					Motor_SetSpeed(-3333);
				}
				
			}
			else if (strcmp(Serial_RxPacket, "FAN_ONE") == 0)
			{
				if (FANFlag == 1){
					if(FANMode == 0){
						Motor_SetSpeed(3333);//设置一档风速
					}else{
						Motor_SetSpeed(-3333);
					}
				}
			}
			else if (strcmp(Serial_RxPacket, "FAN_TWO") == 0)
			{
				if (FANFlag == 1){
					if(FANMode == 0){
						Motor_SetSpeed(6666);//设置二档风速
					}else{
						Motor_SetSpeed(-6666);
					}
				}
			}
			else if (strcmp(Serial_RxPacket, "FAN_THREE") == 0)
			{
				if (FANFlag == 1){
					if(FANMode == 0){
						Motor_SetSpeed(9999);//设置三档风速
					}else{
						Motor_SetSpeed(-9999);
					}
				}
			}
			else if (strcmp(Serial_RxPacket, "FAN_OFF") == 0)
			{
				if (FANFlag == 1){
					FANFlag = 0;
					Motor_SetSpeed(0); //关闭风扇
				}
			}
			else
			{

			}

			Serial_RxFlag = 0;
		}
	}
}
void Light_LED(void *arg) //备用光源模块
{

	while (1)
	{
		if (LEDFlag == 0)
		{
			LightNUM = LightSenor_Get();
			if (LightNUM == 1)
			{
				LED1_ON();
			}
			if (LightNUM == 0)
			{
				LED1_OFF();
			}
		}else{
			LED1_OFF();
		}
	}
}

void LED_Sys(void *arg) //系统光源
{

	while (1)
	{
		if (LEDFlag == 1)
		{
			PWM_SetCompare1(NUM);
			OLED_ShowNum(1, 5, NUM, 3);
		}
		else
		{
			// LED_NUM = NUM; //关灯记录当前亮度
			PWM_SetCompare1(0); // 设置占空比为0，关闭灯光系统
		}
	}
}

void Voice_S(void *arg){ //噪声模块
	while (1)
	{
		Voice = AD_GetValue(ADC_Channel_1);
		//OLED_ShowNum(3,1,Voice,4);
		if(Voice > 1000){
			if(FireFlag == 0)
				LED2_ON();
		}else{
			LED2_OFF();
		}
		vTaskDelay(300);
	}
	
}

void Fire_S(void *arg){ //火灾报警装置
	while (1)
	{
		Fire = AD2_GetValue(ADC_Channel_2);
		//OLED_ShowNum(4,1,Fire,4);
		
		if(Fire < 3000){ //有火
			FireFlag = 1;
			LED3_ON();
			Buzzer_ON();
		}
		if(Fire >3000){ //无火
			FireFlag = 0;
			LED3_OFF();
			Buzzer_OFF();
		}
		vTaskDelay(500);
	}
	
}


int main(void)
{

	// 硬件初始化
	OLED_Init();	// 显示屏初始化
	LED_Init();		// 备用光源初始化
	Serial_Init();	// 串口初始化
	PWM_Init();		// PWM TIM2控制灯光系统
	Encoder_Init(); // 编码器初始化
	Timer_Init();	// 计时器初始化
	LightSensor_Init();//光敏电阻传感器
	Buzzer_Init(); //报警器初始化
	Motor_Init(); //风扇初始化
	AD_Init(); //ADC初始化
	OLED_ShowString(1, 1, "NUM:");
	Delay_ms(500);
	//任务调度
	TaskHandle_t xhandleAsrpro, xhandleLEDSYS,xhandleLight,xhandleVoice,xhandleFire;
	xTaskCreate(ASRPRO, "AsrPro", 100, NULL, 1, &xhandleAsrpro);
	xTaskCreate(LED_Sys, "Task2", 100, NULL, 1, &xhandleLEDSYS);
	xTaskCreate(Light_LED,"LIght_LED",100,NULL,1,&xhandleLight);
	xTaskCreate(Voice_S,"Voice",100,NULL,1,&xhandleVoice);
	xTaskCreate(Fire_S,"Fire",100,NULL,1,&xhandleFire);
	vTaskStartScheduler();
	while (1)
	{

	}
}

/*void TIM1_UP_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) // 检查是否为更新中断
    {
        TIM_ClearITPendingBit(TIM1, TIM_IT_Update); // 清除中断标志

    }
}*/
