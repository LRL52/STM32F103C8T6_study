#include "test.h"
#include "my_usart1.h"
#include "delay.h"

void my_transmit(const char *str,size_t sz){
	char *s = str;
	USART1_SendString(s);
}

void my_delay(uint32_t delay){
	delay_ms(delay);
}