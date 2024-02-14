#ifndef __USART1_H
#define __USART1_H

#include "stm32f10x.h"

#define USART1_PORT	  GPIOA
#define USART1_TX_PIN GPIO_Pin_9
#define USART1_RX_PIN GPIO_Pin_10
#define USART1_RCC	  RCC_APB2Periph_GPIOA

void usart1_init(uint32_t bound);
void usart1_enable_it(void);
#endif
