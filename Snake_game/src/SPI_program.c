/*********************************************************/
/* author  : Farouk                                      */
/* Version : v02                                         */
/* Date    : Sept 16 2020                                */
/*********************************************************/
/*   SPI1     */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "SPI_interface.h"
#include "SPI_private.h"
#include "SPI_config.h"

void (*SPI_CallBack)(u8);

void SPI1_voidInit(void)
{
	/* disable SPI1 */
//	CLR_BIT(SPI1->CR1,6);
    
	/* MSB first   BR=FREQ/2   Master   clk phase =1   clk polarity=1 */
	SPI1->CR1 = 0x0347;
	
	/* enable SPI1 */
//	SET_BIT(SPI1->CR1,6);
}

void SPI1_voidSendReceiveSync(u8 copy_u8DataToTrans , u8* copy_u8pDataToRecv)
{
	/* clear slave select pin */
	MGPIO_voidSetPinValue(SPI1_SLAVE_PIN,LOW);
	
	/* Send Data */
	SPI1-> DR = copy_u8DataToTrans;
	
	/* wait Busy flag */
	while(GET_BIT(SPI1->SR ,7) == 1);
	
	/* return to received data */
	*copy_u8pDataToRecv = SPI1->DR ;
	
	/* Set Slave select pin */
	MGPIO_voidSetPinValue(SPI1_SLAVE_PIN,HIGH);
}

void SPI1_voidSendReceiveAsync(u8 copy_u8DataToTrans , void (*copy_CallBack)(u8) )
{
	/* clear slave select pin */
	MGPIO_voidSetPinValue(SPI1_SLAVE_PIN,LOW);
	
	/* Send Data */
	SPI1-> DR = copy_u8DataToTrans;
	
	/* set callback */
	SPI_CallBack = copy_CallBack;
	
	/* Set Slave select pin */
	MGPIO_voidSetPinValue(SPI1_SLAVE_PIN,HIGH);
}

void SPI1_IRQHandler()
{
	SPI_CallBack(SPI1->DR);
}
