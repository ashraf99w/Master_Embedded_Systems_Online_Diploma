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


#include "Stm32_F103C6_GPIO_Driver.h"
#include "Stm32_F103x6.h"



void clock_init(void)
{
	//Bit 2 IOPAEN: IO port A clock enable
	//Set and cleared by software.
	//0: IO port A clock disabled
	//1: IO port A clock enabled
	RCC_GPIOA_EN();

	//Bit 3 IOPBEN: IO port B clock enable
	//Set and cleared by software.
	//0: IO port B clock disabled
	//1: IO port B clock enabled
	RCC_GPIOB_EN();
}

void Gpio_init(void)
{
	//PA1 INPUT HIGH Z FLOATING INPUT
	GPIO_PinConfig_t PINCFG;
	PINCFG.GPIO_PinNumber=GPIO_Pin_1;
	PINCFG.GPIO_Mode=GPIO_Mode_INPUT_FLI;
	MCAL_GPIO_Init(GPIOA,&PINCFG);


	//PB1 OUT PUT PUSH PULL
	PINCFG.GPIO_PinNumber=GPIO_Pin_1;
	PINCFG.GPIO_Mode=GPIO_Mode_OUTPUT_PP;
	PINCFG.GPIO_output_speed=GPIO_speed_10M;
	MCAL_GPIO_Init(GPIOB,&PINCFG);


	//PA13 INPUT HIGH Z FLOATING INPUT
	PINCFG.GPIO_PinNumber=GPIO_Pin_13;
	PINCFG.GPIO_Mode=GPIO_Mode_INPUT_FLI;
	MCAL_GPIO_Init(GPIOA,&PINCFG);


	//PB1 OUT PUT PUSH PULL
	PINCFG.GPIO_PinNumber=GPIO_Pin_13;
	PINCFG.GPIO_Mode=GPIO_Mode_OUTPUT_PP;
	PINCFG.GPIO_output_speed=GPIO_speed_10M;
	MCAL_GPIO_Init(GPIOB,&PINCFG);


}


void wait(unsigned int x)

{
	unsigned int i,j;
	for(i=0;i<x;i++)
		for(j=0;j<255;j++);

}


int main(void)
{

	clock_init();
	Gpio_init();



	while(1)
	{

		if( MCAL_GPIO_ReadPin(GPIOA, GPIO_Pin_1) == 0) //pull-up true means pressed
		{
			MCAL_GPIO_TogglePin(GPIOB, GPIO_Pin_1);

			while(MCAL_GPIO_ReadPin(GPIOA, GPIO_Pin_1) == 0);//single press
		}

		if(MCAL_GPIO_ReadPin(GPIOA, GPIO_Pin_13)== 1)//pull-down true means pressed
		{
			MCAL_GPIO_TogglePin(GPIOB, GPIO_Pin_13);

		}
		wait(8);


	}

}


