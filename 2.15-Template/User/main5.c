#include "led.h"
#include "delay.h"
#include "timer3.h"

int main(){
	
	LED_GPIO_Config();
	delay_init();
	
	while(1){
		LED_ON();
		delay_ms(500);
		LED_OFF();
		delay_ms(500);
	}
	return 0;
}
