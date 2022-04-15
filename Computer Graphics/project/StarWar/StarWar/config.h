#ifndef CONFIG_H
#define CONFIG_H

// GL
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <string>
#include <vector>
#include <iostream>

extern int windowWidth, windowHeight;
extern double WIN_WIDTH_FAC, WIN_HEIGHT_FAC; 
const int WINDOW_POS_X = 0, WINDOW_POS_Y = 0;
const std::string WINDOW_TITLE = "Star War";
const double BORDER_WIDTH = 0.8, BORDER_HEIGHT = 0.8;

const double WHITE[] = {1, 1, 1};
const double YELLOW[] = {1, 1, 0};
const double RED[] = {1, 0, 0};

#endif