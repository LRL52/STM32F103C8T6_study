#include "delay.h"
#include "stm32f10x.h"  //������Ҫ��ͷ�ļ�


void delay_init()
{
	SysTick->CTRL &= ~(1 << 2); //ϵͳʱ�Ӱ˷�Ƶ
}


void delay_ms(u16 nms)
{	 		  	  
	unsigned int tmp;
	SysTick->LOAD = (unsigned int)nms*9000; //��װ��ֵ
	SysTick->VAL = 0; //��ռ�����
	SysTick->CTRL |= 1; //����������
	do{
		tmp = SysTick->CTRL;
	}while((tmp >> 16) == 0);
	
	SysTick->CTRL &= ~1; //�رռ�����
	SysTick->VAL = 0; //��ռ�����
}


