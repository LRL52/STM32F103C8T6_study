#include "stm32f10x.h"

int main(){
	*(unsigned int*)0x40021018 |= 1 << 4; //RCC_APB2ENR IO端口C时钟开启
	*(unsigned int*)0x40011004 &= ~(0x0F << 20); //GPIOC_CRH 置0
	*(unsigned int*)0x40011004 |= 1 << 20; //通用推挽输出模式, 10Mhz
	//*(unsigned int*)0x40011004 |= 1 << 21; //通用推挽输出模式, 2Mhz
	//*(unsigned int*)0x4001100C &= ~(1 << 13); //GPIOC_ODR 置0
	*(unsigned int*)0x4001100C |= 1 << 13; //GPIOC_ODR 置1
	
	while(1);
}

void SystemInit(){
	
}
