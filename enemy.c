#include "enemy.h"
#include "gba.h"
#include "setup.h"

#include "images/stage1.h"

//determines how an enemy moves based on its characteristics - provides movement logic as well
void movement(Enemy* e) {
    colorIn(e->row, e->col, e->sideLength, stage1);
    if (e->direction == HORIZONTAL) {
        if (e->posDir == 1) {
            e->col += e->speed;
            e->curDistance -= e->speed;
        } else {
            e->col -= e->speed;
            e->curDistance += e->speed;
        }

    } else {
        if (e->posDir == 1) {
            e->row += e->speed;
            e->curDistance -= e->speed;
        } else {
            e->row -= e->speed;
            e->curDistance += e->speed;
        }

    }

    drawRectDMA(e->row, e->col, e->sideLength, e->sideLength, BLUE);

    if (e->curDistance >= e->maxDistance) {
        e->posDir = 1;
    }

    if (e->curDistance <= 0) {
        e->posDir = 0;
    }


}
