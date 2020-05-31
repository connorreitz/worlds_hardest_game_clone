#include "player.h"
#include "images/stage1.h"
#include "gba.h"

//file for movement logic of player

void moveUp(Player* p) {
    int delta = 1;
    colorIn(p->row, p->col, p->sideLength, stage1);
    p->row -= delta;

    drawRectDMA(p->row, p->col, p->sideLength, p->sideLength, RED);

}

void moveDown(Player* p) {
    int delta = 1;
    colorIn(p->row, p->col, p->sideLength, stage1);
    p->row += delta;

    drawRectDMA(p->row, p->col, p->sideLength, p->sideLength, RED);
}

void moveLeft(Player* p) {
    int delta = 1;
    colorIn(p->row, p->col, p->sideLength, stage1);
    p->col -= delta;

    drawRectDMA(p->row, p->col, p->sideLength, p->sideLength, RED);
}

void moveRight(Player* p) {
    int delta = 1;
    colorIn(p->row, p->col, p->sideLength, stage1);
    p->col += delta;

    drawRectDMA(p->row, p->col, p->sideLength, p->sideLength, RED);
}


