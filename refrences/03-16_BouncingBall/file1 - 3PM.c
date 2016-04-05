#define REG_DISPCTL *(unsigned short *)0x4000000
#define MODE3 3
#define BG2_ENABLE (1<<10)

unsigned short *videoBuffer = (unsigned short *)0x6000000;

#define COLOR(r, g, b)   ((r) | (g)<<5 | (b)<<10)
#define RED COLOR(31,0,0)
#define GREEN COLOR(0, 31, 0)
#define BLUE COLOR(0,0,31)
#define WHITE COLOR(31,31,31)
#define YELLOW COLOR(31,31,0)
#define BLACK 0

#define OFFSET(r, c, rowlen) ((r)*(rowlen) + (c))

// Buttons

#define BUTTON_A		(1<<0)
#define BUTTON_B		(1<<1)
#define BUTTON_SELECT	(1<<2)
#define BUTTON_START	(1<<3)
#define BUTTON_RIGHT	(1<<4)
#define BUTTON_LEFT		(1<<5)
#define BUTTON_UP		(1<<6)
#define BUTTON_DOWN		(1<<7)
#define BUTTON_R		(1<<8)
#define BUTTON_L		(1<<9)

#define KEY_DOWN_NOW(key)  (~(BUTTONS) & key)

#define BUTTONS *(volatile unsigned int *)0x4000130




// Prototypes
void  setPixel(int r, int c, unsigned short color);
void drawRect(int row, int col, int height, int width, unsigned short color);
void delay(int n);

int main()
{
	REG_DISPCTL = MODE3 | BG2_ENABLE;
	//*  (videoBuffer + 19320 ) = 32767;
	int row = 80;
	int col = 120;
	int rdel = 1;
	int cdel = 1;
	int size = 5;
	

	
	while(1) // Game Loop
	{
		if(KEY_DOWN_NOW(BUTTON_UP))
		{
			size++;
			if(size>150)
				size = 150;
		}
		if(KEY_DOWN_NOW(BUTTON_DOWN))
		{
			size--;
			if(size<2)
				size = 2;
		}
		row += rdel;
		col += cdel;
		
		if(row < 0)
		{
			row = 0;
			rdel = -rdel;
		}
		if(row > 159-size+1)
		{
			row = 159-size+1;
			rdel = -rdel;
		}
		if(col < 0)
		{
			col = 0;
			cdel = -cdel;
		}
		if(col>239-size+1)
		{
			col = 239-size+1;
			cdel = -cdel;
		}
		drawRect(row, col, size, size, YELLOW);
		delay(1);
		drawRect(row, col, size, size, BLACK);
	} 


}

void  setPixel(int r, int c, unsigned short color)
{
	videoBuffer[OFFSET(r, c, 240)] = color;
}

void drawRect(int row, int col, int height, int width, unsigned short color)
{
	for(int r=0; r<height; r++)
	{
		for(int c = 0; c<width; c++)
		{
			setPixel(row+r, col+c, color);
		}
	}
}

void delay(int n)
{
	volatile int x = 0;
	for(int i=0; i<n*10000; i++)
	{
		x++;
	}
}








