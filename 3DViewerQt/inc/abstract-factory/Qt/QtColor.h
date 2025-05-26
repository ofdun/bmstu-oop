#pragma once

#include <QColor>

#include "AbstractColor.h"

class QtColor : public AbstractColor
{
public:
    ~QtColor() override = default;

    explicit QtColor(QColor color) : color(color)
    {
    }

    unsigned int getColor() const override;
    void setColor(unsigned int color) override;

private:
    QColor color;
};