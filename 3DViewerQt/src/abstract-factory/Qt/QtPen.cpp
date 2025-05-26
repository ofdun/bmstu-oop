#include "QtPen.h"

void QtPen::setWidth(int width)
{
    pen.setWidth(width);
}

void QtPen::setColor(std::shared_ptr<AbstractColor> color)
{
    pen.setColor(color->getColor());
}

QtPen::QtPen(std::shared_ptr<AbstractColor> color)
{
    this->color = color;
    pen.setColor(color->getColor());
}

std::shared_ptr<AbstractColor> QtPen::getColor()
{
    return color;
}

int QtPen::getWidth()
{
    return pen.width();
}


