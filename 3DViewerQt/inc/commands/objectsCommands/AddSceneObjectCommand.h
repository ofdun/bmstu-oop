#pragma once

#include "TransformManager.h"
#include "AbstractCommand.h"

class AddSceneObjectCommand : public AbstractCommand
{
private:
    using Action = bool (SceneElementsManager::*)(std::shared_ptr<AbstractScene>, PtrObject);

public:
    ~AddSceneObjectCommand() override = default;
    AddSceneObjectCommand() = delete;

    explicit AddSceneObjectCommand(PtrObject obj) : obj(obj)
    {
    }

    void execute() override
    {
        ((*sceneElementsManager).*action)(sceneManager->getScene(), obj);
    }

private:
    Action action = &SceneElementsManager::add;
    PtrObject obj;
};