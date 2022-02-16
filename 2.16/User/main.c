#include "led.h"
#include "delay.h"
#include "timer3.h"
#include "timer2.h"
#include "sys.h"

int main(){
	
	LED_GPIO_Config();
	delay_init();
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	TIM2_Init(4999, 7199);
	return 0;
}
