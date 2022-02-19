#include "timer3_IT_delay.h"
#include "led.h"
#include <stdio.h>
/********************
①能定时器时钟。
RCC_APB1PeriphClockCmd();
②  初始化定时器，配置ARR,PSC。
TIM_TimeBaseInit();
③开启定时器中断，配置NVIC。
void TIM_ITConfig();
NVIC_Init();
④使能定时器。
TIM_Cmd();
⑥编写中断服务函数。
TIMx_IRQHandler();
*****************/

static unsigned char flag = 0;
void TIM3_Init(u16 arr,u16 psc){
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = arr;
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
	
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStruct);	
	
	TIM_Cmd(TIM3, ENABLE);
	while(flag < 2) 
		NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;
	flag = 0;
}

void TIM3_IRQHandler(void){
	static int i = 0;
	if(TIM_GetITStatus(TIM3,TIM_IT_Update) != RESET){
		/*switch(i){
			case 0: 
				LED_ON(); i ^= 1;						
				break;
			case 1:
				LED_OFF(); i ^= 1;
				break;	
		}*/
		printf("flag = 1\r\n");
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		++flag;
		if(flag < 2) return;

		TIM_Cmd(TIM3, DISABLE);
		TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
		NVIC_InitTypeDef NVIC_InitStruct;
		NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;
		NVIC_InitStruct.NVIC_IRQChannelCmd = DISABLE;
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
		NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
		NVIC_Init(&NVIC_InitStruct);	
	}
}

		

