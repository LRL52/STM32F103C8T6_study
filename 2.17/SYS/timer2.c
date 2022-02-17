#include "timer2.h"
#include "led.h"
/********************
���ܶ�ʱ��ʱ�ӡ�
RCC_APB1PeriphClockCmd();
��  ��ʼ����ʱ��������ARR,PSC��
TIM_TimeBaseInit();
�ۿ�����ʱ���жϣ�����NVIC��
void TIM_ITConfig();
NVIC_Init();
��ʹ�ܶ�ʱ����
TIM_Cmd();
�ޱ�д�жϷ�������
TIMx_IRQHandler();
*****************/
void TIM2_Init(u16 arr,u16 psc){
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = arr;
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStruct);	
	
	TIM_Cmd(TIM2, ENABLE);
}

void TIM2_IRQHandler(){
	static int i = 0;
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) != RESET){
		switch(i){
			case 0: 
				LED_ON(); i ^= 1;						
				break;
			case 1:
				LED_OFF(); i ^= 1;
				break;	
		}
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

		

