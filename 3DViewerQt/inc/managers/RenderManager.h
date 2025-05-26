#pragma once

#include <memory>

#include "AbstractFactoryRenderer.h"

#include "AbstractManager.h"
#include "AbstractScene.h"
#include "Camera.h"

class RenderManager : public AbstractManager
{
public:
    ~RenderManager() override = default;
    RenderManager() = default;

    explicit RenderManager(std::shared_ptr<AbstractFactoryRenderer> factory) : factory(factory)
    {
    }

    void render(std::shared_ptr<AbstractScene> scene, std::shared_ptr<Camera> camera) const;
    void setFactory(std::shared_ptr<AbstractFactoryRenderer> factory);

private:
    std::shared_ptr<AbstractFactoryRenderer> factory;
};