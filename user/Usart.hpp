

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
 #define DEBUG_USART_TX_GPIO_PIN 				GPIO_Pin_9
 #define DEBUG_USART_RX_GPIO_PORT 			GPIOB
 #define DEBUG_USART_RX_GPIO_PIN 				GPIO_Pin_10 

 #define DEBUG_USART_IRQ 								USART1_IRQn
 #define DEBUG_USART_IRQHandler 				USART1_IRQHandler


	void USART_Config(void);	 
	 
	 
#ifdef __cplusplus
}
#endif



#endif

