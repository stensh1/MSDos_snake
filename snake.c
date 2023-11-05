/* Orshak Ivan, 2015 */

#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>

enum
{
	head = 15, body = 2, FoodColor = 70
};

int length = 5, i, j = 1, z;
int snake_x[100], snake_y[100], food_x[20], food_y[20];
int x_last, x_next, y_last, y_next;
int death = 0, score = 0, level = 1, speed = 20;

void SetGr( void )
{
	asm mov Ax, 0x13 /* 320x200x256 */
	asm int 0x10
}

void CloseGr( void )
{
	asm mov Ax, 0x13 /* 320x200x256 */
	asm int 0x10
}

void PutPixel( int x, int y, int color )
{
	*(char*)(0xA0000000UL + 320U * y + x) = color;
}

void CheckFood( void )
{
	if (snake_x[1] == food_x[1] && snake_y[1] == food_y[1])
	{
		food_x[1] = food_x[1 + j];
		food_y[1] = food_y[1 + j];

		j++;
		score++;
		length++;
		speed--;

		PutPixel(food_x[1], food_y[1], FoodColor);
	}
}

void CheckHit( void )
{
	if (snake_x[1] == 50 || snake_x[1] == 270 || snake_y[1] == 42 || snake_y[1] == 180)
		death = 1;
	else
	{
		for (z = 2; z <= length; z++)
			if (snake_x[1] == snake_x[z] && snake_y[1] == snake_y[z])
				death = 1;
	}
}

void Table( void )
{
	printf(" Score:%i —--SNAKE--— Level:%i\r", score, level);
}

void TurnUp( void )
{
	do
	{
		for (i = 1; i <= length; i++)
		{
			if (i == 1)
			{
				y_next = snake_y[i];
				x_next = snake_x[i];

				snake_y[i]--;
				CheckHit();

				PutPixel(snake_x[i], snake_y[i], head);
				PutPixel(snake_x[length], snake_y[length], 0);

				CheckFood();
				Table();
			}
			else
			{
				y_last = snake_y[i];
				x_last = snake_x[i];
				snake_y[i] = y_next;
				snake_x[i] = x_next;

				PutPixel(snake_x[i], snake_y[i], body);
				PutPixel(snake_x[length], snake_y[length], 0);

				y_next = y_last;
				x_next = x_last;

				delay(speed);
			}
		}
	}
	while(!kbhit() && death != 1);
}

void TurnDown( void )
{
	do
	{
		for (i = 1; i <= length; i++)
		{
			if (i == 1)
			{
				y_next = snake_y[i];
				x_next = snake_x[i];

				snake_y[i]++;
				CheckHit();

				PutPixel(snake_x[i], snake_y[i], head);
				PutPixel(snake_x[length], snake_y[length], 0);

				CheckFood();
				Table();
			}
			else
			{
				y_last = snake_y[i];
				x_last = snake_x[i];

				snake_y[i] = y_next;
				snake_x[i] = x_next;

				PutPixel(snake_x[i], snake_y[i], body);
				PutPixel(snake_x[length], snake_y[length], 0);

				y_next = y_last;
				x_next = x_last;

				delay(speed);
			}
		}
	}
	while(!kbhit() && death != 1);
}

void TurnLeft( void )
{
	do
	{
		for (i = 1; i <= length; i++)
		{
			if (i == 1)
			{
				x_next = snake_x[i];
				y_next = snake_y[i];

				snake_x[i]--;
				CheckHit();

				PutPixel(snake_x[i], snake_y[i], head);
				PutPixel(snake_x[length], snake_y[length], 0);

				CheckFood();
				Table();
			}
			else
			{
				x_last = snake_x[i];
				y_last = snake_y[i];

				snake_x[i] = x_next;
				snake_y[i] = y_next;

				PutPixel(snake_x[i], snake_y[i], body);
				PutPixel(snake_x[length], snake_y[length], 0);

				x_next = x_last;
				y_next = y_last;

				delay(speed);
			}
		}
	}
	while(!kbhit() && death != 1);
}

void TurnRight( void )
{
	do
	{
		for (i = 1; i <= length; i++)
		{
			if (i == 1)
			{
				x_next = snake_x[i];
				y_next = snake_y[i];

				snake_x[i]++;
				CheckHit();

				PutPixel(snake_x[i], snake_y[i], head);
				PutPixel(snake_x[length], snake_y[length], 0);

				CheckFood();
				Table();
			}
			else
			{
				x_last = snake_x[i];
				y_last = snake_y[i];

				snake_x[i] = x_next;
				snake_y[i] = y_next;

				PutPixel(snake_x[i], snake_y[i], body);
				PutPixel(snake_x[length], snake_y[length], 0);

				x_next = x_last;
				y_next = y_last;

				delay(speed);
			}
		}
	}
	while(!kbhit() && death != 1);
}

void main( void )
{
	begin:

	score = 0;
	level = 1;
	speed = 20;

	SetGr();

	printf("\n");

	for (i = 0; i <= 319; i++)
		PutPixel(i, 22, 5);

	for (i = 42; i <= 180; i++)
	{
		PutPixel(50, i, 30);
		PutPixel(270, i, 30);
	}

	for (i = 50; i <=270; i++)
	{
		PutPixel(i, 42, 30);
		PutPixel(i, 180, 30);
	}

	for (i = 1; i <= length; i++)
	{
		snake_x[i] = 57 - i;
		snake_y[i] = 110;

		if (i == 1)
			PutPixel(snake_x[i], snake_y[i], head);
		else
			PutPixel(snake_x[i], snake_y[i], body);
	}

	for (i = 1; i <= 20; i++)
	{
		food_x[i] = rand() % 220 + 50;
		food_y[i] = rand() % 138 + 42;
	}

	PutPixel(food_x[1], food_y[1], FoodColor);

	Table();
	while (death != 1)
	{
		switch (getch())
		{
			case 'w':
			TurnUp();
			break;

			case 'a':
			TurnLeft();
			break;

			case 's':
			TurnDown();
			break;

			case 'd':
			TurnRight();
			break;

			default:
			break;
		}

		if (death == 1)
		{
			printf("\n\n\n\n\n\n\n\n\n\n\n Game over!\n"
			" Do you want play again?\n (y/n)\n\r");

			question:

			switch (getch())
			{
				case 'y':
				death = 0;
				goto begin;

				case 'n':
				break;

				default:
				printf(" Unknown command!\n");
				goto question;
			}
		}
	}

	CloseGr();
}