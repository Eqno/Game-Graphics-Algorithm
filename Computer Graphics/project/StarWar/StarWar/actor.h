#ifndef ACTOR_H
#define ACTOR_H

#include "config.h"
#include "plane.h"

const double *const ACT_COLOR = WHITE;
const double ACT_WIDTH = 100, ACT_HEIGHT = 50;
const double ACT_POS_X = 0, ACT_POS_Y = -500;

class Actor: public Plane
{
public:
    Actor();
    void show();
};

void renderActor();

#endif