#include "utils.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define DEBUG_USART	 USART1
#define ENABLE_DEBUG 1

static u8  fac_us = 0; // us
static u16 fac_ms = 0; // ms

// THUMB指令不支持汇编内联
// 采用如下方法实现执行汇编指令WFI
void WFI_SET(void) { __ASM volatile("wfi"); }
// 关闭所有中断
void INTX_DISABLE(void) { __ASM volatile("cpsid i"); }
// 开启所有中断
void INTX_ENABLE(void) { __ASM volatile("cpsie i"); }
// 设置栈顶地址
// addr:栈顶地址
// clang-format off
__asm void MSR_MSP(u32 addr)
{
	MSR	MSP, r0 // set Main Stack value
	BX r14
}
// clang-format on

int fputc(int ch, FILE *f)
{
	while ((DEBUG_USART->SR & 0X40) == 0)
	{
	}; // 循环发送,直到发送完毕
	DEBUG_USART->DR = (u8)ch;
	return ch;
}

void app_printf(const char *fmt, ...)
{
#if ENABLE_DEBUG
	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
#endif
}

void delay_init()
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	fac_us = SystemCoreClock / 8000000;
	fac_ms = (u16)fac_us * 1000;
}

void delay_us(u32 nus)
{
	u32 temp;
	SysTick->LOAD  = nus * fac_us;
	SysTick->VAL   = 0x00;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	do
	{
		temp = SysTick->CTRL;
	} while ((temp & 0x01) && !(temp & (1 << 16)));
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
	SysTick->VAL   = 0X00;
}

void delay_ms(u16 nms)
{
	u32 temp;
	SysTick->LOAD  = (u32)nms * fac_ms;
	SysTick->VAL   = 0x00;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	do
	{
		temp = SysTick->CTRL;
	} while ((temp & 0x01) && !(temp & (1 << 16)));
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
	SysTick->VAL   = 0X00;
}
