/*********************************************************/
/* author  : Farouk                                      */
/* Version : v01                                         */
/* Date    : Sept 21 2020                                */
/*********************************************************/

#ifndef TFT_CONFIG_H
#define TFT_CONFIG_H

/* write pin in pair port,pin */
#define TFT_A0_PIN      GPIOA,11
#define TFT_RESET_PIN   GPIOA,4

/* Directions */
#define LEFT        0
#define RIGHT       1
#define UP          2
#define DOWN        3

#endif
/*

 void TFT_voidMoveUp(void)
{

	up[1]=1;

	if(down[1] == 1)
	{
		down[0]=1;
		down[1]=0;
	}
	else
	{
		down[0]=down[1]=0;
	}

	if(left[1] == 1)
	{
		left[0]=1;
		left[1]=0;
	}
	else
	{
		left[0]=left[1]=0;
	}

	if(right[1] == 1)
	{
		right[0]=1;
		right[1]=0;
	}
	else
	{
		right[0]=right[1]=0;
	}
}

void TFT_voidMoveDown(void)
{

	down[1]=1;

	if(up[1] == 1)
	{
		up[0]=1;
		up[1]=0;
	}
	else
	{
		up[0]=up[1]=0;
	}

	if(left[1] == 1)
	{
		left[0]=1;
		left[1]=0;
	}
	else
	{
		left[0]=left[1]=0;
	}

	if(right[1] == 1)
	{
		right[0]=1;
		right[1]=0;
	}
	else
	{
		right[0]=right[1]=0;
	}
}

void TFT_voidMoveRight(void)
{

	right[1]=1;

		if(down[1] == 1)
		{
			down[0]=1;
			down[1]=0;
		}
		else
		{
			down[0]=down[1]=0;
		}

		if(left[1] == 1)
		{
			left[0]=1;
			left[1]=0;
		}
		else
		{
			left[0]=left[1]=0;
		}

		if(up[1] == 1)
		{
			up[0]=1;
			up[1]=0;
		}
		else
		{
			up[0]=up[1]=0;
		}
}

void TFT_voidMoveLeft(void)
{

	left[1]=1;

		if(down[1] == 1)
		{
			down[0]=1;
			down[1]=0;
		}
		else
		{
			down[0]=down[1]=0;
		}

		if(up[1] == 1)
		{
			up[0]=1;
			up[1]=0;
		}
		else
		{
			up[0]=up[1]=0;
		}

		if(right[1] == 1)
		{
			right[0]=1;
			right[1]=0;
		}
		else
		{
			right[0]=right[1]=0;
		}
}

u8 TFT_u8PreviousMovement(void)
{
	if(left[0] == 1)
	{
		return LEFT;
	}
	else if(up[0] == 1)
	{
		return UP;
	}
	else if(down[0] == 1)
	{
		return DOWN;
	}
	else if(right[0] == 1)
	{
		return RIGHT;
	}
	else
	{
		return 1;
	}

}

void test(void)
{
	if(x2 > 127)
	{
		x2=15;
		x1=0;
	}
	// clear the snake
	TFT_voidDrawRectangle(x1,x2,y1,y2,0xFFFF);
	x1++;
	x2++;
	// draw the new coordinates
	TFT_voidDrawRectangle(x1,x2,y1,y2,0x0000);
}

void TFT_voidMoveSnake(void)
{
	previousMovement = TFT_u8PreviousMovement();

	while(up[1] == 1)
	{
		if(previousMovement == UP)
		{
			TFT_voidDrawRectangle(x1,x2,y1,y2,0x001F);
			y1++;
			y2++;
		}
		else if(previousMovement == LEFT)
		{
			// coordinate of HEAD
			x1Head = x2-7-(y2-y1);
			x2Head = x2-7;
			y1Head = y2;
			y2Head = y2-7;

			if(x1 == x1Head)
			{
				TFT_voidDrawRectangle(x1Head ,x2Head ,y1 ,y2Head,0x001F);
				y2Head++;
				y1--;
			}

			else
			{
				TFT_voidDrawRectangle(x1,x2Head,y1,y2,0x001F);// tail
				TFT_voidDrawRectangle(x1Head ,x2Head ,y2,y2Head,0x001F);// head
				y2Head++;
				x1--;
			}
		}
		else if(previousMovement == RIGHT)
		{
			u8 x1Tail = x1 + 7;
			x2Head = x1+(y2-y1);
			y2Head = y2 +7;

			if(x2 == x2Head)
			{
				TFT_voidDrawRectangle(x1Tail ,x2Head ,y1 ,y2Head,0x001F);
				y2Head++;
				y1--;
			}

			else
			{
				TFT_voidDrawRectangle(x1Tail,x2,y1,y2,0x001F);// tail
				TFT_voidDrawRectangle(x1Tail ,x2Head ,y2 , y2Head,0x001F);// head
				y2Head++;
				x2Head--;
			}
		}
	}

	while(down[1] == 1)
	{
		if(previousMovement == DOWN)
		{
			TFT_voidDrawRectangle(x1,x2,y1,y2,0x001F);
			y1--;
			y2--;
		}
		else if(previousMovement == LEFT)
		{
			// coordinate of HEAD
			x1Head = x2-7-(y2-y1);
			x2Head = x2-7;
			y2Head = y1;
			y1Head = y1-7;
			if(x1 == x1Head)
			{
				TFT_voidDrawRectangle(x1Head ,x2Head ,y1Head ,y1Head+15 ,0x001F);
				y2Head--;
				y1Head--;
			}

			else
			{
				TFT_voidDrawRectangle(x1,x2Head,y1,y2,0x001F);// tail
				TFT_voidDrawRectangle(x1Head ,x2Head ,y1Head,y2Head,0x001F);// head
				y1Head--;
				x1++;
			}
		}
		else if(previousMovement == RIGHT)
		{
			// coordinate of HEAD
			x1Head = x1+7;// x1Tail
			x2Head = x1+7 + y2-y1;
			y2Head = y1+7;
			y1Head = y1;

			if(x2 == x2Head)// this case is incorrect in the other cases
			{
				TFT_voidDrawRectangle(x1Head ,x2Head ,y1Head ,y1Head+15 ,0x01F);
				y1Head++;

			}

			else
			{
				TFT_voidDrawRectangle(x1Head,x2,y1,y2,0x001F);// tail
				TFT_voidDrawRectangle(x1Head ,x2Head ,y1Head , y2Head,0x001F);// head
				y1Head--;
				x2--;
			}
		}
	}

	while(left[1] == 1)
	{
		if(previousMovement == LEFT)
		{
			TFT_voidDrawRectangle(x1,x2,y1,y2,0x001F);
			x1++;
			x2++;
		}

		else if(previousMovement == UP)
		{
			// initial values of coordinates
			y1Head = y2-7-(x2-x1);
			y2Head = y2-7;
			x1Head = x2;
			x2Head = x2+7;

			if(y1Head == y1)
			{
				TFT_voidDrawRectangle(x1Head,x2Head,y1Head,y2Head,0x001F);
				x1Head++;
				x2Head++;
			}

			else
			{
				TFT_voidDrawRectangle(x1Head ,x2Head ,y1Head ,y2Head ,0x001F);// HEAD
				TFT_voidDrawRectangle(x1 ,x2 ,y1 ,y2Head,0x001F);//Tail
				x1Head++;
				y1++;
			}
		}

		else if(previousMovement == DOWN)
		{
			// initial values of coordinates
			y1Head = y1+7;
			y2Head = y1+7 + x2-x1;
			x1Head = x2;
			x2Head = x2+7;

			if(y2 == y2Head)
			{
				TFT_voidDrawRectangle(x2Head-15,x2Head,y1Head,y2Head,0x001F);
				x2Head++;
			}
			else
			{
				TFT_voidDrawRectangle(x1Head ,x2Head ,y1Head ,y2Head ,0x001F);// HEAD
				TFT_voidDrawRectangle(x1 ,x2 ,y1+7 ,y2 ,0x001F);//Tail
				x2Head++;
				y2--;
			}
		}

	}

	while(right[1] == 1)
	{
		if(previousMovement == RIGHT)
		{
			TFT_voidDrawRectangle(x1,x2,y1,y2,0x001F);
			x1--;
			x2--;
		}
		else if(previousMovement == UP)
		{
			// initial values of coordinates
			x1Head = x1-7;
			x2Head = x1;
			y1Head = y2-7 - (x2-x1);
			y2Head = y2-7;

			if(y1 == y1Head)
			{
				TFT_voidDrawRectangle(x1Head,x1Head+15,y1Head,y2Head,0x001F);
				x1Head--;
			}
			else
			{
				TFT_voidDrawRectangle(x1Head ,x2Head ,y1Head ,y2Head ,0x001F);// HEAD
				TFT_voidDrawRectangle(x1 ,x2 ,y1 ,y2-7 ,0x001F);//Tail
				x1Head--;
				y1++;
			}
		}

		else if(previousMovement == DOWN)
		{
			// initial values of coordinates
			x1Head = x1-7;
			x2Head = x1;
			y1Head = y1+7;
			y2Head = y1+7 + (x2-x1);

			if(y2 == y2Head)
			{
				TFT_voidDrawRectangle(x1Head,x1Head+15,y1Head,y2Head,0x001F);
				x1Head--;
			}
			else
			{
				TFT_voidDrawRectangle(x1Head ,x2Head ,y1Head ,y2Head ,0x001F);// HEAD
				TFT_voidDrawRectangle(x1 ,x2 ,y1+7 ,y2 ,0x001F);//Tail
				x1Head--;
				y2--;
			}
		}
	}
}


 */
