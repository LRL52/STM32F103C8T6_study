#include "led.h"

void LED_GPIO_Config(){
	//≈‰÷√ ±÷”
	GPIO_InitTypeDef GPIO_InitStruct; 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	//≈‰÷√“˝Ω≈
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
}

void LED_ON(){
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);
}

void LED_OFF(){
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
}

//int cnt = 1000;
//void LED_RUN(){
//	static int i = 0;
//	switch(i){
//		case 0: 
//			if(cnt == 0){
//				LED_ON(); i ^= 1;
//				cnt = 1000;
//			}
//			break;
//		case 1:
//			if(cnt == 0){
//				LED_OFF(); i ^= 1;
//				cnt = 1000;
//			}
//			break;
//	}
//}