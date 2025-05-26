#include "QtPainter.h"

QtPainter::QtPainter(std::shared_ptr<QGraphicsScene> scene, std::shared_ptr<AbstractPen> pen)
{
    this->scene = scene;
    this->pen = pen;
}

void QtPainter::setPen(std::shared_ptr<AbstractPen> pen)
{
    this->pen = pen;
}

void QtPainter::drawLine(const Point &p1, const Point &p2)
{
    auto pen_ = QPen();
    pen_.setColor(pen->getColor()->getColor());
    pen_.setWidth(pen->getWidth());

    QLineF line(p1.getX(), p1.getY(), p2.getX(), p2.getY());
    scene->addLine(line, pen_);
}

