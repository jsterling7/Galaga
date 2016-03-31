typedef unsigned short u16;
typedef unsigned int u32;
typedef struct {
    const volatile void *src;
    volatile void *dst;
    volatile u32 cnt;
} DMA_CONTROLLER;

#define OFFSET (row, column, width) row * width + column

#define DMA ((volatile DMA_CONTROLLER*) 0x40000B0)
#define DMA_CHANNEL_3 3

#define DMA_DESTINATION_INCREMENT (0 << 21)
#define DMA_DESTINATION_FIXED (2 << 21)

#define DMA_SOURCE_INCREMENT (0 << 23)
#define DMA_SOURCE_FIXED (2 << 23)

#define DMA_ON (1 << 31)


extern unsigned short *videoBuffer;
