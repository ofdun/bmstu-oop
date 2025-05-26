#pragma once

#include <memory>

#include "AbstractPen.h"
#include "Point.h"

class AbstractPainter
{
public:
    virtual ~AbstractPainter() = 0;

    virtual void drawLine(const Point &p1, const Point &p2) = 0;
    virtual void setPen(std::shared_ptr<AbstractPen> pen) = 0;

protected:
    std::shared_ptr<AbstractPen> pen;
};