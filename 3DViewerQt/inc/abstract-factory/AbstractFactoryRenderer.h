#pragma once

#include <memory>

#include "AbstractPainter.h"

class AbstractFactoryRenderer
{
public:
    virtual ~AbstractFactoryRenderer() = 0;

    virtual std::shared_ptr<AbstractPainter> createPainter() = 0;
    virtual std::shared_ptr<AbstractPen> createPen() = 0;
    virtual std::shared_ptr<AbstractColor> createColor() = 0;
};