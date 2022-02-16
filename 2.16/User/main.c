#include "led.h"
#include "delay.h"
#include "timer3.h"
#include "sys.h"

int main(){
	
	LED_GPIO_Config();
	delay_init();
	
	while(1){
		//*((unsigned int*)0x422201B4) = 0;
		PCout(13) = 0;
		delay_ms(500);
		//*((unsigned int*)0x422201B4) = 1;
		PCout(13) = 1;
		delay_ms(500);
	}
	return 0;
}
