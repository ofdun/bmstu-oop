#pragma once


#include <vector>

#include "AbstractModelImplementation.h"
#include "Edge.h"
#include "Point.h"
#include "Matrix.h"

class EdgeListModelImplementation : public AbstractModelImplementation
{
public:
    ~EdgeListModelImplementation() override = default;
    EdgeListModelImplementation() = default;

    EdgeListModelImplementation(const std::vector<Edge> &edges, const std::vector<Point> &points) : edges(edges),
        points(points)
    {
    }

    [[nodiscard]] std::vector<Edge> getEdges() const override;
    [[nodiscard]] std::vector<Point> getPoints() const override;
    void setEdges(const std::vector<Edge> &edge) override;
    void setPoints(const std::vector<Point> &points) override;
    void addEdge(const Edge &e);
    void addPoint(const Point &p);
    void transform(const Matrix<double> &transformationMatrix) override;
    bool removeEdge(const Edge &e);
    bool removePoint(const Point &p);

private:
    void transformPoints(const Matrix<double> &transformationMatrix);
    void moveToCenter(const Point &center);
    Point getCenter() const;

    std::vector<Edge> edges;
    std::vector<Point> points;
};