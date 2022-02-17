#include "led.h"
#include "sys.h"
#include "delay.h"
#include "my_usart1.h"
#include <string.h>
char text[] = "Hello world!";

int main(){
	//LED_GPIO_Config();
	//LED_ON();
	My_USART1();
	int i;
	for(i = 0; i < strlen(text); ++i){
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
		USART_SendData(USART1, text[i]);
	}
	while(1);
	return 0;
}
