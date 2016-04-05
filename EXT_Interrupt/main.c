#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "misc.h"

void EXTI15_10_IRQHandler(void)
{
	int i = 0;
	GPIO_SetBits(GPIOD,GPIO_Pin_12);
	for(i=0;i<500000;i++);
	GPIO_ResetBits(GPIOD,GPIO_Pin_12);
	for(i=0;i<500000;i++);
}

int main(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitTypeDef PIN;
	EXTI_InitTypeDef EXT;
	NVIC_InitTypeDef VCT;

	PIN.GPIO_Pin = GPIO_Pin_12;
	PIN.GPIO_Mode = GPIO_Mode_IN;
	PIN.GPIO_Speed = GPIO_Speed_25MHz;
	PIN.GPIO_PuPd = GPIO_PuPd_UP;

	GPIO_Init(GPIOD,&PIN);

	EXT.EXTI_Line = EXTI_Line12;
	EXT.EXTI_LineCmd = ENABLE;
	EXT.EXTI_Mode = EXTI_Mode_Interrupt;
	EXT.EXTI_Trigger = EXTI_Trigger_Falling;

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource12);

	EXTI_Init(&EXT);

	VCT.NVIC_IRQChannel = EXTI15_10_IRQn;
	VCT.NVIC_IRQChannelPreemptionPriority = 0x00;
	VCT.NVIC_IRQChannelSubPriority = 0x00;
	VCT.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&VCT);

    while(1)
    {

    }
}
