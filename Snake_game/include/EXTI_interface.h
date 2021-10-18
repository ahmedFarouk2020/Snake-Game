/*********************************************************/
/* author  : Farouk                                      */
/* Version : v01                                         */
/* Date    : August 19 2020                              */
/*********************************************************/
#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

/* INT LINES */
#define EXTI_LINE0          0
#define EXTI_LINE1          1
#define EXTI_LINE2          2
#define EXTI_LINE3          3
#define EXTI_LINE4          4
#define EXTI_LINE5          5
#define EXTI_LINE6          6
#define EXTI_LINE7          7
#define EXTI_LINE8          8
#define EXTI_LINE9          9
#define EXTI_LINE10         10
#define EXTI_LINE11         11
#define EXTI_LINE12         12
#define EXTI_LINE13         13
#define EXTI_LINE14         14
#define EXTI_LINE15         15
/* TRIGGER MODE */
#define RISSING       0
#define FALLING       1
#define ON_CHANGE     2

/* intialize EXT line -> enable and set trigger mode of the line from config file */
void EXTI_voidInit(void);
/* enable interrupt on EXT line */
void EXTI_voidEnableExtInt( u8 Copy_u8TrigMode , u8 Copy_u8LineInt);
/* disable interrupt on EXT line */
void EXTI_voidDisableEXTI(u8 Copy_u8EXTILine);
/* specify trigger mode of EXT line */
void EXTI_voidSetTrigMode(u8 Copy_u8TrigMode , u32 Copy_u32LineInt);
/* generate SW trigger on EXT line */
void EXTI_voidGeneratSwInt(u32 Copy_u32LineInt);
/* read pending flag of EXT line */
u8   EXTI_u8GetPF(u32 Copy_u32LineInt);

void EXTI_voidSetCallBack0(void (*ptr) (void));
void EXTI_voidSetCallBack1(void (*ptr) (void));
void EXTI_voidSetCallBack2(void (*ptr) (void));
void EXTI_voidSetCallBack3(void (*ptr) (void));


#endif
