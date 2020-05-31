#ifndef GAME_H
#define GAME_H

#include "gba.h"

                    /* TODO: */

            // Create any necessary structs //

typedef struct player {
    int sideLength;
    int row;
    int col;
} Player;

typedef struct enemy {
    int sideLength;
    int speed;
    int direction;
    int row;
    int col;
    int maxDistance;
    int curDistance;
    int posDir;
} Enemy;

typedef struct state {
    Player player;
    Enemy enemies[3];
} State;

/*
* For example, for a Snake game, one could be:
*
* typedef struct snake {
*   int heading;
*   int length;
*   int row;
*   int col;
* } Snake;
*
*
*
*
*
* Example of a struct to hold state machine data:
*
* typedef struct state {
*   int currentState;
*   int nextState;
* } State
*
*/

#endif
