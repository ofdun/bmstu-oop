#pragma once

class AbstractColor
{
public:
    virtual ~AbstractColor() = 0;

    virtual unsigned int getColor() const = 0;
    virtual void setColor(unsigned int color) = 0;
};