#include "delay.h"
#include "stm32f10x.h"  //������Ҫ��ͷ�ļ�


//void delay_init(void)
//{
//	SysTick->CTRL &= ~(1 << 2); //ϵͳʱ�Ӱ˷�Ƶ
//}


//void delay_ms(u16 nms)
//{	 		  	  
//	unsigned int tmp;
//	SysTick->LOAD = (unsigned int)nms*9000; //��װ��ֵ
//	SysTick->VAL = 0; //��ռ�����
//	SysTick->CTRL |= 1; //����������
//	do{
//		tmp = SysTick->CTRL;
//	}while(((tmp >> 16) & 1) == 0);
//	
//	SysTick->CTRL &= ~1; //�رռ�����
//	SysTick->VAL = 0; //��ռ�����
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
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///ʹ��TIM3ʱ��
	TIM_TimeBaseInitStruct.TIM_Period    = xms*10-1; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler = 7200-1;       //��ʱ����Ƶ
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; //ʱ�ӷ�Ƶ1��
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);//��ʼ��TIM3
	TIM3->SR = 0;
	TIM_Cmd(TIM3,ENABLE); //������ʱ��
	while((TIM3->SR & TIM_FLAG_Update)!=SET);
	TIM_Cmd(TIM3,DISABLE); //�رն�ʱ��
	TIM3->CNT = 0;
}


