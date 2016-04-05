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
#include "startScreen.h"
#include <stdio.h>

enum gameState {
  STARTSCREEN,
  LEVEL_1,
  LEVEL_1_TEXT,
  // LEVEL_1,
  // LEVEL_2_TEXT,
  // LEVEL_2,
  // LEVEL_3_TEXT,
  // LEVEL_3,
  // GAMEOVER,
};

int theScore = 10;

char levelText1[] = "LEVEL 1";
char currentScore[100];


enum gameState currentState = STARTSCREEN;

int main() {
  REG_DISPCTL = MODE3 | BG2_ENABLE;
  // Fill the background with the image for the start screen

  while(1) {
    waitForVblank();
    switch(currentState) {
      case STARTSCREEN:
        drawImage3(0, 0, STARTSCREEN_WIDTH, STARTSCREEN_HEIGHT, startScreen);
        if (KEY_DOWN_NOW(BUTTON_START)) {
          currentState = LEVEL_1_TEXT;
        }
        break;
      case LEVEL_1_TEXT:
        fillScreen(BLACK);
        drawString(73, 110, levelText1, BLUE);
        // print LEVEL 1 to the screen
        wait(100);
        currentState = LEVEL_1;
        break;
      case LEVEL_1:
      //  currentScore = "%d", theScore;
        // scoreLength = getNum(score);
        // for (int i = 0; i < scoreLength) {
        //   score[i] =
        // }
        sprintf(currentScore, "SCORE: %d", theScore);
        drawImage3(0, 0, DEEPSPACE_WIDTH, DEEPSPACE_HEIGHT,deepSpace);
        drawString(150, 5, currentScore, WHITE);
        if (KEY_DOWN_NOW(BUTTON_A)) {
          theScore++;
        }
        break;
    }


      // Screen for when the game ends
    //  drawImage3(0, 0, GAMEOVER_WIDTH, GAMEOVER_HEIGHT, gameOver);

  return 0;
}
