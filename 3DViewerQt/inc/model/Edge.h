#pragma once

#include <cstddef>

class Edge
{
public:
    Edge(size_t first, size_t second) : first(first), second(second)
    {
    }

    [[nodiscard]] size_t getFirst() const;
    [[nodiscard]] size_t getSecond() const;
    void setFirst(size_t p);
    void setSecond(size_t p);

    bool operator==(const Edge &e) const;

private:
    size_t first;
    size_t second;
};