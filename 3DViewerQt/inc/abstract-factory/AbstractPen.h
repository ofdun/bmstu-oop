#pragma once

#include <memory>
#include "AbstractColor.h"

class AbstractPen
{
public:
    virtual ~AbstractPen() = 0;

    virtual std::shared_ptr<AbstractColor> getColor() = 0;
    virtual int getWidth() = 0;
    virtual void setColor(std::shared_ptr<AbstractColor> color) = 0;
    virtual void setWidth(int width) = 0;

protected:
    std::shared_ptr<AbstractColor> color;
};