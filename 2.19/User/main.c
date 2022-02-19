#include "stm32f10x.h"
#include "led.h"
#include "sys.h"
#include "delay.h"
#include "my_usart1.h"
#include "mem.h"
#include "test.h"
#include <string.h>
#include <stdio.h>
//unsigned char membase[MEMBASESIZE];
//int memtbl[MEMTBLSIZE];
extern unsigned char membase[];
extern int memtbl[];

int main(void){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	LED_GPIO_Config();
	My_USART1();
	delay_init();
	LED_ON();
	mem_init();
	printf("MEMBASESIZE = %d\r\n", MEMBASESIZE);
	printf("MEMTBLSIZE = %d\r\n", MEMTBLSIZE);
	start_test(membase, MEMBASESIZE);
	while(1);
}
