#include "RenderVisitor.h"

#include "Model.h"
#include "NotImplementedException.h"
#include "ProjectionVisitor.h"

void RenderVisitor::visit(Model &model)
{
    auto impl = model.impl;
    auto edges = impl->getEdges();
    auto points = impl->getPoints();

    std::vector<Point> projected;

    for (const auto &p : points)
    {
        auto clone = p.clone();
        camera->accept(std::make_shared<ProjectionVisitor>(clone));
        projected.push_back(clone);
    }

    for (const auto &edge : edges)
    {
        auto p1 = projected[edge.getFirst()];
        auto p2 = projected[edge.getSecond()];

        if (p1.getZ() <= 1 || p2.getZ() <= 1)
            continue;

        painter->drawLine(p1, p2);
    }
}

void RenderVisitor::visit(PlainCamera &camera)
{
}
