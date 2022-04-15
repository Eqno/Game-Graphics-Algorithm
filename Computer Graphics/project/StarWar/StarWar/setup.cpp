#include "config.h"
#include "render.h"
#include "init.h"

int windowWidth = 1600, windowHeight = 900;
double WIN_WIDTH_FAC = windowWidth, WIN_HEIGHT_FAC = windowHeight; 

int main(int argc, char **argv)
{
    // init
    createWindow(argc, argv);
    initActor();
    initEnemy();

    // render
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    // loop
    glutMainLoop();
}