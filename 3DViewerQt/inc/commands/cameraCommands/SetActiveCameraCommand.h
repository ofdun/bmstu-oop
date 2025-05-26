#pragma once

#include "AbstractCommand.h"

class SetActiveCameraCommand : public AbstractCommand
{
private:
    using Action = void (SceneElementsManager::*)(std::shared_ptr<AbstractScene> scene, size_t);

public:
    ~SetActiveCameraCommand() override = default;

    explicit SetActiveCameraCommand(size_t id) : id(id)
    {
    }

    void execute() override
    {
        ((*sceneElementsManager).*action)(sceneManager->getScene(), id);
    }

private:
    Action action = &SceneElementsManager::setActiveCamera;
    size_t id;
};