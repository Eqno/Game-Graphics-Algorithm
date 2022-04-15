#include "plane.h"
#include "actor.h"

extern Plane *actor;

Actor::Actor(): Plane(ACT_POS_X, ACT_POS_Y, ACT_WIDTH, ACT_HEIGHT, ACT_COLOR) {}

void Actor::show()
{
    glColor3dv(this->color);
    glBegin(GL_POLYGON);
    glVertex2d((this->x-this->width)/WIN_WIDTH_FAC, (this->y-this->height)/WIN_HEIGHT_FAC);
    glVertex2d((this->x+this->width)/WIN_WIDTH_FAC, (this->y-this->height)/WIN_HEIGHT_FAC);
    glVertex2d(this->x/WIN_WIDTH_FAC, (this->y+this->height)/WIN_HEIGHT_FAC);
    glEnd();
}

void renderActor() { actor->show(); }
