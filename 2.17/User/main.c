#include "stm32f10x.h"
#include "led.h"
#include "sys.h"
#include "delay.h"
#include "my_usart1.h"
#include <string.h>
#include <stdio.h>
char text[] = "Hello world!\r\n  ¡ª¡ªsent by LRL52 on Feb 17th, 2022";

int main(void){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	LED_GPIO_Config();
	LED_ON();
	My_USART1();
	printf("%s\r\n", text);
//	USART1_SendString(text);
//	static char s[2] = {0};
//	while(1){
//		while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
//		s[0] = USART_ReceiveData(USART1);
//		USART1_SendString(s);
//	}
	while(1);
}
