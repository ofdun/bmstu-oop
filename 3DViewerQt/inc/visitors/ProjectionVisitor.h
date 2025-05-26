#pragma once

#include "AbstractVisitor.h"
#include "Point.h"

class ProjectionVisitor : public AbstractVisitor
{
public:
    ~ProjectionVisitor() override = default;

    explicit ProjectionVisitor(Point &p) : point(p)
    {
    }

    void visit(Model &model) override;
    void visit(PlainCamera &camera) override;

private:
    Point &point;
};