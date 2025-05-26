#include "Point.h"

#include <cmath>

double Point::getX() const
{
    return x;
}

double Point::getY() const
{
    return y;
}

double Point::getZ() const
{
    return z;
}

void Point::setX(double x)
{
    this->x = x;
}

void Point::setY(double y)
{
    this->y = y;
}

void Point::setZ(double z)
{
    this->z = z;
}

Point Point::clone() const
{
    return Point(x, y, z);
}

void Point::transform(const Matrix<double> &m)
{
    Matrix<double> cur = {{x, y, z, 1}};
    Matrix<double> new_ = cur * m;

    x = new_[0][0];
    y = new_[0][1];
    z = new_[0][2];
}

bool Point::operator==(const Point &p) const
{
    return std::abs(p.x - x) < __DBL_EPSILON__
           && std::abs(p.y - y) < __DBL_EPSILON__
           && std::abs(p.z - z) < __DBL_EPSILON__;
}

std::partial_ordering Point::operator<=>(const Point &p) const
{
    return x <=> p.x;
}

