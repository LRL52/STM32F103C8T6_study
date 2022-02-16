	
int main()
{
	*(unsigned int*)0x40021018 |=(1<<4);//打开GPIOC时钟, RCC_APB2ENR
	*(unsigned int*)0x40011004 &=~(0x0F<<(4*5));//配置输出模式, GPIOC_CRH
	*(unsigned int*)0x40011004 |=(1<<(4*5));
	*(unsigned int*)0x4001100C &=~(1<<13);//配置输出低电平, GPIOC_ODR
	//*(unsigned int*)0x4001100C |=(1<<13);//配置输出高电平
	
	while(1);
	
}

void SystemInit(void)
{

}
