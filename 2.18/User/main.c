#include "stm32f10x.h"
#include "led.h"
#include "sys.h"
#include "delay.h"
#include "my_usart1.h"
#include "mem.h"
#include "test.h"
#include <string.h>
#include <stdio.h>
unsigned char membase[1024];
int memtbl[32];

int main(void){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	LED_GPIO_Config();
	LED_ON();
	delay_init();
	My_USART1();
	printf("test\r\n");
	mem_init();
	void *p1 = my_malloc(55);
    void *p2 = my_malloc(125);
    void *p3 = my_malloc(555);
    my_free(p1);
    my_free(p2);
    my_free(p3);
    printf("test done\r\n");
	start_test(membase, 1024);
	while(1);
}
