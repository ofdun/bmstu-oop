#include "point.hpp"

errCode point_inputFromFile(FILE *f, point &p)
{
    errCode rc = ERR_OK;
    
    if (rc == ERR_OK && !f)
        rc = ERR_WRONG_FILE;

    double x, y, z;
    if (rc == ERR_OK && fscanf(f, "%lf%lf%lf", &x, &y, &z) != 3)
        rc = ERR_WRONG_FILE_STRUCTURE;

    if (rc == ERR_OK)
    {
        p.x = x;
        p.y = y;
        p.z = z;
    }

    return rc;
}

errCode point_inputPoints(FILE *f, point *array, size_t count)
{
    errCode rc = ERR_OK;

    if (!array)
        rc = ERR_NULL_POINTER;
    
    for (size_t i = 0; rc == ERR_OK && i < count; i++)
        rc = point_inputFromFile(f, array[i]);

    return rc;
}

static void rotateXAxisPoint(point &p, const double degree)
{
    double y = p.y;
    double z = p.z;
    double cos = std::cos(degree);
    double sin = std::sin(degree);
    
    p.y = y * cos - z * sin;
    p.z = y * sin + z * cos;
}

static void rotateYAxisPoint(point &p, const double degree)
{
    double x = p.x;
    double z = p.z;
    double cos = std::cos(degree);
    double sin = std::sin(degree);

    p.x = x * cos + z * sin;
    p.z = -x * sin + z * cos;
}

static void rotateZAxisPoint(point &p, const double degree)
{
    double x = p.x;
    double y = p.y;
    double cos = std::cos(degree);
    double sin = std::sin(degree);

    p.x = x * cos - y * sin;
    p.y = x * sin + y * cos;
}

point point_addPoints(const point *points, size_t count)
{
    point p = point_init(0, 0, 0);
    
    for (size_t i = 0; i < count; i++)
        p = point_add(points[i], p);

    return p;
}

point point_add(const point &p1, const point &p2)
{
    return point_init(p1.x + p2.x, p1.y + p2.y, p1.z + p2.z);
}

point point_init(double x, double y, double z)
{
    point p;
    p.x = x;
    p.y = y;
    p.z = z;

    return p;
}

void point_rotatePoints(point *points, size_t count, const rotation &rotation)
{
    for (size_t i = 0; i < count; i++)
        point_rotate(points[i], rotation);
}

void point_rotate(point &p, const rotation &rotation)
{
    rotateXAxisPoint(p, rotation.xDegree);
    rotateYAxisPoint(p, rotation.yDegree);
    rotateZAxisPoint(p, rotation.zDegree);
}

void point_multiply(point &p, double num)
{
    p.x *= num;
    p.y *= num;
    p.z *= num;
}

void point_scalePoints(point *points, size_t count, const scale &scale)
{
    for (size_t i = 0; i < count; i++)
        point_scale(points[i], scale);
}

void point_scale(point &p, const scale &scale)
{
    p.x *= scale.xModifier;
    p.y *= scale.yModifier;
    p.z *= scale.zModifier;
}

void point_translatePoints(point *points, size_t count, const offset &offset)
{
    for (size_t i = 0; i < count; i++)
        point_translate(points[i], offset);
}

void point_translate(point &p, const offset &offset)
{
    p.x += offset.x;
    p.y += offset.y;
    p.z += offset.z;
}
