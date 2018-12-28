#include "main.hpp"


void RCC_Configuration(void)
{
    RCC_DeInit();//
 
    RCC_HSICmd(ENABLE);//ʹ��HSI  
    while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);//�ȴ�HSIʹ�����
 
    RCC_HCLKConfig(RCC_SYSCLK_Div1);   
    RCC_PCLK1Config(RCC_HCLK_Div2);
    RCC_PCLK2Config(RCC_HCLK_Div1);
    
    //���� PLL ʱ��Դ�ͱ�Ƶϵ��
    RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_12);//ʹ�ܻ���ʧ�� PLL,�����������ȡ:ENABLE ���� DISABLE 
    RCC_PLLCmd(ENABLE);
    //�ȴ�ָ���� RCC��־���óɹ����ȴ�PLL��ʼ���ɹ�
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
 
    //����ϵͳʱ��(SYSCLK) ����PLLΪϵͳʱ��Դ
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);//ѡ����Ҫ��ʱ��Դ 
    //  0x00:HSI ��Ϊʱ��Դ
    //  0x04:HSE ��Ϊʱ��Դ
    //  0x08:PLL ��Ϊʱ��Դ
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

