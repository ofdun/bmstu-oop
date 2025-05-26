#pragma once

#include <QPainter>
#include <QGraphicsScene>

#include "AbstractPainter.h"

class QtPainter : public AbstractPainter
{
public:
    ~QtPainter() override = default;
    QtPainter() = delete;
    QtPainter(std::shared_ptr<QGraphicsScene> scene, std::shared_ptr<AbstractPen> pen);

    void drawLine(const Point &p1, const Point &p2) override;
    void setPen(std::shared_ptr<AbstractPen> pen) override;

private:
    std::shared_ptr<QGraphicsScene> scene;
};