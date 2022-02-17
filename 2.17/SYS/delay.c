#include "delay.h"
#include "stm32f10x.h"  //包含需要的头文件


void delay_init()
{
	SysTick->CTRL &= ~(1 << 2); //系统时钟八分频
}


void delay_ms(u16 nms)
{	 		  	  
	unsigned int tmp;
	SysTick->LOAD = (unsigned int)nms*9000; //重装数值
	SysTick->VAL = 0; //清空计数器
	SysTick->CTRL |= 1; //启动计数器
	do{
		tmp = SysTick->CTRL;
	}while((tmp >> 16) == 0);
	
	SysTick->CTRL &= ~1; //关闭计数器
	SysTick->VAL = 0; //清空计数器
}


