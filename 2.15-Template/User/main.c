//#include "stm32f10x.h"

//void delay(){
//	int i;
//	for(i = 0; i < 2500000; ++i);
//}

//int main(){
//	GPIO_InitTypeDef GPIO_InitStruct;
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//	
//	GPIO_Init(GPIOC, &GPIO_InitStruct);
//	GPIO_SetBits(GPIOC, GPIO_Pin_13);
//	//GPIO_ResetBits(GPIOC, GPIO_Pin_13);
//	
////	while(1){
////		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
////		delay();
////		GPIO_SetBits(GPIOC, GPIO_Pin_13);
////		delay();
////	}
//}
