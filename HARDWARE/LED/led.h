#ifndef __LED_H
#define __LED_H
#include "stm32f10x.h"

///////////////////////////////////////////// led0
#define LED0_PORT GPIOB
#define LED0_PIN  GPIO_Pin_4
#define LED0_RCC  RCC_APB2Periph_GPIOA

typedef struct
{
	void (*on)(void);
	void (*off)(void);
	void (*toggle)(void);
} led_ctrl_t;

extern led_ctrl_t led0_ctrl;

void led_init(void);

#endif
