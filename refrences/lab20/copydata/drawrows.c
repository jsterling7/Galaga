// CS 2110 DMA lab
// drawrows.c

typedef unsigned short u16;
typedef unsigned int u32;
typedef struct {
	const volatile void *src;
	volatile void *dst;
	volatile u32 cnt;
} DMA_CONTROLLER;

#define DMA ((volatile DMA_CONTROLLER*) 0x40000B0)
#define DMA_CHANNEL_0 0
#define DMA_CHANNEL_1 1
#define DMA_CHANNEL_2 2
#define DMA_CHANNEL_3 3

#define DMA_DESTINATION_INCREMENT (0 << 21)
#define DMA_DESTINATION_DECREMENT (1 << 21)
#define DMA_DESTINATION_FIXED (2 << 21)
#define DMA_DESTINATION_RESET (3 << 21)

#define DMA_SOURCE_INCREMENT (0 << 23)
#define DMA_SOURCE_DECREMENT (1 << 23)
#define DMA_SOURCE_FIXED (2 << 23)

#define DMA_REPEAT (1 << 25)

#define DMA_16 (0 << 26)
#define DMA_32 (1 << 26)

#define DMA_NOW (0 << 28)
#define DMA_AT_VBLANK (1 << 28)
#define DMA_AT_HBLANK (2 << 28)
#define DMA_AT_REFRESH (3 << 28)

#define DMA_IRQ (1 << 30)
#define DMA_ON (1 << 31)

extern unsigned short *videoBuffer;

// Draw one row of the screen with DMA
void drawrow(int row, const unsigned short *image) {

	// TODO re-implement this loop using DMA
	// Hint: There shouldn't even be a loop if you've done it correctly
	// This loop only draws one row of a fullscreen image
	// for(int i = 0; i < 240; ++i) {
	// 	videoBuffer[row * 240 + i] = image[row * 240 + i];
	// }

	DMA[DMA_CHANNEL_3].src = image + 240 * row ;
	DMA[DMA_CHANNEL_3].dst = videoBuffer + row * 240;
	DMA[DMA_CHANNEL_3].cnt = (240) |
													 DMA_SOURCE_INCREMENT |
													 DMA_DESTINATION_INCREMENT |
													 DMA_ON;


}
