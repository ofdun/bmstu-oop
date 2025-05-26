#pragma once

#include "TransformManager.h"
#include "AbstractCommand.h"

class UnselectSceneObjectCommand : public AbstractCommand
{
private:
    using Action = bool (SelectManager::*)(size_t) const;

public:
    ~UnselectSceneObjectCommand() override = default;
    UnselectSceneObjectCommand() = delete;

    explicit UnselectSceneObjectCommand(size_t id) : id(id)
    {
    }

    void execute() override
    {
        ((*selectManager).*action)(id);
    }

private:
    Action action = &SelectManager::remove;
    size_t id;
};