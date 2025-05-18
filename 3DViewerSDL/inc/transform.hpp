#ifndef TRANSFORM_HPP__
#define TRANSFORM_HPP__

#include "constants.hpp"

typedef struct
{
    double xModifier;
    double yModifier;
    double zModifier;
} scale;

typedef struct
{
    double xDegree;
    double yDegree;
    double zDegree;
} rotation;

typedef struct
{
    double x;
    double y;
    double z;
} offset;

typedef struct
{
    scale scale;
    rotation rotation;
    offset offset;
} transform;

scale transform_scaleInit(double x, double y, double z);
rotation transform_rotationInit(double x, double y, double z);
offset transform_offsetInit(double x, double y, double z);

transform transform_init(const scale &scale, const rotation &rotation, const offset &offset);

#endif // !TRANSFORM_HPP__
