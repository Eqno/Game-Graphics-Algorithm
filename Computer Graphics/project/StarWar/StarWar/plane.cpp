#include "plane.h"

Plane::Plane(double x, double y)
{
    this->x = x, this->y = y;
    this->width = POLY_WIDTH;
    this->height = POLY_HEIGHT;
    this->color = POLY_COLOR;
}
Plane::Plane(double x, double y, double w, double h)
{
    this->x = x, this->y = y;
    this->width = w;
    this->height = h;
    this->color = POLY_COLOR;
}
Plane::Plane(double x, double y, const double * const c)
{
    this->x = x, this->y = y;
    this->width = POLY_WIDTH;
    this->height = POLY_HEIGHT;
    this->color = c;
}
Plane::Plane(double x, double y, double w, double h, const double * const c)
{
    this->x = x, this->y = y;
    this->width = w;
    this->height = h;
    this->color = c;
}


