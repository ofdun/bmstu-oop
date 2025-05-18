#include "transform.hpp"

scale transform_scaleInit(double x, double y, double z)
{
    scale s;

    s.xModifier = x;
    s.yModifier = y;
    s.zModifier = z;

    return s;
}

rotation transform_rotationInit(double x, double y, double z)
{
    rotation r;

    r.xDegree = x;
    r.yDegree = y;
    r.zDegree = z;

    return r;
}

offset transform_offsetInit(double x, double y, double z)
{
    offset o;

    o.x = x;
    o.y = y;
    o.z = z;

    return o;
}

transform transform_init(const scale &scale, const rotation &rotation, const offset &offset)
{
    transform tr;

    tr.scale = scale;
    tr.rotation = rotation;
    tr.offset = offset;

    return tr;
}
