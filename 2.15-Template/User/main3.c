#include "led.h"
#include "delay.h"
#include "timer3.h"

int main(){
	
	LED_GPIO_Config();
	delay_init();
	TIM3_Init(9999, 7199);
	
	
	
//	while(1){
//		LED_ON();
//		delay_ms(1000);
//		LED_OFF();
//		delay_ms(1000);
//	}
	return 0;
}
