#include "setup.h"

//file for setting up beginning of game

void setup(Player* p, Enemy* e1, Enemy* e2, Enemy* e3) {
    // sets player characteristics, draws to screen
    p->sideLength = 8;
    p->row = 26;
    p->col = 47;
    drawRectDMA(p->row, p->col, p->sideLength, p->sideLength, RED);

    // sets each enemy characteristics. NOTE: enemy 3 wasn't included in final game
    e1->speed = 1;
    e1->sideLength = 6;
    e1->direction = HORIZONTAL;
    e1->row = 60;
    e1->col = 70;
    e1->curDistance = 0;
    e1->maxDistance = 40;
    e1-> posDir = 0;
    drawRectDMA(e1->row, e1->col, e1->sideLength, e1->sideLength, BLUE);

    e2->speed = 1;
    e2->sideLength = 6;
    e2->direction = 0;
    e2->row = 130;
    e2->col = 160;
    e2->curDistance = 0;
    e2->maxDistance = 60;
    e2-> posDir = 0;
    drawRectDMA(e2->row, e2->col, e2->sideLength, e2->sideLength, BLUE);

    e3->speed = 1;
    e3->sideLength = 6;
    e3->direction = HORIZONTAL;
    e3->row = 60;
    e3->col = 70;
    e3->curDistance = 0;
    e3->maxDistance = 40;
    e3-> posDir = 0;
    drawRectDMA(e3->row, e3->col, e3->sideLength, e3->sideLength, BLUE);


}
