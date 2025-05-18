#ifndef POINT_HPP__
#define POINT_HPP__

#include "transform.hpp"
#include "errors.hpp"

#include <stdio.h>
#include <cmath>

typedef struct
{
    double x;
    double y;
    double z;
} point;

void point_scale(point &p, const scale &scale);
void point_scalePoints(point *points, size_t count, const scale &scale);
void point_translate(point &p, const offset &offset);
void point_translatePoints(point *points, size_t count, const offset &offset);
void point_rotate(point &p, const rotation &rotation);
void point_rotatePoints(point *points, size_t count, const rotation &rotation);
void point_multiply(point &p, double num);
errCode point_inputPoints(FILE *f, point *array, size_t count);
errCode point_inputFromFile(FILE *f, point &p);
point point_addPoints(const point *points, size_t count);
point point_add(const point &p1, const point &p2);
point point_init(double x, double y, double z);

#endif // !POINT_HPP__
