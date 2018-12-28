#include "main.hpp"


void RCC_Configuration(void)
{
    RCC_DeInit();//
 
    RCC_HSICmd(ENABLE);//使能HSI  
    while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);//等待HSI使能完成
 
    RCC_HCLKConfig(RCC_SYSCLK_Div1);   
    RCC_PCLK1Config(RCC_HCLK_Div2);
    RCC_PCLK2Config(RCC_HCLK_Div1);
    
    //设置 PLL 时钟源和倍频系数
    RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_12);//使能或者失能 PLL,这个参数可以取:ENABLE 或者 DISABLE 
    RCC_PLLCmd(ENABLE);
    //等待指定的 RCC标志设置成功，等待PLL初始化成功
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
 
    //设置系统时钟(SYSCLK) 设置PLL为系统时钟源
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);//选择想要的时钟源 
    //  0x00:HSI 作为时钟源
    //  0x04:HSE 作为时钟源
    //  0x08:PLL 作为时钟源
    while(RCC_GetSYSCLKSource() != 0x08);//??????????????,RCC_SYSCLKSource_PLL 
}


RCC_ClocksTypeDef SYSclock;


int main(int argc, char *argv[])
{
	RCC_Configuration();
	MotorDriverGPIO_Init();

	TIM4_init();
	USART_Config();
		
	RCC_GetClocksFreq(&SYSclock);

	GUA_Timer1_PWM_Init(20000);	
	GUA_Timer1_PWM_Status(GUA_TIMER1_PWM_STATUS_ON);   	
	
	while(1)
	{
		
		
	}

}

