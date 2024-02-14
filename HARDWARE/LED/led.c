#include "led.h"

led_ctrl_t led0_ctrl;

void led0_on(void);
void led0_off(void);
void led0_toggle(void);
void led0_init(void);

void led_init(void) { led0_init(); }
///////////////////////////////////////////////////////// led0
void led0_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // 使能PB,PE端口时钟

	GPIO_InitStructure.GPIO_Pin	  = GPIO_Pin_4;		  // LED0-->PB.5 端口配置
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP; // 推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);			  // 根据设定参数初始化GPIOB.5
	GPIO_SetBits(GPIOB, GPIO_Pin_4);				  // PB.5 输出高

	led0_ctrl.on	 = led0_on;
	led0_ctrl.off	 = led0_off;
	led0_ctrl.toggle = led0_toggle;
}
void led0_on(void) { GPIO_ResetBits(LED0_PORT, LED0_PIN); }

void led0_off(void) { GPIO_SetBits(LED0_PORT, LED0_PIN); }

void led0_toggle(void)
{
	static uint8_t flag;
	BitAction	   action;
	flag   = !flag;
	action = (flag == 0) ? Bit_RESET : Bit_SET;
	GPIO_WriteBit(LED0_PORT, LED0_PIN, action);
}

////////////////////////////////////////////////////////////////// led1
