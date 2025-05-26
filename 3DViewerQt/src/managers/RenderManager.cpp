#include "RenderManager.h"

#include "AbstractFactoryRenderer.h"
#include "ManagerExceptions.h"
#include "QtFactoryRenderer.h"
#include "RenderVisitor.h"

#include <iostream>

void RenderManager::render(std::shared_ptr<AbstractScene> scene, std::shared_ptr<Camera> camera) const
{
    if (factory == nullptr)
        throw AbstractFactoryNotSetException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    if (camera == nullptr)
        throw NoCameraSetException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    auto painter = factory->createPainter();
    std::shared_ptr<AbstractVisitor> visitor = std::make_shared<RenderVisitor>(painter, camera);
    for (auto it = scene->begin(); it != scene->end(); ++it)
        it->get()->accept(visitor);
}

void RenderManager::setFactory(std::shared_ptr<AbstractFactoryRenderer> factory)
{
    this->factory = factory;
}
