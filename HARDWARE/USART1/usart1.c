#include "usart1.h"

void usart1_init(uint32_t bound)
{
	// GPIO端口设置
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | USART1_RCC, ENABLE); 

	// USART1_TX
	GPIO_InitStructure.GPIO_Pin	  = USART1_TX_PIN; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP; // 复用推挽输出
	GPIO_Init(USART1_PORT, &GPIO_InitStructure);	

	// USART1_RX
	GPIO_InitStructure.GPIO_Pin	 = USART1_RX_PIN;		 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; // 浮空输入
	GPIO_Init(USART1_PORT, &GPIO_InitStructure);		 

	// USART 初始化设置
	USART_InitStructure.USART_BaudRate			  = bound;							// 串口波特率
	USART_InitStructure.USART_WordLength		  = USART_WordLength_8b;			// 字长为8位数据格式
	USART_InitStructure.USART_StopBits			  = USART_StopBits_1;				// 一个停止位
	USART_InitStructure.USART_Parity			  = USART_Parity_No;				// 无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 无硬件数据流控制
	USART_InitStructure.USART_Mode				  = USART_Mode_Rx | USART_Mode_Tx;	// 收发模式

	USART_Init(USART1, &USART_InitStructure); // 初始化串口1
	USART_Cmd(USART1, ENABLE);				  // 使能串口1
}

void usart1_enable_it(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	// Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel					 = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;	   // 抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority		 = 3;	   // 子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd				 = ENABLE; // IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);								   // 根据指定的参数初始化VIC寄存器

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); // 开启串口接受中断
}

void USART1_IRQHandler() { }
