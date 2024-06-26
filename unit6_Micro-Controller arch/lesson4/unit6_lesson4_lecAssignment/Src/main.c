/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


typedef volatile unsigned int vuint32_t ;
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

// register address
#define GPIOA_BASE 0x40010800
#define GPIOA_CRH *(vuint32_t *)(GPIOA_BASE + 0x04)
#define GPIOA_CRL *(vuint32_t *)(GPIOA_BASE + 0x0)
#define GPIOA_ODR *(vuint32_t *)(GPIOA_BASE + 0x0C)

#define RCC_BASE 0x40021000
//APB2 peripheral clock enable register (RCC_APB2ENR)
#define RCC_APB2ENR *(vuint32_t *)(RCC_BASE+ 0x18)
#define RCC_CFGR *(vuint32_t *)(RCC_BASE+ 0x04)

//EXTI
#define EXTI_base 0x40010400
//Interrupt mask register (EXTI_IMR)
#define EXTI_IMR *(vuint32_t *)(EXTI_base+ 0x00)
//Rising trigger selection register (EXTI_RTSR)
#define EXTI_RTSR *(vuint32_t *)(EXTI_base+ 0x08)
//Pending register (EXTI_PR)
#define EXTI_PR *(vuint32_t *)(EXTI_base+ 0x14)


//AFIO
#define AFIO_base 0x40010000
//External interrupt configuration register 1 (AFIO_EXTICR1)
#define AFIO_EXTICR1 *(vuint32_t *)(AFIO_base+ 0x18)

//NVIC INTERRUPT ENABLE
#define NVIC_EXTIE0 *(vuint32_t *)(0xE000E100)


void clock_init(void)
{
	//		Bit 2 IOPAEN: IO port A clock enable
	//		Set and cleared by software.
	//		0: IO port A clock disabled
	//		1: IO port A clock enabled
	RCC_APB2ENR |=(1<<2);

//	Bit 0 AFIOEN: Alternate function IO clock enable
//	Set and cleared by software.
//	0: Alternate Function IO clock disabled
//	1: Alternate Function IO clock enabled
	RCC_APB2ENR |=(1<<0);

}


void Gpio_init(void)
{
	//pin 13 in port a to be output
	//Init GPIOA
	GPIOA_CRH &= 0xFF0FFFFF;
	GPIOA_CRH |= 0x00200000;
	//pin0 in port a to be floating
	GPIOA_CRL |=(1<<2);

}

int main(void)
{

	clock_init();
	Gpio_init();
		//	Bits 15:0 EXTIx[3:0]: EXTI x configuration (x= 0 to 3)
		//	These bits are written by software to select the source input for EXTIx external interrupt.
		//	Refer to Section 10.2.5: External interrupt/event line mapping
		//	0000: PA[x] pin
		//	0001: PB[x] pin
		//	0010: PC[x] pin
		//	0011: PD[x] pin
		//	0100: PE[x] pin
		//	0101: PF[x] pin
		//	0110: PG[x] pin

		AFIO_EXTICR1=0;

	//	Bits 19:0 MRx: Interrupt Mask on line x
	//	0: Interrupt request from Line x is masked
	//	1: Interrupt request from Line x is not masked
	//to enable line 0 for pin 0
	EXTI_IMR |=(1<<0);

	//	 TRx: Rising trigger event configuration bit of line x
	//	0: Rising trigger disabled (for Event and Interrupt) for input line
	//	1: Rising trigger enabled (for Event and Interrupt) for input line.
	//to enable rising_edge for line 0 for pin 0
	EXTI_RTSR |=(1<<0);

	//Enable IRQ6 of line0
	NVIC_EXTIE0 |=(1<<6);


	while(1);

}

void EXTI0_IRQHandler(void)
{
	//toggle pin 13 in port A Every IRQ
	GPIOA_ODR ^=(1<<13);
	//TO CLEAR THE Interrupt request signal or line 0
	EXTI_PR |=(1<<0);
}









