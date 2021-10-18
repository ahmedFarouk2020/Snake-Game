/*********************************************************/
/* author  : Farouk                                      */
/* Version : v02                                         */
/* Date    : Sept 16 2020                                */
/*********************************************************/

#ifndef SPI_INTERFACE_H
#define SPI_INTERFACE_H
/* configure SPI */
void SPI1_voidInit(void);
/* send and receive sync (polling) */
void SPI1_voidSendReceiveSync(u8 copy_u8DataToTrans , u8* copy_u8pDataToRecv);
/* send and receive async (interrupt) */
//void SPI1_voidSendReceiveAsync(u8 copy_u8DataToTrans , void (*CallBack)(u8));

#endif
