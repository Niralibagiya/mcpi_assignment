/*
 * systick.c
 *
 *  Created on: Oct 11, 2024
 *      Author: niralisoni
 */
#include "stm32f4xx.h"
#include "led.h"
#include "systick.h"

volatile uint32_t jiffies = 0;
void SysTick_Handler(void) {
	jiffies++;
	//GPIOD->ODR ^= BV(LED_RED_PIN); // ---> Oscilloscope/Analyzer
}
void SysTick_Delay(uint32_t ms) {
	uint32_t until = jiffies + ms;
	while(jiffies < until)

