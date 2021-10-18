/*********************************************************/
/* author  : Farouk                                      */
/* Version : v01                                         */
/* Date    : August 19 2020                              */
/*********************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_config.h"

#define NULL     ((void*)0x00)

static void (* EXTI0_CallBack) (void) = NULL ;
static void (* EXTI1_CallBack) (void) = NULL ;
static void (* EXTI2_CallBack) (void) = NULL ;
static void (* EXTI3_CallBack) (void) = NULL ;

void	EXTI0_IRQHandler(void)
{
	EXTI0_CallBack();
	SET_BIT(EXTI -> PR , 0);
}

void	EXTI1_IRQHandler(void)
{
	EXTI1_CallBack();
	SET_BIT(EXTI -> PR , 1);
}

void	EXTI2_IRQHandler(void)
{
	EXTI2_CallBack();
	SET_BIT(EXTI -> PR , 2);
}

void	EXTI3_IRQHandler(void)
{
	EXTI3_CallBack();
	SET_BIT(EXTI -> PR , 3);
}

void EXTI_voidInit(void)
{
	#if		EXTI_LINE == EXTI_LINE0
			SET_BIT(EXTI -> IMR , EXTI_LINE0 );
	#elif	EXTI_LINE == EXTI_LINE1
			SET_BIT(EXTI -> IMR , EXTI_LINE1 );
	#elif	EXTI_LINE == EXTI_LINE2
			SET_BIT(EXTI -> IMR , EXTI_LINE2 );
	#else
		#error ("Wrong Externl Interrupt Line !")
	#endif
	
	
	#if		EXTI_TRIG_MODE == FALLING
			SET_BIT(EXTI -> FTSR , EXTI_LINE);
	#elif	EXTI_TRIG_MODE == RISING
			SET_BIT(EXTI -> RTSR , EXTI_LINE);
	#elif	EXTI_TRIG_MODE == ON_CHANGE
			SET_BIT(EXTI -> RTSR , EXTI_LINE);
			SET_BIT(EXTI -> FTSR , EXTI_LINE);
	#else
		#error ("Wrong External Interrupt Sense Mode !")
	#endif
}



void EXTI_voidEnableExtInt( u8 Copy_u8TrigMode , u8 Copy_u8LineInt)
{
	switch(Copy_u8TrigMode)
	{
		case	RISSING		:	SET_BIT(EXTI -> RTSR , Copy_u8LineInt);	break;
		case	FALLING		:	SET_BIT(EXTI -> FTSR , Copy_u8LineInt);	break;
		case	ON_CHANGE	:	SET_BIT(EXTI -> RTSR , Copy_u8LineInt);
								SET_BIT(EXTI -> FTSR , Copy_u8LineInt);	break;
	}
	SET_BIT(EXTI->IMR , Copy_u8LineInt);
}

void EXTI_voidGeneratSwInt(u32 Copy_u32LineInt)
{
	EXTI -> SWIER = (1 << Copy_u32LineInt);
}

u8   EXTI_u8GetPF(u32 Copy_u32LineInt)
{
	//u8 Local_u8PendingVal = (1 << Copy_u32LineInt);
	return GET_BIT(EXTI -> PR , Copy_u32LineInt);
}

void EXTI_voidDisableEXTI(u8 Copy_u8EXTILine)
{
	CLR_BIT(EXTI -> IMR , Copy_u8EXTILine);
}

void EXTI_voidSetCallBack0(void (*ptr) (void))
{
	EXTI0_CallBack = ptr ;
}

void EXTI_voidSetCallBack1(void (*ptr) (void))
{
	EXTI1_CallBack = ptr ;
}

void EXTI_voidSetCallBack2(void (*ptr) (void))
{
	EXTI2_CallBack = ptr ;
}

void EXTI_voidSetCallBack3(void (*ptr) (void))
{
	EXTI3_CallBack = ptr ;
}
