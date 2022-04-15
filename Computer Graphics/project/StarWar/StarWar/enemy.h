#ifndef ENEMY_H
#define ENEMY_H

#include "config.h"
#include "plane.h"

const double *const ENE_COLOR = YELLOW;
const double ENE_WIDTH = 50, ENE_HEIGHT = 50;
const double ENE_POS_X = 0, ENE_POS_Y = 0;

class Enemy: public Plane
{
public:
    Enemy();
    void show();
};

void renderEnemy();

#endif