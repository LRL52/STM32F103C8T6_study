#include "stm32f10x.h"

int main(){
	*(unsigned int*)0x40021018 |= 1 << 4; //RCC_APB2ENR IO�˿�Cʱ�ӿ���
	*(unsigned int*)0x40011004 &= ~(0x0F << 20); //GPIOC_CRH ��0
	*(unsigned int*)0x40011004 |= 1 << 20; //ͨ���������ģʽ, 10Mhz
	//*(unsigned int*)0x40011004 |= 1 << 21; //ͨ���������ģʽ, 2Mhz
	//*(unsigned int*)0x4001100C &= ~(1 << 13); //GPIOC_ODR ��0
	*(unsigned int*)0x4001100C |= 1 << 13; //GPIOC_ODR ��1
	
	while(1);
}

void SystemInit(){
	
}
