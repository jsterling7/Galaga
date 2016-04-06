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
#include "ship_1.h"
#include "ship_1_life.h"
#include "alien_1.h"
#include <stdio.h>

enum gameState {
  STARTSCREEN,
  LEVEL_1,
  LEVEL_1_INIT,
  LEVEL_1_TEXT,
  LEVEL_1_UPDATE,
  // LEVEL_1,
  // LEVEL_2_TEXT,
  // LEVEL_2,
  // LEVEL_3_TEXT,
  // LEVEL_3,
  // GAMEOVER,
};

u32 theScore = 0;
u32 currentShipPosition = 105;
u32 exitToStart = 0;
u32 bullet = 0;
u32 selectB = 0;
u32 leftB = 0;
u32 rightB = 0;
u32 upB = 0;

u16 whiteColor = WHITE;

char levelText1[] = "LEVEL 1";
char currentScore[100];
char test[100];
u32 row1[8] = {1,1,1,1,1,1,1,1};
u32 row1Kill[8] = {1,1,1,1,1,1,1,1};
u32 row2[8] = {1,1,1,1,1,1,1,1};
u32 row2Kill[8] = {1,1,1,1,1,1,1,1};
u32 firstHit = 0;
u32 one = 0;
u32 two = 0;
u32 hit = 0;

u32 lowerbound;
u32 upperbound;
u32 currentP;
enum gameState currentState = STARTSCREEN;

int main() {
  REG_DISPCTL = MODE3 | BG2_ENABLE;
  // Fill the background with the image for the start screen

  while(1) {
    waitForVblank();
    switch(currentState) {
      case STARTSCREEN:
        theScore = 0;
        drawImage3(0, 0, STARTSCREEN_WIDTH, STARTSCREEN_HEIGHT, startScreen);
        if (KEY_DOWN_NOW(BUTTON_START)) {
          currentState = LEVEL_1_TEXT;
        }
        break;
      case LEVEL_1_TEXT:
        fillScreen(BLACK);
        drawString(73, 110, levelText1, BLUE);
        // print LEVEL 1 to the screen
        wait(50);
        currentState = LEVEL_1_INIT;
        break;
      case LEVEL_1_INIT:
        sprintf(currentScore, "SCORE: %d", theScore);
        drawImage3(0, 0, DEEPSPACE_WIDTH, DEEPSPACE_HEIGHT,deepSpace);
        drawString(150, 5, currentScore, WHITE);
        drawImage3(114, currentShipPosition, SHIP_1_WIDTH, SHIP_1_HEIGHT, ship_1);
        for (int width = 190; width < 235; width += 15) {
            drawImage3(140, width, SHIP_1_LIFE_WIDTH, SHIP_1_LIFE_HEIGHT, ship_1_life);
        }
        for (int height = 5; height <= 25; height += 20){
          for (int width = 20; width <= 200; width += 30) {
            drawImage3(height, width, ALIEN_1_WIDTH, ALIEN_1_HEIGHT - 5, alien_1);
          }
        }
        currentState = LEVEL_1;
        break;
      case LEVEL_1:
        if (KEY_DOWN_NOW(BUTTON_SELECT) && selectB == 0) {
          exitToStart = 1;
          currentState = STARTSCREEN;
          selectB = 1;
        }
        if (!KEY_DOWN_NOW(BUTTON_SELECT)) {selectB = 0;}
        if (KEY_DOWN_NOW(BUTTON_LEFT) && leftB == 0) {
          currentShipPosition -= 10;
          currentState = LEVEL_1_UPDATE;
          leftB = 1;
        }
        if (!KEY_DOWN_NOW(BUTTON_LEFT)) {leftB = 0;}

        if (KEY_DOWN_NOW(BUTTON_RIGHT) && rightB == 0) {
          currentShipPosition += 10;
          currentState = LEVEL_1_UPDATE;
          rightB = 1;
        }
        if (!KEY_DOWN_NOW(BUTTON_RIGHT)) {rightB = 0;}
        if (KEY_DOWN_NOW(BUTTON_UP) && upB == 0) {
          bullet = 1;
          currentState = LEVEL_1_UPDATE;
          upB = 1;
        }
        if (!KEY_DOWN_NOW(BUTTON_UP)) {upB = 0;}
        break;
      case LEVEL_1_UPDATE:

        if (currentShipPosition > 200) {
          currentShipPosition = 200;
        }
        if (currentShipPosition < 10) {
          currentShipPosition = 10;
        }
        int ailenP = currentShipPosition / 30;
        ailenP = ailenP * 30 - 10 + 30;
        int ailenP2 = ailenP + 30;
        waitForVblank();
        drawImage3(40, 0, DEEPSPACE_WIDTH, (DEEPSPACE_HEIGHT - 60), (deepSpace + (240*40)));
        drawImage3(114, currentShipPosition, SHIP_1_WIDTH, SHIP_1_HEIGHT, ship_1);
        if (bullet) {
          for (int i = 0; i < 8; i++) {
            lowerbound = (i * 30) + 20;
            upperbound = (i * 30) + 40;
            currentP = currentShipPosition + 11;
            if (currentP > lowerbound && currentP < upperbound) {
              hit = 1;
              sprintf(test, "P: %d", currentP);
              drawString(120, 5, test, WHITE);
              sprintf(test, "lowerbound, upperbound %d, %d", lowerbound, upperbound);
              drawString(100, 5, test, WHITE);
              if (row2[i] == 0 && row1[i] == 1) {
                firstHit = 0;
                row1[i] = 0;
                one = 1;
                theScore += 10;
              } else if (row2[i] == 1){
                row2[i] = 0;
                firstHit = 30;
                two = 2;
                theScore += 10;
              }
            }
          }
          sprintf(test, "P: %d", currentP);
          drawString(120, 5, test, WHITE);
          for(int height = 114; height > firstHit; height -= 5) {
            waitForVblank();
            if (hit) {
                drawImage3_2(0, ailenP, DEEPSPACE_WIDTH, (DEEPSPACE_HEIGHT - 48), (deepSpace), 30);
            } else {
                drawImage3_2(0, ailenP - 10, DEEPSPACE_WIDTH, (DEEPSPACE_HEIGHT - 48), (deepSpace), 10);
            }
            for (int height2 = 5; height2 <= 25; height2 += 20){
              for (int width = ailenP; width < ailenP2; width += 30) {
                if (height2 == 5) {
                  if (row1[width/30] == 0) {
                    if (height > 25 && row1Kill[width/30] == 1) {
                        drawImage3(height2, width, ALIEN_1_WIDTH, ALIEN_1_HEIGHT - 5, alien_1);

                    }
                  } else {
                    drawImage3(height2, width, ALIEN_1_WIDTH, ALIEN_1_HEIGHT - 5, alien_1);
                  }
                } else {
                  if (row2[width/30] == 0) {
                    if (height > 45 && row2Kill[width/30] == 1) {
                        drawImage3(height2, width, ALIEN_1_WIDTH, ALIEN_1_HEIGHT - 5, alien_1);

                    }
                  } else {
                    drawImage3(height2, width, ALIEN_1_WIDTH, ALIEN_1_HEIGHT - 5, alien_1);
                  }
                }

              }
            }
            shoot(height - 10, currentShipPosition + 11, whiteColor);
            wait(1);
          }
          if (one) {
            row1Kill[ailenP/30] = 0;
            one = 0;
            drawImage3_2(0, currentShipPosition - 3, DEEPSPACE_WIDTH, (DEEPSPACE_HEIGHT - 71), (deepSpace), 28);
          } else if (two) {
              row2Kill[ailenP/30] = 0;
              two = 0;
              waitForVblank();
              wait(1);
              drawImage3_2(23, currentShipPosition - 3, DEEPSPACE_WIDTH, (DEEPSPACE_HEIGHT - 48), (deepSpace), 28);
          }
          waitForVblank();
          drawImage3_2(114, currentShipPosition, DEEPSPACE_WIDTH, (DEEPSPACE_HEIGHT - 208), (deepSpace), 25);
          drawImage3(114, currentShipPosition, SHIP_1_WIDTH, SHIP_1_HEIGHT, ship_1);
          bullet = 0;
          firstHit = 0;
          hit = 0;
        }
        sprintf(currentScore, "SCORE: %d", theScore);
        drawImage3_2(150, 10, DEEPSPACE_WIDTH, (DEEPSPACE_HEIGHT - 150), deepSpace, 60);
        drawString(150, 5, currentScore, WHITE);
        currentState = LEVEL_1;
        break;
    }
  }
  return 0;
}
