#pragma once

#include "TransformManager.h"
#include "AbstractCommand.h"

class RemoveSceneObjectCommand : public AbstractCommand
{
private:
    using Action = bool (SceneElementsManager::*)(std::shared_ptr<AbstractScene>, size_t);

public:
    ~RemoveSceneObjectCommand() override = default;
    RemoveSceneObjectCommand() = delete;

    explicit RemoveSceneObjectCommand(size_t id) : id(id)
    {
    }

    void execute() override
    {
        ((*sceneElementsManager).*action)(sceneManager->getScene(), id);
    }

private:
    Action action = &SceneElementsManager::remove;
    size_t id;
};