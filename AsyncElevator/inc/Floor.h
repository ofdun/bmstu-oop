#pragma once

enum Direction
{
    UP = 1,
    NONE = 0,
    DOWN = -1,
};

struct Floor
{
public:
    int floor;
    Direction direction;
};
