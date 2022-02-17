#include "led.h"
#include "sys.h"
#include "delay.h"
#include "my_usart1.h"
#include <string.h>
char text[] = "Hello world!";

int main(void){
	int i;
	LED_GPIO_Config();
	LED_ON();
	My_USART1();
	USART_ClearFlag(USART1, USART_FLAG_TC); //手动将TC标志位清0
	for(i = 0; i < strlen(text); ++i){
		USART_SendData(USART1, text[i]);
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	}
	while(1);
}
