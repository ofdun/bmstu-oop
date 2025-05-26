#pragma once

#include "TransformManager.h"
#include "AbstractCommand.h"

class SelectSceneObjectCommand : public AbstractCommand
{
private:
    using Action = bool (SelectManager::*)(std::shared_ptr<SceneManager> sceneManager, size_t id) const;

public:
    ~SelectSceneObjectCommand() override = default;
    SelectSceneObjectCommand() = delete;

    explicit SelectSceneObjectCommand(size_t id) : id(id)
    {
    }

    void execute() override
    {
        ((*selectManager).*action)(sceneManager, id);
    }

private:
    Action action = &SelectManager::add;
    size_t id;
};