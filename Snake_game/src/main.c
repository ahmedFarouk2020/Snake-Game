/*
 * main.c
 *
 *  Created on: Sep 21, 2020
 *      Author: Farouk
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
// MCAL
#include "RCC_interface.h"
#include "DIO_interface.h"
#include "NVIC_interface.h"
#include "STK_interface.h"
#include "EXTI_interface.h"
#include "SPI_interface.h"
// HAL
#include "TFT_interface.h"

void main(void)
{
	/* RCC Init */
	RCC_voidInitSysClock();

	RCC_voidEnableClock(RCC_APB2,2);// GPIOA
	RCC_voidEnableClock(RCC_APB2,12);// SPI1

	/* DIO Init */
	MGPIO_voidSetPinDirection(GPIOA,4,OUTPUT_2MHZ_PP);// reset
	MGPIO_voidSetPinDirection(GPIOA,11,OUTPUT_2MHZ_PP);// A0
	MGPIO_voidSetPinDirection(GPIOA,5,OUTPUT_10MHZ_AF_PP);// clk
	MGPIO_voidSetPinDirection(GPIOA,7,OUTPUT_10MHZ_AF_PP);// MOSI
	// set callback
	EXTI_voidSetCallBack0(TFT_voidChooseDown);
	EXTI_voidSetCallBack1(TFT_voidChooseUp);
	EXTI_voidSetCallBack2(TFT_voidChooseRight);
	EXTI_voidSetCallBack3(TFT_voidChooseLeft);


	/* set EXTI pins as input pullup */
	MGPIO_voidSetPinDirection(GPIOA,0,INPUT_PULLUP_PULLDOWN);// down
	MGPIO_voidSetPinDirection(GPIOA,1,INPUT_PULLUP_PULLDOWN);// up
	MGPIO_voidSetPinDirection(GPIOA,2,INPUT_PULLUP_PULLDOWN);// right
	MGPIO_voidSetPinDirection(GPIOA,3,INPUT_PULLUP_PULLDOWN);// left
	MGPIO_voidSetPinValue(GPIOA,PIN0,HIGH);
	MGPIO_voidSetPinValue(GPIOA,PIN1,HIGH);
	MGPIO_voidSetPinValue(GPIOA,PIN2,HIGH);
	MGPIO_voidSetPinValue(GPIOA,PIN3,HIGH);

	/* systick Init */
	STK_voidInit();

	/* enable EXTI on line 0,1,2,3 => FALLING TRIGGER */
	EXTI_voidEnableExtInt(FALLING,0);
	EXTI_voidEnableExtInt(FALLING,1);
	EXTI_voidEnableExtInt(FALLING,2);
	EXTI_voidEnableExtInt(FALLING,3);

	/* enable EXTI0 ,EXTI1,EXTI2,EXTI3 from NVIC */
	MNVIC_voidEnableInterrupt(6);
	MNVIC_voidEnableInterrupt(7);
	MNVIC_voidEnableInterrupt(8);
	MNVIC_voidEnableInterrupt(9);

	/* SPI Init */
	SPI1_voidInit();

	/* TFT Init */
	TFT_voidInit();

	TFT_voidFillColor(0xFFFF);

	TFT_voidDrawRectangle(0,8,0,8,0x001F);

	TFT_voidRandomFood();
	while(1)
	{

		TFT_voidMoveUp();
		TFT_voidMoveRight();
		TFT_voidMoveDown();
		TFT_voidMoveLeft();
	}


}
