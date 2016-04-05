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
//  drawImage3(10, 10, 200, 120, deepSpace);
  drawRectangle(10, 10, 200, 120, BLUE);
  //fillScreen(BLUE);
}
