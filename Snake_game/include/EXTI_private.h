/*********************************************************/
/* author  : Farouk                                      */
/* Version : v01                                         */
/* Date    : August 19 2020                              */
/*********************************************************/
#ifndef EXTI_PRIVATE_H
#define EXTI_PRIVATE_H

typedef struct {
/* ENABLE INT REQ AND EVENT */   
    volatile u32 IMR;	
    volatile u32 EMR;
/* ENABLE TRIGGER MODE */	
	volatile u32 RTSR;
	volatile u32 FTSR;
/* GENERATE REQ BY SW AND CHECK THE PENDING FLAGS */	
	volatile u32 SWIER;
	volatile u32 PR;
}EXTI_R;

#define EXTI           ((EXTI_R *)0x40010400)


#endif
