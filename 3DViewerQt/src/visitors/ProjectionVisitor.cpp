#include "ProjectionVisitor.h"

#include "PlainCamera.h"

double dotProduct(const Point &p1, const Point &p2)
{
    return p1.getX() * p2.getX() + p1.getY() * p2.getY() + p1.getZ() * p2.getZ();
}

void ProjectionVisitor::visit(Model &model)
{
}

void ProjectionVisitor::visit(PlainCamera &camera)
{
    auto impl = camera.impl;
    auto copy = point.clone();

    Point relative = Point(copy.getX() - impl->getPos().getX(),
                           copy.getY() - impl->getPos().getY(),
                           copy.getZ() - impl->getPos().getZ());

    double x_cam = dotProduct(relative, impl->getRight());
    double y_cam = dotProduct(relative, impl->getUp());
    double z_cam = dotProduct(relative, impl->getDir());

    copy.setZ(z_cam);

    if (fabs(z_cam) < __DBL_EPSILON__)
        z_cam = 1e-6;

    double px = x_cam / z_cam;
    double py = y_cam / z_cam;

    auto width = 746;
    auto height = 776;

    double screen_x = (px + 1) * width / 2;
    double screen_y = (1 - py) * height / 2;

    copy.setX(screen_x);
    copy.setY(screen_y);

    point = copy;
}

