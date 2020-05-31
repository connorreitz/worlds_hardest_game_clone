#include "game.h"

#include <stdio.h>
#include <stdlib.h>

#include "gba.h"
#include "setup.h"
#include "player.h"
#include "enemy.h"

#include "images/garbage.h"
#include "images/title_screen.h"
#include "images/stage1.h"
#include "images/win_screen.h"
#include "images/lose_screen.h"
#include "images/difficulty_meter.h"

/* TODO: */
// Include any header files for title screen or exit
// screen images generated by nin10kit. Example for the provided garbage
// image:
// #include "images/garbage.h"

/* TODO: */
// Add any additional states you need for your app.
typedef enum {
  START,
  WAIT_PLAY,
  SETUP_PLAY,
  PLAY,
  WIN,
  LOSE,
} GBAState;

int main(void) {
  /* TODO: */
  // Manipulate REG_DISPCNT here to set Mode 3. //
  REG_DISPCNT = MODE3 | BG2_ENABLE;
  // Save current and previous state of button input.
  u32 previousButtons = BUTTONS;
  u32 currentButtons = BUTTONS;
  //Create player, enemies
  Player p;
  Enemy e1;
  Enemy e2;
  Enemy e3;
  //int acts as bool to determine whether to draw the "one more chance" message
  int drawMessage = 0;


  // Load initial game state
  GBAState state = START;

  while (1) {
    currentButtons = BUTTONS;  // Load the current state of the buttons

    /* TODO: */
    // Manipulate the state machine below as needed //
    // NOTE: Call waitForVBlank() before you draw

    switch (state) {
      case START:  // draws title screen and transitions to wait for the person to play
        waitForVBlank();
        drawFullScreenImageDMA(title_screen);
        state = WAIT_PLAY;
        break;
      case WAIT_PLAY: // waits for a to be pressed to play
        if (KEY_JUST_PRESSED(BUTTON_A, currentButtons, previousButtons)) {
          state = SETUP_PLAY;
        }
        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
          state = START;
        }
        break;
      case SETUP_PLAY: // draws beginning of the stage
        waitForVBlank();
        drawFullScreenImageDMA(stage1);
        drawImageDMA(25, 100, DIFFICULTY_METER_WIDTH, DIFFICULTY_METER_HEIGHT, difficulty_meter);
        setup(&p, &e1, &e2, &e3); // sets up players and enemies on screen
        drawMessage = 0;

        state = PLAY;
        break;
      case PLAY:
        waitForVBlank();

        // checks for movement, makes sure you can't move diagonally (2 inputs at same time)
        if (KEY_DOWN(BUTTON_UP, currentButtons)) {
          if (p.row > 66 || (p.col <= 87 - p.sideLength && p.row > 17)) {
            waitForVBlank();
            moveUp(&p);
        }
      } else if (KEY_DOWN(BUTTON_DOWN, currentButtons)) {
        if (p.row < 145 - p.sideLength) {
          waitForVBlank();
          moveDown(&p);
        }

      } else if (KEY_DOWN(BUTTON_LEFT, currentButtons)) {
        if (p.col > 21) {
          waitForVBlank();
          moveLeft(&p);
        }

      } else if (KEY_DOWN(BUTTON_RIGHT, currentButtons)) {
        if (p.row > 65 || p.col < 87 - p.sideLength) {
          waitForVBlank();
          moveRight(&p);
        }
      }
      // if player movement has been conducted, move enemies on screen
      movement(&e1);
      movement(&e2);

      // if player is in the safe zone, we've won!
      if (p.col >= 185) {
        state = WIN;
        drawMessage = 0;
      }

      //logic for getting hit by enemies, collision detection, one more chance
      if ((e1.row - p.row <= 6 && e1.row - p.row >= -6) && (e1.col - p.col <= 6 && e1.col - p.col >= -6)) {
        colorIn(p.row, p.col, p.sideLength, stage1);
        p.row = 26;
        p.col = 47;
        drawRectDMA(p.row, p.col, p.sideLength, p.sideLength, RED);
        if (drawMessage == 0) {
          drawString(15, 100, "One more chance!", BLACK);
          drawMessage = 1;
        } else {
          state = LOSE;
          drawMessage = 0;
        }
      }

      // logic for enemy 2 (probably just should've made a function but oh well)
      if ((e2.row - p.row <= 6 && e2.row - p.row >= -6) && (e2.col - p.col <= 6 && e2.col - p.col >= -6)) {
        colorIn(p.row, p.col, p.sideLength, stage1);
        p.row = 26;
        p.col = 47;
        drawRectDMA(p.row, p.col, p.sideLength, p.sideLength, RED);
        if (drawMessage == 0) {
          drawString(15, 100, "One more chance!", BLACK);
          drawMessage = 1;
        } else {
          state = LOSE;
          drawMessage = 0;
        }

      }

        // if select is pressed, go to start screen
        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
          state = START;
        }

        break;
      case WIN:
        waitForVBlank();
        drawFullScreenImageDMA(win_screen);

        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
          state = START;
        }
        break;
      case LOSE:
        waitForVBlank();
        drawFullScreenImageDMA(lose_screen);

        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
          state = START;
        }
        // state = ?
        break;
    }

    previousButtons = currentButtons;  // Store the current state of the buttons
  }

  //UNUSED(previousButtons);  // You can remove this once previousButtons is used

  return 0;
}
