#include "led.h"
#include "sys.h"
#include "delay.h"
#include "my_usart1.h"
#include <string.h>
char text[] = "Hello world!";

int main(){
	LED_GPIO_Config();
	LED_ON();
	My_USART1();
	//while(1){	
	//USART_SendData(USART1, 'S');
	//}
	int i;
	for(i = 0; i < strlen(text); ++i){
		delay_ms(5);
		USART_SendData(USART1, text[i]);
	}
	while(1);
	return 0;
}
