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
      DMA[DMA_CHANNEL_3].src = image + 240 * row;
      DMA[DMA_CHANNEL_3].dst = &videoBuffer[OFFSET((row + r), c, 240)];
      DMA[DMA_CHANNEL_3].cnt = width | DMA_DESTINATION_INCREMENT | DMA_SOURCE_INCREMENT | DMA_ON;
    }
}

void waitForVblank() {
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 160);
}

void wait(int time) {
	volatile int t = 0;
	for (int i = 0; i < time*10000; i++) {
		t++;
	}
}

void drawChar(int row, int col, char ch, u16 color) {
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 6; c++) {
			if(fontdata_6x8[OFFSET(r, c, 6) + ch*48]) {
				setPixel(row+r, col+c, color);
			}
		}
	}
}

void drawString(int row, int col, char *str, u16 color) {
	while(*str) {
		drawChar(row, col, *str++, color);
		col += 6;
	}
}

void setPixel(int r, int c, unsigned short color) {
	videoBuffer[OFFSET(r, c, 240)] = color;
}

int getNum(int num) {
  if (num == 0) {
    return 1;
  }
  int count = 0;
  int divide = 2;
  while (divide >= 1) {
    divide = num / (10^count);
    if (divide >= 1) {
      count++;
    }
  }
  return count;
}


void drawRectangle(int row, int column, int width, int height, u16 color) {
  for (int r = 0; r < height; r++) {
      DMA[DMA_CHANNEL_3].src = &color;
      DMA[DMA_CHANNEL_3].dst = &videoBuffer[OFFSET((r + row), column, 240)];
      DMA[DMA_CHANNEL_3].cnt = width | DMA_ON | DMA_SOURCE_FIXED;
    }
}

void fillScreen(volatile u16 color) {
  DMA[DMA_CHANNEL_3].src = &color;
  DMA[DMA_CHANNEL_3].dst = videoBuffer;
  DMA[DMA_CHANNEL_3].cnt = 38400 | DMA_ON | DMA_SOURCE_FIXED;
}
