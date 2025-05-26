#pragma once

#include <memory>
#include <vector>

#include "AbstractVisitor.h"
#include "Edge.h"
#include "Point.h"

class AbstractModelImplementation
{
public:
    virtual ~AbstractModelImplementation() = 0;

    virtual std::vector<Edge> getEdges() const = 0;
    virtual std::vector<Point> getPoints() const = 0;
    virtual void setEdges(const std::vector<Edge> &edges) = 0;
    virtual void setPoints(const std::vector<Point> &points) = 0;
    virtual void transform(const Matrix<double> &transformationMatrix) = 0;
};