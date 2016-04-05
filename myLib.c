#include "myLib.h"

unsigned short *videoBuffer = (unsigned short *)0x6000000;

/* drawimage3
   * A function that will draw an arbitrary sized image
   * onto the screen (with DMA).
   * @param r row to draw the imcage
   * @param c column to draw the image
   * @param width width of the image
   * @param height height of the image
   * @param image Pointer to the first element of the image.
   */

void drawImage3(int r, int c, int width, int height, const u16* image) {
    for (int row = 0; row < height; row++) {
        DMA[DMA_CHANNEL_3].src = &image;
        DMA[DMA_CHANNEL_3].dst = &videoBuffer[OFFSET(row + r, c, 240)];
        DMA[DMA_CHANNEL_3].cnt = width | DMA_SOURCE_INCREMENT | DMA_DESTINATION_INCREMENT |
            DMA_ON;
    }
}

void drawRectangle(int r, int c, int width, int height, u16 color) {
  for (int row = 0; row < height; row++) {
      DMA[DMA_CHANNEL_3].src = &color;
      DMA[DMA_CHANNEL_3].dst = &videoBuffer[OFFSET(row + r, c, 240)];
      DMA[DMA_CHANNEL_3].cnt = width | DMA_SOURCE_FIXED | DMA_ON;
    }
}

void fillScreen(volatile u16 color) {
  DMA[DMA_CHANNEL_3].src = &color;
 DMA[DMA_CHANNEL_3].dst = videoBuffer;
  DMA[DMA_CHANNEL_3].cnt = 38400 | DMA_ON | DMA_SOURCE_FIXED;
}
