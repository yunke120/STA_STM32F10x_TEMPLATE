#include "led.h"
#include "usart1.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	usart1_init(115200);
	led_init();
	while (1)
	{
		app_printf("led test failed\r\n");
		led0_ctrl.toggle();
		delay_ms(1000);
	}
}
