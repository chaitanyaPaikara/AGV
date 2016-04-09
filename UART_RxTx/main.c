#include "stm32f4xx_usart.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef PIN;
	USART_InitTypeDef MSG;

	PIN.GPIO_Pin = GPIO_Pin_6;
	PIN.GPIO_Mode = GPIO_Mode_AF;
	PIN.GPIO_OType = GPIO_OType_PP;
	PIN.GPIO_Speed = GPIO_Speed_25MHz;
	PIN.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);

	GPIO_Init(GPIOB,&PIN);

	MSG.USART_BaudRate = 9600;
	MSG.USART_WordLength = USART_WordLength_8b;
	MSG.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	MSG.USART_Mode = USART_Mode_Tx;
	MSG.USART_Parity = USART_Parity_No;
	MSG.USART_StopBits = USART_StopBits_2;

	USART_Init(USART1,&MSG);

	USART_Cmd(USART1, ENABLE);

    while(1)
    {
    	while( !(USART1->SR & 0x00000040) );
    	USART_SendData(USART1,'K');
    	while( !(USART1->SR & 0x00000040) );
    	USART_SendData(USART1,'R');
    	while( !(USART1->SR & 0x00000040) );
    	USART_SendData(USART1,'S');
    	while( !(USART1->SR & 0x00000040) );
    	USART_SendData(USART1,'S');
    	while( !(USART1->SR & 0x00000040) );
    	USART_SendData(USART1,'G');
    	while( !(USART1->SR & 0x00000040) );
    	USART_SendData(USART1,'\n');
    }
}
