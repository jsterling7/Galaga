// typedefs
typedef unsigned short u16;
typedef unsigned int u32;

// CORE
#define REG_DISPCTL *(unsigned short *) 0x4000000
#define MODE3 3
#define BG2_ENABLE (1<<10)

#define SCANLINECOUNTER *(volatile unsigned short *)0x4000006

// COLORS
#define COLOR(r, g, b) (r | g << 5 | b << 10)

#define BLUE COLOR(0,0,31)
#define GREEN COLOR(0, 31, 0)
#define RED COLOR(31, 0, 0)
#define BLACK COLOR(0, 0, 0)
#define WHITE COLOR(31, 31, 31)
#define CYAN COLOR(0, 31, 31)


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

// DMA STUFF
typedef struct {
    const volatile void *src;
    volatile void *dst;
    volatile u32 cnt;
} DMA_CONTROLLER;

#define OFFSET(row, column, width) (row * width + column)

#define DMA ((volatile DMA_CONTROLLER *) 0x40000B0)
#define DMA_CHANNEL_3 3

#define DMA_DESTINATION_INCREMENT (0 << 21)
#define DMA_DESTINATION_FIXED (2 << 21)

#define DMA_SOURCE_INCREMENT (0 << 23)
#define DMA_SOURCE_FIXED (2 << 23)

#define DMA_ON (1 << 31)


extern unsigned short *videoBuffer;
extern const unsigned char fontdata_6x8[12288];

// Prototypes

void drawImage3(int r, int c, int width, int height, const u16* image);
void drawImage3_2(int r, int c, int width, int height, const u16* image, int cutoff);
void waitForVblank();
void wait(int time);
void drawChar(int row, int col, char ch, u16 color);
void drawString(int row, int col, char *str, u16 color);
void setPixel(int r, int c, unsigned short color);
void shoot(int row, int column, u16 color);
void isLeftButton();
void isRightButton();
void isUpButton();
void isSelectButton();
void isStartButton();
void shootBullet();
void moveShip();
void updateScore();
int checkArray(u32 array[]);
int isLevel1Complete();
void alienShoot();
void setLevel();
int isLevel2Complete();
void alienShoot2();
void shootBullet2();




// void drawRectangle(int r, int c, int width, int height, u16 color);
void fillScreen(volatile u16 color);
