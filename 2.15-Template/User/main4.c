#include "led.h"
#include "delay.h"
#include "timer3.h"

int main(){
	
	LED_GPIO_Config();
	delay_init();
	TIM3_Init(9999, 7199);
	
	return 0;
}
