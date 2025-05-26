#include "MatrixModelImplementation.h"

std::unordered_map<size_t, std::unordered_map<size_t, bool>> MatrixModelImplementation::getMatrix() const
{
    return matrix;
}

std::vector<Edge> MatrixModelImplementation::getEdges() const
{
    std::vector<Edge> result;
    for (const auto &it1 : matrix)
        for (const auto &it2 : it1.second)
            if (it2.second)
                result.emplace_back(it1.first, it2.first);

    return result;
}

std::vector<Point> MatrixModelImplementation::getPoints() const
{
    return points;
}

void MatrixModelImplementation::setEdges(const std::vector<Edge> &edges)
{
    matrix.clear();
    for (const auto &e : edges)
        addEdge(e);
}

void MatrixModelImplementation::setPoints(const std::vector<Point> &points)
{
    this->points.clear();
    for (const auto &p : points)
        addPoint(p);
}

bool MatrixModelImplementation::addPoint(const Point &p)
{
    auto it = std::find(points.begin(), points.end(), p);

    if (it != points.end())
        return false;

    points.push_back(p);
    return true;
}

bool MatrixModelImplementation::removePoint(const Point &p)
{
    auto it = std::find(points.begin(), points.end(), p);

    if (it == points.end())
        return false;

    points.erase(it);
    return true;
}

bool MatrixModelImplementation::addEdge(const Edge &e)
{
    auto p1 = e.getFirst();
    auto p2 = e.getSecond();

    if (matrix.contains(p1) && matrix[p1].contains(p2) && matrix[p1][p2])
        return false;

    matrix[p1][p2] = true;
    matrix[p2][p1] = true;
    return true;
}

bool MatrixModelImplementation::removeEdge(const Edge &e)
{
    auto p1 = e.getFirst();
    auto p2 = e.getSecond();

    if (!matrix.contains(p1) || !matrix[p1].contains(p2) || !matrix[p1][p2])
        return false;

    matrix[p1][p2] = false;
    matrix[p2][p1] = false;
    return true;
}

void MatrixModelImplementation::transform(const Matrix<double> &transformationMatrix)
{
    for (auto &p : points)
        p.transform(transformationMatrix);
}

