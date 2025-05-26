#include "QtColor.h"

unsigned int QtColor::getColor() const
{
    return color.rgb();
}

void QtColor::setColor(unsigned int color)
{
    this->color.setRgb(color);
}
