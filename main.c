/*
Do not use floats or doubles
only call waitForVBlank once per iteration of the while/game loop
no tearing
keep code efficent
this HW is graded no creativity and work ethic so go above and beyond


GameBoy | Keyboard
--------|----------
Start   | Enter
Select  | Backspace
A |Z
B |X
L |A
R |S
Left | Left Arrow Right | Right Arrow Up | Up Arrow Down | Down Arrow

use the rand function to add in randomness
*/

#include <myLib.h>
#include <deepSpace.h>
#include <gameOver.h>





int main() {

    void drawImage3(int r, int c, int width, int height, const u16* image);

    drawImage3(0, 0, 240, 160, &deepSpace);
}


/* drawimage3
   * A function that will draw an arbitrary sized image
   * onto the screen (with DMA).
   * @param r row to draw the image
   * @param c column to draw the image
   * @param width width of the image
   * @param height height of the image
   * @param image Pointer to the first element of the image.
   */
void drawImage3(int r, int c, int width, int height, const u16* image) {
    for (int row = 0; r < height; r++) {
        DMA[DMA_CHANNEL_3].src = &image;
        DMA[DMA_CHANNEL_3].dst = &videoBuffer[OFFSET(r + row, col, 240)];
        DMA[DMA_CHANNEL_3].cnt = width | DMA_SOURCE_INCREMENT| DMA_DESTINATION_INCREMENT |
            DMA_ON;
    }



}
