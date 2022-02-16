#include "led.h"
#include "delay.h"
#include "timer3.h"
#include "sys.h"

int main(){
	
	LED_GPIO_Config();
	delay_init();
	
	while(1){
		PCout(13) = 0;
		delay_ms(500);
		PCout(13) = 1;
		delay_ms(500);
	}
	return 0;
}
