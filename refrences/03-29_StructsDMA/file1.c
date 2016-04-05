#include "myLib.h"
#include <stdlib.h>

#define NUMOBJS 7

typedef struct
{
	int row;
	int col;
	int rdel;
	int cdel;
	int size;
	u16 color;
} MOVOBJ;

int main()
{

	REG_DISPCTL = MODE3 | BG2_ENABLE;
	MOVOBJ objs[NUMOBJS];
	MOVOBJ oldobjs[NUMOBJS];
	MOVOBJ *cur;
	int dels[] = {-3, -2, -1, 1, 2, 3};
	int numdels = sizeof(dels)/sizeof(dels[0]);
	u16 colors[] = {RED, GREEN, BLUE, MAGENTA, CYAN, YELLOW, WHITE};
	int numcolors = sizeof(colors)/sizeof(colors[0]);

	for(int i=0; i<NUMOBJS; i++)
	{
		objs[i].row = 70 +rand()%20;
		objs[i].col = 110 + rand()%20;
		objs[i].rdel = dels[rand()%numdels];
		objs[i].cdel = dels[rand()%numdels];
		objs[i].color = colors[i%numcolors];
		objs[i].size = 5;
		oldobjs[i] = objs[i];
	}

	int size = 5;	
	int oldsize = size;
	int bgcolor = GRAY;
	DMA[3].src = &bgcolor;
	DMA[3].dst = videoBuffer;
	DMA[3].cnt = 38400 | DMA_ON | DMA_SOURCE_FIXED; 
	while(1)  // Game Loop
	{
		if(KEY_DOWN_NOW(BUTTON_UP))
		{
			size++;
			if(size > 150)
				size = 150;

		}
		if(KEY_DOWN_NOW(BUTTON_DOWN))
		{
			size--;
			if(size<2)
				size = 2;
		}
		for(int i=0; i<NUMOBJS; i++)
		{
			//cur = &objs[i];
			cur = objs + i;


			cur->row += cur->rdel;
			cur->col += cur->cdel;
			if(cur->row<0)
			{
				cur->row = 0;
				cur->rdel = - cur->rdel;
			}
			if(cur->row > 159-size+1)
			{
				cur->row = 159-size+1;
				cur->rdel = -cur->rdel;
			}
			if(cur->col < 0)
			{
				cur->col = 0;
				cur->cdel = -cur->cdel;
			}
			if(cur->col > 239-size+1)
			{
				cur->col= 239-size+1;
				cur->cdel = -cur->cdel;
			}
		}
		waitForVblank();
		for(int i=0; i<NUMOBJS; i++)
		{
			drawRect(oldobjs[i].row, oldobjs[i].col, oldsize, oldsize, bgcolor);
		}
		for(int i=0; i<NUMOBJS; i++)
		{
			cur = objs+i;
			drawRect(cur->row, cur->col, size, size, cur->color);
			oldobjs[i] = objs[i];
		}
		oldsize = size;
		

	}
}

