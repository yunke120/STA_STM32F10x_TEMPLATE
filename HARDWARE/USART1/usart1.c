#include "usart1.h"

void usart1_init(uint32_t bound)
{
	// GPIO�˿�����
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | USART1_RCC, ENABLE); 

	// USART1_TX
	GPIO_InitStructure.GPIO_Pin	  = USART1_TX_PIN; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP; // �����������
	GPIO_Init(USART1_PORT, &GPIO_InitStructure);	

	// USART1_RX
	GPIO_InitStructure.GPIO_Pin	 = USART1_RX_PIN;		 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; // ��������
	GPIO_Init(USART1_PORT, &GPIO_InitStructure);		 

	// USART ��ʼ������
	USART_InitStructure.USART_BaudRate			  = bound;							// ���ڲ�����
	USART_InitStructure.USART_WordLength		  = USART_WordLength_8b;			// �ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits			  = USART_StopBits_1;				// һ��ֹͣλ
	USART_InitStructure.USART_Parity			  = USART_Parity_No;				// ����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // ��Ӳ������������
	USART_InitStructure.USART_Mode				  = USART_Mode_Rx | USART_Mode_Tx;	// �շ�ģʽ

	USART_Init(USART1, &USART_InitStructure); // ��ʼ������1
	USART_Cmd(USART1, ENABLE);				  // ʹ�ܴ���1
}

void usart1_enable_it(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	// Usart1 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel					 = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;	   // ��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority		 = 3;	   // �����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd				 = ENABLE; // IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);								   // ����ָ���Ĳ�����ʼ��VIC�Ĵ���

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); // �������ڽ����ж�
}

void USART1_IRQHandler() { }
