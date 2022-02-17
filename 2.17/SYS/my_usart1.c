/*
1.串口时钟、GPIOC时钟使能
2.GPIOA端口模式设置
3.串口参数初始化
4.开启中断并且初始化NVIC
5.使能串口
6.编写中断处理函数
*/
#include "my_usart1.h"
#include <string.h>
#include <stdio.h>

void My_USART1(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	//1.串口时钟、GPIOC时钟使能
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//2.GPIOA端口模式设置
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	//3.串口参数初始化
	USART_InitStruct.USART_BaudRate = 9600;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &USART_InitStruct);
	
	//4.开启中断并且初始化NVIC
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //记着别漏了！！！
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStruct);
	
	//5.使能串口
	USART_Cmd(USART1, ENABLE);
}

void USART1_SendChar(char c){
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	USART_SendData(USART1, c);
}

void USART1_SendString(char *s){
	int len = strlen(s), i;
	for(i = 0; i < len; ++i) USART1_SendChar(s[i]);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
}

int tot = 0;
void USART1_IRQHandler(){
	++tot;
	//printf("第 %d 次进入中断服务函数\r\n", ++tot);
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == RESET) return;
	uint16_t c = USART_ReceiveData(USART1);
	USART1_SendChar(c);
}

int fputc(int ch, FILE *f){
	USART1_SendChar((char)ch);
	return ch;
}
