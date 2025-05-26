#pragma once

#include "RenderManager.h"
#include "AbstractCommand.h"

class LoadSceneCommand : public AbstractCommand
{
private:
    using CallbackFunc = std::function<void(size_t, objType)>;
    using Action = void (LoadManager::*)(const std::filesystem::path &path, CallbackFunc callback);

public:
    ~LoadSceneCommand() override = default;

    explicit LoadSceneCommand(std::filesystem::path path, CallbackFunc callback) : path(path), callback(callback)
    {
    }

    void execute() override
    {
        ((*loadManager).*action)(path, callback);
    }

private:
    Action action = &LoadManager::loadScene;
    CallbackFunc callback;
    std::filesystem::path path;
};