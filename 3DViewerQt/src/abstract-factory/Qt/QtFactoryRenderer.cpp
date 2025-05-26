#include "QtFactoryRenderer.h"

#include "QtColor.h"
#include "QtPainter.h"
#include "QtPen.h"

std::shared_ptr<AbstractColor> QtFactoryRenderer::createColor()
{
    return std::make_shared<QtColor>(QColor(Qt::black));
}

std::shared_ptr<AbstractPen> QtFactoryRenderer::createPen()
{
    auto color = createColor();
    return std::make_shared<QtPen>(color);
}

std::shared_ptr<AbstractPainter> QtFactoryRenderer::createPainter()
{
    auto pen = createPen();
    return std::make_shared<QtPainter>(scene, pen);
}

