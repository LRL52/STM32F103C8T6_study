	
int main()
{
	*(unsigned int*)0x40021018 |=(1<<4);//��GPIOCʱ��, RCC_APB2ENR
	*(unsigned int*)0x40011004 &=~(0x0F<<(4*5));//�������ģʽ, GPIOC_CRH
	*(unsigned int*)0x40011004 |=(1<<(4*5));
	*(unsigned int*)0x4001100C &=~(1<<13);//��������͵�ƽ, GPIOC_ODR
	//*(unsigned int*)0x4001100C |=(1<<13);//��������ߵ�ƽ
	
	while(1);
	
}

void SystemInit(void)
{

}
