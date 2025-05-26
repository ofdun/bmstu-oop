#pragma once

#include "Matrix.h"

class Point
{
public:
    Point(double x, double y, double z) : x(x), y(y), z(z)
    {
    }

    [[nodiscard]] double getX() const;
    [[nodiscard]] double getY() const;
    [[nodiscard]] double getZ() const;
    void setX(double x);
    void setY(double y);
    void setZ(double z);
    Point clone() const;
    void transform(const Matrix<double> &m);

    bool operator==(const Point &p) const;
    std::partial_ordering operator<=>(const Point &p) const;

private:
    double x;
    double y;
    double z;
};