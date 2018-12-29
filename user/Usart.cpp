
#include "Usart.hpp"

/*

0xA5 0x85 P1L P1H P2L P2H P3L P3H LED_State 0x0D 0x0A

Pitch PWM1  P1H<<8+P1L
Roll  PWM2  P2H<<8+P2L
Yaw   PWM3  P3H<<8+P3L
LED-On/Off  LED_State    1->On  0->Off

*/

u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
u16 USART_RX_STA=0;       //����״̬���	 
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


		//Usart1 NVIC ����
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
		NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
		
		 //USART ��ʼ������

		USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;//���ڲ�����
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
		USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
		USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

		USART_Init(USART1, &USART_InitStructure); //��ʼ������1
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
		USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 
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







