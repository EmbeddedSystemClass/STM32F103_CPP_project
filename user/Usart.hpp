

#ifndef __USART_HPP__
#define __USART_HPP__


#ifdef __cplusplus
 extern "C" {
#endif 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "stm32f10x_usart.h"
#include "misc.h"	 
	 
 #define DEBUG_USARTx 									USART1
 #define DEBUG_USART_CLK 								RCC_APB2Periph_USART1
 #define DEBUG_USART_APBxClkCmd 				RCC_APB2PeriphClockCmd
 #define DEBUG_USART_BAUDRATE 					115200 
 // USART GPIO 
 #define DEBUG_USART_GPIO_CLK 					(RCC_APB2Periph_GPIOB)
 #define DEBUG_USART_GPIO_APBxClkCmd 		RCC_APB2PeriphClockCmd 

 #define DEBUG_USART_TX_GPIO_PORT 			GPIOB
 #define DEBUG_USART_TX_GPIO_PIN 				GPIO_Pin_6
 #define DEBUG_USART_RX_GPIO_PORT 			GPIOB
 #define DEBUG_USART_RX_GPIO_PIN 				GPIO_Pin_7 

 #define DEBUG_USART_IRQ 								USART1_IRQn
 #define DEBUG_USART_IRQHandler 				USART1_IRQHandler



#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define CommandLenth   11
extern u8 finishFlah;			
extern u8  USART_RX_BUF[USART_REC_LEN]; 	//接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         					//接收状态标记	


extern u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
extern u16 USART_RX_STA;       //接收状态标记	 
extern u8 rxFlag;
extern int16_t rxCounter;
extern int16_t rxCounterf;
void USART_Config(void);	 
void Usart_SendString( USART_TypeDef * pUSARTx, char *str);



	 
#ifdef __cplusplus
}
#endif



#endif

