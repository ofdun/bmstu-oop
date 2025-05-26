#include "Edge.h"

size_t Edge::getFirst() const
{
    return first;
}

size_t Edge::getSecond() const
{
    return second;
}

void Edge::setFirst(size_t p)
{
    first = p;
}

void Edge::setSecond(size_t p)
{
    second = p;
}

bool Edge::operator==(const Edge &e) const
{
    return e.first == first && e.second == second;
}

