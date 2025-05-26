#pragma once

#include "Point.h"
#include "Matrix.h"

class PlainCameraImplementation
{
public:
    PlainCameraImplementation(const Point &pos) : pos(pos)
    {
    }

    Point getPos() const;
    Point getUp() const;
    Point getRight() const;
    Point getDir() const;
    void setPos(const Point &pos);
    void setUp(const Point &up);
    void setRight(const Point &right);
    void setDir(const Point &angle);
    void transform(const Matrix<double> &transformationMatrix);

private:
    Point pos;
    Point up = Point(0, 0, 1);
    Point dir = Point(0, 1, 0);
    Point right = Point(1, 0, 0);
};