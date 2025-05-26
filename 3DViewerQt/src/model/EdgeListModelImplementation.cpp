#include "EdgeListModelImplementation.h"

std::vector<Edge> EdgeListModelImplementation::getEdges() const
{
    return edges;
}

std::vector<Point> EdgeListModelImplementation::getPoints() const
{
    return points;
}

void EdgeListModelImplementation::setEdges(const std::vector<Edge> &edges)
{
    this->edges.clear();
    for (const auto &e : edges)
        addEdge(e);
}

void EdgeListModelImplementation::setPoints(const std::vector<Point> &points)
{
    this->points.clear();
    for (const auto &p : points)
        addPoint(p);
}

void EdgeListModelImplementation::addEdge(const Edge &e)
{
    edges.push_back(e);
}

void EdgeListModelImplementation::addPoint(const Point &p)
{
    points.push_back(p);
}

void EdgeListModelImplementation::transform(const Matrix<double> &transformationMatrix)
{
    // for (const auto &p : points)
    // {
    //     std::cout << p.getX() << ' ' << p.getY() << ' ' << p.getZ() << std::endl;
    // }
    // std::cout << "\n\n\n";

    auto center = getCenter();
    auto start = Point(-center.getX(), -center.getY(), -center.getZ());
    moveToCenter(start);
    transformPoints(transformationMatrix);
    moveToCenter(center);

    // for (const auto &p : points)
    // {
    //     std::cout << p.getX() << ' ' << p.getY() << ' ' << p.getZ() << std::endl;
    // }
}

bool EdgeListModelImplementation::removeEdge(const Edge &e)
{
    auto it = std::ranges::find(edges, e);
    if (it != edges.end())
    {
        edges.erase(it);
        return true;
    }

    return false;
}

bool EdgeListModelImplementation::removePoint(const Point &p)
{
    auto it = std::ranges::find(points, p);
    if (it != points.end())
    {
        points.erase(it);
        return true;
    }

    return false;
}

void EdgeListModelImplementation::transformPoints(const Matrix<double> &transformationMatrix)
{
    for (auto &p : points)
        p.transform(transformationMatrix);
}

void EdgeListModelImplementation::moveToCenter(const Point &center)
{
    Matrix<double> m = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {center.getX(), center.getY(), center.getZ(), 1},
    };
    transformPoints(m);
}

Point EdgeListModelImplementation::getCenter() const
{
    double x_ = 0, y_ = 0, z_ = 0;
    size_t count = points.size();

    if (count == 0)
        return Point(x_, y_, z_);

    for (const auto &p : points)
    {
        x_ += p.getX();
        y_ += p.getY();
        z_ += p.getZ();
    }

    return Point(x_ / count, y_ / count, z_ / count);
}

