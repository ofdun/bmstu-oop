#pragma once

#include <QGraphicsScene>

#include "AbstractFactoryRenderer.h"

class QtFactoryRenderer : public AbstractFactoryRenderer
{
public:
    ~QtFactoryRenderer() override = default;
    QtFactoryRenderer() = delete;

    explicit QtFactoryRenderer(std::shared_ptr<QGraphicsScene> scene) : scene(scene)
    {
    }

    std::shared_ptr<AbstractPainter> createPainter() override;
    std::shared_ptr<AbstractPen> createPen() override;
    std::shared_ptr<AbstractColor> createColor() override;

private:
    std::shared_ptr<QGraphicsScene> scene;
};