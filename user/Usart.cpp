
#include "Usart.hpp"

static void NVIC_Configuration(void)
{
		NVIC_InitTypeDef NVIC_InitStructure; 

		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);


		NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;

		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;

		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;

		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

		NVIC_Init(&NVIC_InitStructure);
}

void USART_Config(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;

		DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);

		DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK, ENABLE);

		GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);


		USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;

		USART_InitStructure.USART_WordLength = USART_WordLength_8b;

		USART_InitStructure.USART_StopBits = USART_StopBits_1;

		USART_InitStructure.USART_Parity = USART_Parity_No ;

		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

		USART_Init(DEBUG_USARTx, &USART_InitStructure);


		NVIC_Configuration();


		USART_ITConfig(DEBUG_USARTx, USART_IT_RXNE, ENABLE);

		USART_Cmd(DEBUG_USARTx, ENABLE);
}


void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
		USART_SendData(pUSARTx,ch);
		while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}


void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
		unsigned int k=0;
		do 
		{
			Usart_SendByte( pUSARTx, *(str + k) );
			k++;
		} while (*(str + k)!='\0');

		while (USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET) 
		{
			
		}
}


void DEBUG_USART_IRQHandler(void)
{
		uint8_t ucTemp;
		if (USART_GetITStatus(DEBUG_USARTx,USART_IT_RXNE)!=RESET) 
		{
			ucTemp = USART_ReceiveData( DEBUG_USARTx );
			//USART_SendData(DEBUG_USARTx,ucTemp);
		}
}
