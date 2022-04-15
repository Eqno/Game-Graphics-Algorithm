#include "enemy.h"

extern std::vector <Plane *> enemy;

Enemy::Enemy(): Plane(ENE_POS_X, ENE_POS_Y, ENE_WIDTH, ENE_HEIGHT, ENE_COLOR) {};

void Enemy::show()
{
    glColor3dv(this->color);
    glBegin(GL_POLYGON);
    glVertex2d((this->x-this->width)/WIN_WIDTH_FAC, (this->y-this->height)/WIN_HEIGHT_FAC);
    glVertex2d((this->x-this->width)/WIN_WIDTH_FAC, (this->y+this->height)/WIN_HEIGHT_FAC);
    glVertex2d((this->x+this->width)/WIN_WIDTH_FAC, (this->y+this->height)/WIN_HEIGHT_FAC);
    glVertex2d((this->x+this->width)/WIN_WIDTH_FAC, (this->y-this->height)/WIN_HEIGHT_FAC);
    glEnd();
}

void renderEnemy()
{
    for (const auto &i: enemy) i->show();
}