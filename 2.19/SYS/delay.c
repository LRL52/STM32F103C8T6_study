#include "delay.h"
#include "stm32f10x.h"  //包含需要的头文件


//void delay_init(void)
//{
//	SysTick->CTRL &= ~(1 << 2); //系统时钟八分频
//}


//void delay_ms(u16 nms)
//{	 		  	  
//	unsigned int tmp;
//	SysTick->LOAD = (unsigned int)nms*9000; //重装数值
//	SysTick->VAL = 0; //清空计数器
//	SysTick->CTRL |= 1; //启动计数器
//	do{
//		tmp = SysTick->CTRL;
//	}while(((tmp >> 16) & 1) == 0);
//	
//	SysTick->CTRL &= ~1; //关闭计数器
//	SysTick->VAL = 0; //清空计数器
//}


void delay_init(void){
	NVIC_InitTypeDef NVIC_InitStruct;
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStruct);	
}


void delay_ms(u16 xms)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///使能TIM3时钟
	TIM_TimeBaseInitStruct.TIM_Period    = xms*10-1; 	//自动重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler = 7200-1;       //定时器分频
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; //时钟分频1倍
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);//初始化TIM3
	TIM3->SR = 0;
	TIM_Cmd(TIM3,ENABLE); //启动定时器
	while((TIM3->SR & TIM_FLAG_Update)!=SET);
	TIM_Cmd(TIM3,DISABLE); //关闭定时器
	TIM3->CNT = 0;
}


