/*
Author: Nilesh Ghule <nilesh@sunbeaminfo.com>
Course: PG-DESD @ Sunbeam Infotech
Date: Sep 30, 2024
*/


#include "timer.h"

void Timer_Init(void) {
	//* Enable Timer APB clock(set APB1ENR.5)
	//RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
	RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
	//* Set Timer clock -- PCLK = TCLK = 16 MHz : * Set PR = 16000
	//TIM6->PSC = (PR-1);
	TIM7->PSC = (PR-1);
}

void Timer_Delay(uint32_t ms) {
	//* Calculate number of clocks to count (CNT).
	uint32_t cnt = (TCLK / 1000) * ms / PR;
	//* Set CNT in ARR.
	//TIM6->ARR = cnt - 1;
	TIM7->ARR = cnt - 1;
	//* Reset Timer Counter to 0.
	//TIM6->CNT = 0;
	TIM7->CNT = 0;
	//* Start Timer in CR1.
	//TIM6->CR1 |= TIM_CR1_CEN;
	TIM7->CR1 |= TIM_CR1_CEN;
	//* Wait for UIF flag (in SR).
	//while(!(TIM6->SR & TIM_SR_UIF));
	while(!(TIM7->SR & TIM_SR_UIF));
	//* Clear UIF in SR
	//TIM6->SR &= ~TIM_SR_UIF;
	TIM7->SR &= ~TIM_SR_UIF;
	//* Stop Timer in CR1.
	//TIM6->CR1 &= ~TIM_CR1_CEN;
	TIM7->CR1 &= ~TIM_CR1_CEN;
}

