/*
 * 
 */
#include "stm8s.h"
#include <stdio.h>

uint16_t ticks = 0;
uint16_t ticks_now = 0;
uint16_t ticks_last = 0;

uint16_t index = 0;

void UART1_SendString(char *s) {
	for (;*s!=0;s++) {
		while(!UART1_GetFlagStatus(UART1_FLAG_TXE));
		UART1_SendData8(*s);
	}
}

void delay(uint16_t i) {
	while (i--) {
	}
}

@far @interrupt void EXTI_PORTA_IRQHandler(void)
{
	ticks_now = ticks;
		
	if (ticks_now - ticks_last > 10000) {
		index = 0;
	}
	
	if (index%2) {
		sprintf(buf, "%u ", ticks_now - ticks_last);
	} else {
		sprintf(buf, "%u\n", ticks_now - ticks_last);
	}
	UART1_SendString(buf);

	index++;
	
	ticks_last = ticks_now;
}

@far @interrupt void TIM4_UPD_OVF_IRQHandler(void)
{
	TIM4_ClearFlag(TIM4_FLAG_UPDATE);
	ticks++;
}

main()
{
	// CPU: 16MHz
	CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);

	// UART1: ...
	UART1_DeInit();
	UART1_Init(115200, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO, UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TX_ENABLE|UART1_MODE_RX_DISABLE);
	
	// GPIOA.2: Pull-up input mode and enable interrupt
	GPIO_Init(GPIOA, GPIO_PIN_2, GPIO_MODE_IN_PU_IT);
	EXTI_DeInit();
	EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOA, EXTI_SENSITIVITY_RISE_FALL);

	// TIM4: Interrupt per 10us
	TIM4_DeInit();
	TIM4_TimeBaseInit(TIM4_PRESCALER_16, 10); // 16MHz / 16 = 1MHz, 1MHz / 10 = 100KHz, 100KHz = 10us
	TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);
	TIM4_Cmd(ENABLE);
	
	enableInterrupts();

	UART1_SendString("start...\n");

	while (1) {
		delay(30000);
	}
}

void assert_failed(u8* file, u32 line)
{
  while (1)
  {
  }
}
