#pragma once

#include "RenderManager.h"
#include "AbstractCommand.h"

class RenderSceneCommand : public AbstractCommand
{
private:
    using Action = void (RenderManager::*)(std::shared_ptr<AbstractScene>, std::shared_ptr<Camera>) const;

public:
    ~RenderSceneCommand() override = default;
    RenderSceneCommand() = default;

    void execute() override
    {
        ((*renderManager).*action)(sceneManager->getScene(), sceneElementsManager->getActiveCamera());
    }

private:
    Action action = &RenderManager::render;
    PtrObject obj;
};