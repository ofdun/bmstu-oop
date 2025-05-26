#pragma once


#include <unordered_map>
#include <vector>

#include "AbstractModelImplementation.h"
#include "Edge.h"
#include "Point.h"

class MatrixModelImplementation : public AbstractModelImplementation
{
public:
    ~MatrixModelImplementation() override = default;
    MatrixModelImplementation() = default;

    explicit MatrixModelImplementation(const std::unordered_map<size_t, std::unordered_map<size_t, bool>> &matrix) :
        matrix(matrix)
    {
    }

    [[nodiscard]] std::unordered_map<size_t, std::unordered_map<size_t, bool>> getMatrix() const;

    std::vector<Edge> getEdges() const override;
    std::vector<Point> getPoints() const override;
    void setEdges(const std::vector<Edge> &edges) override;
    void setPoints(const std::vector<Point> &points) override;
    bool addPoint(const Point &p);
    bool removePoint(const Point &p);
    bool addEdge(const Edge &e);
    bool removeEdge(const Edge &e);
    void transform(const Matrix<double> &transformationMatrix) override;

private:
    std::unordered_map<size_t, std::unordered_map<size_t, bool>> matrix;
    std::vector<Point> points;
};