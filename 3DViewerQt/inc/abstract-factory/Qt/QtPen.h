#pragma once

#include <QPen>

#include "AbstractPen.h"

class QtPen : public AbstractPen
{
public:
    ~QtPen() override = default;
    QtPen(std::shared_ptr<AbstractColor> color);

    std::shared_ptr<AbstractColor> getColor() override;
    int getWidth() override;
    void setColor(std::shared_ptr<AbstractColor> color) override;
    void setWidth(int width) override;

private:
    QPen pen;
};
