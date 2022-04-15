#ifndef PLANE_H
#define PLANE_H

#include "config.h"

const double *const POLY_COLOR = WHITE;
const double POLY_WIDTH = 100, POLY_HEIGHT = 100;
const double POLY_POS_X = 0, POLY_POS_Y = 0;

class Plane
{
public:
    double x, y, width, height;
    const double *color;
    Plane(double, double);
    Plane(double, double, double, double);
    Plane(double, double, const double * const);
    Plane(double, double, double, double, const double * const);
    virtual void show() = 0;
};

#endif