

typedef unsigned short u16;
typedef unsigned int u32;

#define REG_DISPCTL *(unsigned short *) 0x4000000
#define MODE3 3
#define BG2_ENABLE (1<<10)

#define COLOR(r, g, b) (r | g << 5 | b << 10)

#define BLUE COLOR(0,0,31)
#define GREEN COLOR(0, 31, 0)


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

//
void drawImage3(int r, int c, int width, int height, const u16* image);
void drawRectangle(int r, int c, int width, int height, u16 color);
void fillScreen(volatile u16 color);
