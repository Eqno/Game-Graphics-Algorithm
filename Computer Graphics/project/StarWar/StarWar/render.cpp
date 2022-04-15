#include "actor.h"
#include "enemy.h"
#include "config.h"

void renderBorder()
{
    glColor3dv(WHITE);
    glBegin(GL_LINE_LOOP);
    glVertex2d(-BORDER_WIDTH, -BORDER_HEIGHT);
    glVertex2d(-BORDER_WIDTH, BORDER_HEIGHT);
    glVertex2d(BORDER_WIDTH, BORDER_HEIGHT);
    glVertex2d(BORDER_WIDTH, -BORDER_HEIGHT);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    renderBorder();
    renderActor();
    renderEnemy();

    glutSwapBuffers();
}

void reshape(int x, int y)
{
    WIN_WIDTH_FAC = x, WIN_HEIGHT_FAC = y;
    glViewport(0, 0, x, y);
}