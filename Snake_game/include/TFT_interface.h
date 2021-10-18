/*********************************************************/
/* author  : Farouk                                      */
/* Version : v01                                         */
/* Date    : Sept 21 2020                                */
/*********************************************************/

#ifndef TFT_INTERFACE_H
#define TFT_INTERFACE_H

void TFT_voidInit(void);

void TFT_voidFillColor(u16 color);
/* ( x -> 0:127 & x1<x2 )  AND  ( y -> 0:159 & y1<y2 ) */
void TFT_voidDrawRectangle(u8 x1, u8 x2, u8 y1, u8 y2 ,u16 color);

/* ( x -> 0:127 & x1<x2 )  AND  ( y -> 0:159 & y1<y2 ) */
void TFT_voidDrawChar(u8 x1, u8 x2, u8 y1, u8 y2 ,u16* letter);

void TFT_voidMoveUp(void);
void TFT_voidMoveDown(void);
void TFT_voidMoveLeft(void);
void TFT_voidMoveRight(void);

void TFT_voidChooseLeft(void);
void TFT_voidChooseRight(void);
void TFT_voidChooseUp(void);
void TFT_voidChooseDown(void);
// draw a rectangle at random coordinates(make some variable random to be changed)
void TFT_voidRandomFood(void);
// check if the snake pass on the food and increase its size and alter random food
//void TFT_voidSnakeSize(void);
// check if the snake pass on the food inside motion functions: done
// when call size function
// DrawTail function (shared variables)
void TFT_voidDrawTail(void);
// remove previous tail
void TFT_voidRemoveTail(void);
#endif
