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

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // ʹ��PB,PE�˿�ʱ��

	GPIO_InitStructure.GPIO_Pin	  = GPIO_Pin_4;		  // LED0-->PB.5 �˿�����
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP; // �������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);			  // �����趨������ʼ��GPIOB.5
	GPIO_SetBits(GPIOB, GPIO_Pin_4);				  // PB.5 �����

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
