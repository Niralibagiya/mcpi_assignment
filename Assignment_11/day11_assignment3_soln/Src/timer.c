/*
Author: Nilesh Ghule <nilesh@sunbeaminfo.com>
Course: PG-DESD @ Sunbeam Infotech
Date: Sep 30, 2024
*/

#include <stdio.h>
#include "timer.h"
#include "i2c_lcd.h"
//#include "led.h"

void Timer_Init(uint32_t ms) {
	//* Enable Timer APB clock
	//RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
	RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
	//* Set Timer clock -- PCLK = TCLK = 16 MHz : * Set PR = 16000
	//TIM6->PSC = (PR-1);
	TIM7->PSC = (PR-1);
	//* Calculate number of clocks to count (CNT).
	uint32_t cnt = (TCLK / 1000) * ms / PR;
	//* Set CNT in ARR.
	//TIM6->ARR = (cnt-1);
	TIM7->ARR = (cnt-1);
	//* Reset Timer Counter to 0.
	//TIM6->CNT = 0;
	TIM7->CNT = 0;
	//* Enable Timer Interrupt in DIER.
	//TIM6->DIER |= TIM_DIER_UIE;
	TIM7->DIER |= TIM_DIER_UIE;
	//* Enable Timer Interrupt in NVIC.
	//NVIC_EnableIRQ(TIM6_DAC_IRQn);
	NVIC_EnableIRQ(TIM7_IRQn);
	//* Start Timer in CR1.
	//TIM6->CR1 |= TIM_CR1_CEN;
	TIM7->CR1 |= TIM_CR1_CEN;
}

void TIM7_IRQHandler(void)
{
	char str[32];

	//* Check if UIF flag is set (in SR).
	if(TIM7->SR & TIM_SR_UIF)
	{
		//* Clear UIF in SR (Ack)
		TIM7->SR &= ~TIM_SR_UIF;

		// increment the global count and write it in str to send it on i2c_lcd display.
		sprintf(str,"gCounter = %d",++gCounter);
		Lcd_WriteByte(LCD_CMD, LCD_CLEAR);
		Lcd_Puts(LCD_LINE1, str);
		//LedToggle(12);
		//LedToggle(13);
		//LedToggle(14);
		//LedToggle(15);
	}
}
