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
#include <stdlib.h>

enum gameState {
  STARTSCREEN,
  INSTRUCTIONS,
  LEVEL_1,
  LEVEL_1_INIT,
  LEVEL_1_TEXT,
  LEVEL_1_SCORE,
  LEVEL_2_TEXT,
  LEVEL_2_INIT,
  LEVEL_2,
  LEVEL_2_SCORE,
  GAMEOVERDEAD,
  FINALSCORE,
  HIT,
  FINISH,
};

time_t t;

u32 theScore = 0;
u32 currentShipPosition = 105;
int numberOfLives = 3;
u32 *sp = &currentShipPosition;
u32 bullet = 0;
u32 startB = 0;
u32 selectB = 0;
u32 leftB = 0;
u32 rightB = 0;
u32 upB = 0;

u16 whiteColor = WHITE;

char levelText1[] = "LEVEL 1";
char levelText2[] = "LEVEL 2";
char levelComplete1[] = "LEVEL 1 COMPLETE";
char levelComplete2[] = "LEVEL 2 COMPLETE";
char instruction1[] = "MOVE with the LEFT and RIGHT arrows";
char instruction2[] = "SHOOT with the UP arrow";
char finishGame[] = "THE END";
char author[] = "CREATED BY: Joshua Sterling";
char currentScore[100];
char test[100];
u32 row1[7] = {1,1,1,1,1,1,1};
u32 row1Kill[7] = {1,1,1,1,1,1,1};
u32 row2[7] = {1,1,1,1,1,1,1};
u32 row2Kill[7] = {1,1,1,1,1,1,1};
int firstHit = 0;
u32 one = 0;
u32 two = 0;
u32 hit = 0;
u32 theFirstCurrentPosition;
u32 leave = 0;
u32 levelsCompleted = 0;

u32 lowerbound;
u32 upperbound;
u32 currentP;
enum gameState currentState = STARTSCREEN;

int main() {
  REG_DISPCTL = MODE3 | BG2_ENABLE;
//  srand((unsigned) time(&t));


  while(1) {
    waitForVblank();
    switch(currentState) {
      case STARTSCREEN:
        theScore = 0;
        drawImage3(0, 0, STARTSCREEN_WIDTH, STARTSCREEN_HEIGHT, startScreen);
        isStartButton();
        break;
      case INSTRUCTIONS:
        fillScreen(BLACK);
        drawString(58, 15, instruction1, CYAN);
        drawString(73, 55, instruction2, CYAN);
        wait(75);
        currentState = LEVEL_1_TEXT;
        break;
      case LEVEL_1_TEXT:
        fillScreen(BLACK);
        drawString(73, 110, levelText1, BLUE);
        // print LEVEL 1 to the screen
        wait(80);
        currentState = LEVEL_1_INIT;
        break;
      case LEVEL_1_INIT:
        setLevel();
        for (int height = 5; height <= 25; height += 20){
          for (int width = 20; width <= 200; width += 30) {
            if (height == 5) {
              if (row1[width/30] == 1) {
                    drawImage3(height, width, ALIEN_1_WIDTH, ALIEN_1_HEIGHT - 5, alien_1);
                }
            } else {
              if (row2[width/30] == 1) {
                    drawImage3(height, width, ALIEN_1_WIDTH, ALIEN_1_HEIGHT - 5, alien_1);

              }
            }
          }
        }
        currentState = LEVEL_1;
        break;
      case LEVEL_1:
        isSelectButton();
        isLeftButton();
        isRightButton();
        //isUpButton();
        alienShoot();
        if (isLevel1Complete()) {
          currentState = LEVEL_1_SCORE;
        }
        break;
      case LEVEL_1_SCORE:
        fillScreen(BLACK);
        drawString(63, 78, levelComplete1, CYAN);
        drawString(73, 90, currentScore, CYAN);
        wait(100);
        currentState = LEVEL_2_TEXT;
        levelsCompleted++;
        break;
      case LEVEL_2_TEXT:
        fillScreen(BLACK);
        drawString(73, 110, levelText2, BLUE);
        wait(80);
        currentState = LEVEL_2_INIT;
        break;
      case LEVEL_2_INIT:
        setLevel();
        for (int i = 0; i < 7; i++) {
          row1[i] = 1;
          row2[i] = 1;
          row2Kill[i] = 1;
          row1Kill[i] = 1;
        }
        // updateArray(row2);
        // updateArray(row1Kill);
        // updateArray(row2Kill);
        for (int height = 5; height <= 25; height += 20) {
          for (int width = 20; width <= 200; width += 30) {
            if (height == 5) {
              if (row1[width/30] == 1) {
                    drawImage3(height, width, ALIEN_1_WIDTH, ALIEN_1_HEIGHT - 5, alien_1);
                }
            } else {
              if (row2[width/30] == 1) {
                    drawImage3(height, width, ALIEN_1_WIDTH, ALIEN_1_HEIGHT - 5, alien_1);

              }
            }
          }
        }
        currentState = LEVEL_2;
        break;
      case LEVEL_2:
        isSelectButton();
        isLeftButton();
        isRightButton();
        //isUpButton();
        alienShoot();
        if (isLevel2Complete()) {
          currentState = LEVEL_2_SCORE;
        }
        break;
      case LEVEL_2_SCORE:
        fillScreen(BLACK);
        drawString(63, 78, levelComplete2, CYAN);
        drawString(73, 90, currentScore, CYAN);
        wait(100);
        currentState = FINISH;
        levelsCompleted++;
        break;
      case FINISH:
        fillScreen(BLACK);
        drawString(53, 98, finishGame, CYAN);
        drawString(73, 35, author, CYAN);
        wait(250);
        currentState = FINALSCORE;
        break;
      case HIT:
        numberOfLives = numberOfLives - 1;
        if (numberOfLives < 0) {
          currentState = GAMEOVERDEAD;
          wait(50);
        } else {
          currentState = LEVEL_1_INIT;
          currentShipPosition = 105;
        }
        break;
      case GAMEOVERDEAD:
        drawImage3(0, 0, GAMEOVER_WIDTH, GAMEOVER_HEIGHT, gameOver);
        currentState = FINALSCORE;
        wait(100);
      case FINALSCORE:
        fillScreen(BLACK);
        sprintf(currentScore, "FINAL SCORE: %d", theScore);
        drawString(70, 63, currentScore, WHITE);
        sprintf(currentScore, "LEVELS COMPLETED: %d", levelsCompleted);
        drawString(60, 63, currentScore, WHITE);
        wait(300);
        leave = 1;
        break;
    }
    if(leave) {
      break;
    }
  }
  fillScreen(BLACK);
  return 0;
}


void setLevel() {
  currentShipPosition = 105;
  sprintf(currentScore, "SCORE: %d", theScore);
  drawImage3(0, 0, DEEPSPACE_WIDTH, DEEPSPACE_HEIGHT,deepSpace);
  drawString(150, 5, currentScore, WHITE);
  drawImage3(114, currentShipPosition, SHIP_1_WIDTH, SHIP_1_HEIGHT, ship_1);
  for (int width = 235 - (15 * numberOfLives); width < 235; width += 15) {
      drawImage3(140, width, SHIP_1_LIFE_WIDTH, SHIP_1_LIFE_HEIGHT, ship_1_life);
  }
}
void isLeftButton() {
  if (KEY_DOWN_NOW(BUTTON_LEFT) && leftB == 0) {
    currentShipPosition -= 10;
    moveShip();
    leftB = 1;
  }
  if (!KEY_DOWN_NOW(BUTTON_LEFT)) {leftB = 0;}
}

void isRightButton() {
  if (KEY_DOWN_NOW(BUTTON_RIGHT) && rightB == 0) {
    currentShipPosition += 10;
    moveShip();
    rightB = 1;
  }
  if (!KEY_DOWN_NOW(BUTTON_RIGHT)) {rightB = 0;}
}

void isUpButton() {
  if (KEY_DOWN_NOW(BUTTON_UP) && upB == 0) {
    shootBullet();
    upB = 1;
  }
  if (!KEY_DOWN_NOW(BUTTON_UP)) {upB = 0;}
}

void isSelectButton() {
  if (KEY_DOWN_NOW(BUTTON_SELECT) && selectB == 0) {
    theScore = 0;
    currentShipPosition = 105;
    numberOfLives = 3;
    for (int i = 0; i < 7; i++) {
      row1[i] = 1;
      row2[i] = 1;
      row2Kill[i] = 1;
      row1Kill[i] = 1;
    }
    currentState = STARTSCREEN;
    selectB = 1;
  }
  if (!KEY_DOWN_NOW(BUTTON_SELECT)) {selectB = 0;}
}



void isStartButton() {
  drawImage3(0, 0, STARTSCREEN_WIDTH, STARTSCREEN_HEIGHT, startScreen);
  if (KEY_DOWN_NOW(BUTTON_START) && startB == 0) {
    currentState = INSTRUCTIONS;
    startB = 1;
  }
  if (!KEY_DOWN_NOW(BUTTON_START)) {startB = 0;}
}

void moveShip() {
  if (currentShipPosition > 200) {
    currentShipPosition = 200;
  }
  if (currentShipPosition < 10) {
    currentShipPosition = 10;
  }
  waitForVblank();
  drawImage3_2(114, currentShipPosition - 10, DEEPSPACE_WIDTH, (DEEPSPACE_HEIGHT - 134), (deepSpace), 45);
  drawImage3(114, currentShipPosition, SHIP_1_WIDTH, SHIP_1_HEIGHT, ship_1);
}

void updateScore() {
  sprintf(currentScore, "SCORE: %d", theScore);
  drawImage3_2(150, 10, DEEPSPACE_WIDTH, (DEEPSPACE_HEIGHT - 150), deepSpace, 60);
  drawString(150, 5, currentScore, WHITE);
}
void alienShoot() {
  u32 randomAlien = (rand() % 6);
  u32 chance = (rand() % 10);
  u32 alienPosition1 = randomAlien * 30 + 20 + 9;
  isUpButton();
  isLeftButton();
  isRightButton();
  if (row2[randomAlien] == 1 && chance > 8) {
    for (int height = 45; height < 139; height += 5) {
      isUpButton();
      isLeftButton();
      isRightButton();
      if (height > 114 && alienPosition1 > currentShipPosition && alienPosition1 < currentShipPosition + 20) {
           currentState = HIT;
      }
      drawImage3_2(height - 5, alienPosition1, DEEPSPACE_WIDTH, 5, (deepSpace), 3);
      shoot(height, alienPosition1, whiteColor);
      isLeftButton();
      isRightButton();
      wait(3);
    }
  }

  drawImage3_2(135, alienPosition1, DEEPSPACE_WIDTH, 5, (deepSpace), 3);

}

void shootBullet() {
    theFirstCurrentPosition = *sp;
    if (theFirstCurrentPosition > 200) {
      theFirstCurrentPosition = 200;
    }
    if (theFirstCurrentPosition < 10) {
      theFirstCurrentPosition = 10;
    }
    int ailenP = theFirstCurrentPosition / 30;
    ailenP = ailenP * 30 - 10 + 30;
    int ailenP2 = ailenP + 30;
    for (int i = 0; i < 8; i++) {
      lowerbound = (i * 30) + 20;
      upperbound = (i * 30) + 40;
      currentP = theFirstCurrentPosition + 11;
      if (currentP > lowerbound && currentP < upperbound) {
        hit = 1;
        if (row2[i] == 0 && row1[i] == 1) {
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
    for(int height = 104; height > firstHit; height -= 5) {
      waitForVblank();
      if (hit) {
          if (height < 45) {
            drawImage3_2(height + 5, ailenP, DEEPSPACE_WIDTH, 10, deepSpace, 30);
          } else {
            drawImage3_2(height + 5, theFirstCurrentPosition + 11, DEEPSPACE_WIDTH, 5, deepSpace, 3);
          }

      } else {
          drawImage3_2(height + 5, theFirstCurrentPosition + 11, DEEPSPACE_WIDTH, 5, deepSpace, 3);
      }
      for (int height2 = 5; height2 <= 25; height2 += 20) {
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
      shoot(height, theFirstCurrentPosition + 11, whiteColor);
      isLeftButton();
      isRightButton();
      wait(1);
    }
      if (one) {
        row1Kill[ailenP/30] = 0;
        one = 0;
        drawImage3_2(0, theFirstCurrentPosition - 3, DEEPSPACE_WIDTH, 25, (deepSpace), 28);
      } else if (two) {
          row2Kill[ailenP/30] = 0;
          two = 0;
          drawImage3_2(23, theFirstCurrentPosition - 3, DEEPSPACE_WIDTH, 25, (deepSpace), 28);
      } else {
          drawImage3_2(0, theFirstCurrentPosition + 11, DEEPSPACE_WIDTH, 10, (deepSpace), 5);
      }
      bullet = 0;
      firstHit = 0;
      hit = 0;
      updateScore();
  }

  int checkArray(u32 array[]) {
    for (int i = 0; i < 8; i++) {
      if (array[i] == 1) {
        return 0;
      }
    }
    return 1;
  }

  int isLevel1Complete() {
    if (checkArray(row1) && checkArray(row2)) {
      return 1;
    }
    return 0;
  }

  int isLevel2Complete() {
    if (checkArray(row1) && checkArray(row2)) {
      return 1;
    }
    return 0;
  }
