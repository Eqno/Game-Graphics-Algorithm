#include "config.h"
#include "init.h"
#include "actor.h"
#include "plane.h"
#include "enemy.h"

void createWindow(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(WINDOW_POS_X, WINDOW_POS_Y);
    glutCreateWindow(WINDOW_TITLE.c_str());
}

extern Plane *actor;
Plane *actor;
extern std::vector<Plane *> enemy;
std::vector<Plane *> enemy;

void initActor() { actor = new Actor(); }
void initEnemy() { enemy.push_back((Plane *) new Enemy()); }