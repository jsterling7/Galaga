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

#include "myLib.h"
#include "deepSpace.h"
#include "gameOver.h"





int main() {
  REG_DISPCTL = MODE3 | BG2_ENABLE;
  // Fill the background with the image for the start screen
  //drawImage3(0, 0, STARTSCREEN_WIDTH, STARTSCREEN_HEIGHT, startScreen);
  // Press enter to start
  // Sceen that says, "LEVEL 1"


  // Fill the background with a picture of a galaxy
  drawImage3(0, 0, DEEPSPACE_WIDTH, DEEPSPACE_HEIGHT, deepSpace);
  // drawImage3(0, 0, SMUGCAT_WIDTH, SMUGCAT_HEIGHT, data);
  while(1);
  return 0;
  //fillScreen(GREEN);
  // drawRect(10, 10, 100, 50, BLUE);
  // drawRectangle(10, 10, 100, 50, BLUE);
}
