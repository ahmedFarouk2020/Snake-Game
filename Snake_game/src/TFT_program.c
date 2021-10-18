/*********************************************************/
/* author  : Farouk                                      */
/* Version : v01                                         */
/* Date    : Sept 21 2020                                */
/*********************************************************/

/*
 * problems:
 * 1- change positions and value of delays for user-friendly(usability) issues
 * 2- try to get the unpredictable delays in RANDOM FOOD function
 * 3- add lose function if you step over the tail
 */

#include <stdlib.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "STK_interface.h"
#include "SPI_interface.h"

#include "TFT_interface.h"
#include "TFT_private.h"
#include "TFT_config.h"

// Directions
volatile u8 up=1;
volatile u8 down;
volatile u8 left;
volatile u8 right;

u8 globalScore=0;// number of pieces eaten

// food coordinates
u8 x2Rand = 0;
u8 y2Rand = 0;

// initial coordinates of the snake
u8 x1=0; u8 x2=8; u8 y1=0; u8 y2=8;
// previous coordinates
u8 prevX1=0;u8 prevX2=0;u8 prevY1=0;u8 prevY2=0;
// array of coordinates (can be done using LL or struct)
//tail coordinates
u8 x1Arr[9] = {0};
u8 x2Arr[9] = {8};
u8 y1Arr[9] = {0};
u8 y2Arr[9] = {8};

void TFT_voidInit(void)
{
	/* reset pulse */
	MGPIO_voidSetPinValue(TFT_RESET_PIN,HIGH);
	STK_voidSetBusyWait(100);
	MGPIO_voidSetPinValue(TFT_RESET_PIN,LOW);
	STK_voidSetBusyWait(1);
	MGPIO_voidSetPinValue(TFT_RESET_PIN,HIGH);
	STK_voidSetBusyWait(100);
	MGPIO_voidSetPinValue(TFT_RESET_PIN,LOW);
	STK_voidSetBusyWait(100);
	MGPIO_voidSetPinValue(TFT_RESET_PIN,HIGH);
	STK_voidSetBusyWait(120000);
	
	/* sleep out command */
	TFT_voidWriteCommand(0x11);
	
	/* wait 150 msec */
	STK_voidSetBusyWait(150000);
	
	/* color mode command */
	TFT_voidWriteCommand(0x3A);
	TFT_voidWriteData(0x05);
	
	/* display-on command */
	TFT_voidWriteCommand(0x29);
}

static void TFT_voidWriteCommand(u8 copy_u8Command)
{
	u8 Local_u8Temp;
	
	/* A0 is LOW */
	MGPIO_voidSetPinValue(TFT_A0_PIN,LOW);
	
	/* send command over SPI */
	SPI1_voidSendReceiveSync(copy_u8Command,&Local_u8Temp);
}

static void TFT_voidWriteData(u8 copy_u8Data)
{
	u8 Local_u8Temp;
	
	/* A0 is HIGH */
	MGPIO_voidSetPinValue(TFT_A0_PIN,HIGH);
	
	/* send data over SPI */
	SPI1_voidSendReceiveSync(copy_u8Data,&Local_u8Temp);
}

void TFT_voidFillColor(u16 color)
{
	u16 counter;
	u8 Data;

    /* set X address*/
	TFT_voidWriteCommand(0x2A);
	/* the beginning */
	TFT_voidWriteData(0); // 8 MSBs
	TFT_voidWriteData(0); // 8 LSBs
	/* the end */
	TFT_voidWriteData(0);
	TFT_voidWriteData(127);

	/* set Y address*/
	TFT_voidWriteCommand(0x2B);
	/* the beginning */
	TFT_voidWriteData(0);
	TFT_voidWriteData(0);
	/* the end */
	TFT_voidWriteData(0);
	TFT_voidWriteData(159);

	/* RAM Write */
	TFT_voidWriteCommand(0x2C);

    /* fill color */
	for(counter=0 ;counter<20480;counter++)
	{
		Data = color>> 8;

		/* Write the high byte */
		TFT_voidWriteData(Data);
		/* Write the low byte */
		Data = color & 0x00FF;
		TFT_voidWriteData(Data);
	}

}

void TFT_voidDrawRectangle(u8 x1, u8 x2, u8 y1, u8 y2 ,u16 color)
{
	u16 counter;
	u8 Data;

	u16 size = (x2-x1+1) * (y2-y1+1);// data validation is not specified

    /* set X address*/
	TFT_voidWriteCommand(0x2A);
	/* the beginning */
	TFT_voidWriteData(0);
	TFT_voidWriteData(x1);
	/* the end */
	TFT_voidWriteData(0);
	TFT_voidWriteData(x2);

	/* set Y address*/
	TFT_voidWriteCommand(0x2B);
	/* the beginning */
	TFT_voidWriteData(0);
	TFT_voidWriteData(y1);
	/* the end */
	TFT_voidWriteData(0);
	TFT_voidWriteData(y2);

	/* RAM Write */
	TFT_voidWriteCommand(0x2C);

    /* show shape */
	for(counter=0 ;counter<size;counter++)
	{
		Data = color>> 8;

		/* Write the high byte */
		TFT_voidWriteData(Data);
		/* Write the low byte */
		Data = color & 0x00FF;
		TFT_voidWriteData(Data);
	}

}

void TFT_voidDrawChar(u8 x1, u8 x2, u8 y1, u8 y2 ,u16* letter)
{
	u16 counter;
	u8 Data;

	u16 size = (x2-x1+1) * (y2-y1+1);

    /* set X address*/
	TFT_voidWriteCommand(0x2A);
	/* the beginning */
	TFT_voidWriteData(0);
	TFT_voidWriteData(x1);
	/* the end */
	TFT_voidWriteData(0);
	TFT_voidWriteData(x2);

	/* set Y address*/
	TFT_voidWriteCommand(0x2B);
	/* the beginning */
	TFT_voidWriteData(0);
	TFT_voidWriteData(y1);
	/* the end */
	TFT_voidWriteData(0);
	TFT_voidWriteData(y2);

	/* RAM Write */
	TFT_voidWriteCommand(0x2C);

    /* show img */
	for(counter=0 ;counter<size;counter++)
	{
		/* transfer data into 1 byte */
		    Data = letter[counter]>> 8;

		    /* Write the high byte */
		    TFT_voidWriteData(Data);

		    /* Write the low byte */
		    Data = letter[counter] & 0x00FF;
		    TFT_voidWriteData(Data);
	}
}

void TFT_voidMoveLeft(void)
{
	while(left == 1)
	{
		TFT_voidDrawRectangle(x1,x2,y1,y2,0xFFFF);//remove Rectangle
		TFT_voidRemoveTail(); // remove tail
		if(x2 >= 127)
		{
			u8 x2Edge = 0;// x2 of the rest of the snake when he reach the edge
			u8 x1Edge = 0;
			// previous coordinates
			prevX1=x1;prevX2=x2;prevY1=y1;prevY2=y2;
			while(x1<x2)
			{

				TFT_voidDrawRectangle(x1,x2,y1,y2,0xFFFF);//remove Rectangle
				x1+=8;
			/* draw the part of the snake which is at the edge */
				TFT_voidDrawRectangle(x1,x2,y1,y2,0x001F);
				x2Edge+=8;// error
			/* draw the part of the snake which left the edge and appeared at the beginning*/
				TFT_voidDrawRectangle(x1Edge,x2Edge,y1,y2,0x001F);
				STK_voidSetBusyWait(100000);

			}
			TFT_voidDrawRectangle(x1,x2,y1,y2,0xFFFF);//remove Rectangle
			x1 = 0;
			x2 = 8;
		}

		else
		{
			// previous coordinates
			prevX1=x1;prevX2=x2;prevY1=y1;prevY2=y2;
			x1+=8;
			x2+=8;
			TFT_voidDrawRectangle(x1,x2,y1,y2,0x001F);// draw Rectangle
			STK_voidSetBusyWait(90000);
		}
		// snake ate the food?
		if( ((x2 >= (x2Rand-8) && x2 <= x2Rand)||(x1 >= (x2Rand-8) && x1 <= x2Rand)) && ( (y2 <= y2Rand && y2 >= y2Rand-8)||(y1 <= y2Rand && y1 >= y2Rand-8)) )
		{
			globalScore++;
			TFT_voidRandomFood();
			TFT_voidDrawTail();
			STK_voidSetBusyWait(100000);
			//globalScore++;
		}
		else
		{
			if(globalScore >0)
			{
				TFT_voidDrawTail();
				STK_voidSetBusyWait(90000);
			}
		}
	}
}

void TFT_voidMoveUp(void)
{
	while(up == 1)
	{
		TFT_voidDrawRectangle(x1,x2,y1,y2,0xFFFF);//remove Rectangle
		// remove tail
		TFT_voidRemoveTail();

		if(y2 >= 159)//-----
		{
			u8 y2Edge = 0;// y2 of the rest of the snake when he reach the top edge
			u8 y1Edge = 0;
			// previous coordinates
			prevX1=x1;prevX2=x2;prevY1=y1;prevY2=y2;
			while(y1<y2)
			{
				TFT_voidDrawRectangle(x1,x2,y1,y2,0xFFFF);//remove Rectangle

				y1+=8;//-----
			/* draw the part of the snake which is at the top edge */
				TFT_voidDrawRectangle(x1,x2,y1,y2,0x001F);

				y2Edge+=8;//-----
			/* draw the part of the snake which left the edge and appeared at the beginning*/
				TFT_voidDrawRectangle(x1,x2,y1Edge,y2Edge,0x001F);     //*************
				STK_voidSetBusyWait(100000);


			}
			TFT_voidDrawRectangle(x1,x2,y1,y2,0xFFFF);//remove Rectangle
			y1 = 0;
			y2 = 8;
		}

		else
		{
			// previous coordinates
			prevX1=x1;prevX2=x2;prevY1=y1;prevY2=y2;
			y1+=8;//-----
			y2+=8;//-----
			TFT_voidDrawRectangle(x1,x2,y1,y2,0x001F);// draw Rectangle
			STK_voidSetBusyWait(90000);
		}
		// snake ate the food?
		if( ((x2 >= (x2Rand-8) && x2 <= x2Rand)||(x1 >= (x2Rand-8) && x1 <= x2Rand)) && ( (y2 <= y2Rand && y2 >= y2Rand-8)||(y1 <= y2Rand && y1 >= y2Rand-8)))
		{
			globalScore++;
			TFT_voidRandomFood();
			TFT_voidDrawTail();
			STK_voidSetBusyWait(100000);
			//globalScore++;
		}
		else
		{
			if(globalScore >0)
			{
				TFT_voidDrawTail();
				STK_voidSetBusyWait(90000);
			}
		}
	}
}

void TFT_voidMoveDown(void)
{
	while(down == 1)
	{
		TFT_voidDrawRectangle(x1,x2,y1,y2,0xFFFF);//remove Rectangle
		TFT_voidRemoveTail(); // remove
		if( (u8)(y1-8) >= (u8)(160) )//********
		{
			// previous coordinates
			prevY1=y1;prevY2=y2;
			y1 = 159-8;
			y2 = 159;
			TFT_voidDrawRectangle(x1,x2,y1,y2,0x001F);//draw Rectangle
			STK_voidSetBusyWait(100000);
		}

		else
		{
			// previous coordinates
			prevX1=x1;prevX2=x2;prevY1=y1;prevY2=y2;
			y1-=8;
			y2-=8;
			TFT_voidDrawRectangle(x1,x2,y1,y2,0x001F);// draw Rectangle
			STK_voidSetBusyWait(90000);
		}
		// snake ate the food?
		if( ((x2 >= (x2Rand-8) && x2 <= x2Rand)||(x1 >= (x2Rand-8) && x1 <= x2Rand)) && ( (y2 <= y2Rand && y2 >= y2Rand-8)||(y1 <= y2Rand && y1 >= y2Rand-8)) )//*********
		{
			globalScore++;
			TFT_voidRandomFood();
			TFT_voidDrawTail();
			STK_voidSetBusyWait(100000);
			//globalScore++;
		}
		else
		{
			if(globalScore > 0){
				TFT_voidDrawTail();
				STK_voidSetBusyWait(90000);
			}
		}
	}
}

void TFT_voidMoveRight(void)
{
	while(right == 1)
	{
		TFT_voidDrawRectangle(x1,x2,y1,y2,0xFFFF);//remove Rectangle
		TFT_voidRemoveTail(); // remove
		if( (u8)(x1-8) >= (u8)(128) )//********
		{
			// previous coordinates
			prevX1=x1;prevX2=x2;prevY1=y1;prevY2=y2;
			x1 = 119;
			x2 = 127;
			TFT_voidDrawRectangle(x1,x2,y1,y2,0x001F);//draw Rectangle
			STK_voidSetBusyWait(100000);
		}

		else
		{
			// previous coordinates
			prevX1=x1;prevX2=x2;prevY1=y1;prevY2=y2;
			x1-=8;//***************
			x2-=8;//***************
			TFT_voidDrawRectangle(x1,x2,y1,y2,0x001F);// draw Rectangle
			STK_voidSetBusyWait(90000);
		}
		// snake ate the food?
		if( ((x2 >= (x2Rand-8) && x2 <= x2Rand)||(x1 >= (x2Rand-8) && x1 <= x2Rand)) && ( (y2 <= y2Rand && y2 >= y2Rand-8)||(y1 <= y2Rand && y1 >= y2Rand-8)) )
		{
			globalScore++;
			TFT_voidRandomFood();
			TFT_voidDrawTail();
			STK_voidSetBusyWait(100000);
			//globalScore++;
		}
		else
		{
			if(globalScore > 0){
				TFT_voidDrawTail();
				STK_voidSetBusyWait(90000);
			}
		}
	}
}

void TFT_voidChooseLeft(void)
{
	if(left || up || down){
		left  = 1;
		up    = 0;
		down  = 0;
		right = 0;
	}
}
void TFT_voidChooseRight(void)
{
	if(right || up || down){
		left  = 0;
		up 	  = 0;
		down  = 0;
		right = 1;
	}
}
void TFT_voidChooseUp(void)
{
	if(right || up || left){
		up 	  = 1;
		left  = 0;
		down  = 0;
		right = 0;
	}
}
void TFT_voidChooseDown(void)
{
	if(right || down || left){
		up 	  = 0;
		left  = 0;
		down  = 1;
		right = 0;
	}
}

void TFT_voidRandomFood(void)
{
	// remove previous food piece                 white
	TFT_voidDrawRectangle(x2Rand-8, x2Rand, y2Rand-8, y2Rand, 0xFFFF);
	static u8 color = 0x00;// black
	// random x
	x2Rand = rand()%128;
	u8 x1 = x2Rand-8;
	// random y
	y2Rand = rand()%160;
	u8 y1 = y2Rand-8;
	// draw the food
	TFT_voidDrawRectangle(x1, x2Rand, y1, y2Rand, color);
}

// increase size and draw tails
void TFT_voidDrawTail(void)
{
	if(globalScore>8){globalScore = 8;}// max score = 8
	// array of coordinates (can be done using LL or struct)
	if(globalScore > 0){
		// assign tail coordinate to arrays
		for(s8 i=globalScore; i>0; i--){
			x1Arr[i] = x1Arr[i-1];
			x2Arr[i] = x2Arr[i-1];
			y1Arr[i] = y1Arr[i-1];
			y2Arr[i] = y2Arr[i-1];
		}
		// assign prev coordinates to arrs[0]
		// tail_1 coordinates
		x1Arr[0] = prevX1;
		x2Arr[0] = prevX2;
		y1Arr[0] = prevY1;
		y2Arr[0] = prevY2;
	}
	else{
		// tail_1 coordinates
		x1Arr[0] = prevX1;
		x2Arr[0] = prevX2;
		y1Arr[0] = prevY1;
		y2Arr[0] = prevY2;
		// draw 1 tail
		TFT_voidDrawRectangle(x1Arr[0], x2Arr[0], y1Arr[0], y2Arr[0], 0x001F);
	}
	// draw tails
	for(u8 i=0; i<globalScore; i++){
		TFT_voidDrawRectangle(x1Arr[i], x2Arr[i], y1Arr[i], y2Arr[i], 0x001F);
	}
}
// remove tail
void TFT_voidRemoveTail(void){
	// remove tails
	for(u8 i=0; i<globalScore; i++){
		TFT_voidDrawRectangle(x1Arr[i], x2Arr[i], y1Arr[i], y2Arr[i], 0xFFFF);
	}
}
