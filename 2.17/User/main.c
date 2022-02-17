#include "stm32f10x.h"
#include "led.h"
#include "sys.h"
#include "delay.h"
#include "my_usart1.h"
#include <string.h>
#include <stdio.h>
char text[] = "Hello world!\r\n  ——sent by LRL52 on Feb 17th, 2022";
extern int tot;

int main(void){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	LED_GPIO_Config();
	LED_ON();
	delay_init();
	My_USART1();
	printf("%s\r\n", text);
	int i;
	for(i = 0; i < 10; ++i) delay_ms(1000);
	printf("%d 次进入中断服务函数\r\n", tot);
//	USART1_SendString(text);
//	static char s[2] = {0};
//	while(1){
//		while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
//		s[0] = USART_ReceiveData(USART1);
//		USART1_SendString(s);
//	}
	while(1);
}
