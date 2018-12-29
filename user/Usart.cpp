
#include "Usart.hpp"

/*

0xA5 0x85 P1L P1H P2L P2H P3L P3H LED_State 0x0D 0x0A

Pitch PWM1  P1H<<8+P1L
Roll  PWM2  P2H<<8+P2L
Yaw   PWM3  P3H<<8+P3L
LED-On/Off  LED_State    1->On  0->Off

*/

u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
u16 USART_RX_STA=0;       //接收状态标记	 
u8 rxFlag=0;
u8 finishFlah=0;
int16_t rxCounter=0;
int16_t rxCounterf=0;

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
		NVIC_InitTypeDef NVIC_InitStructure;
	
		DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);

		DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK, ENABLE);

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
		
		GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);
		
		GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);


		//Usart1 NVIC 配置
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
		NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
		
		 //USART 初始化设置

		USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;//串口波特率
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
		USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
		USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

		USART_Init(USART1, &USART_InitStructure); //初始化串口1
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
		USART_Cmd(USART1, ENABLE);                    //使能串口1 
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







