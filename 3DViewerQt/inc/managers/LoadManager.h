#pragma once

#include "AbstractManager.h"
#include "CameraParserSolution.h"
#include "FileLoaderSolution.h"
#include "ModelBuilderDirectorSolution.h"
#include "ModelParserSolution.h"
#include "SceneManager.h"
#include "SceneParserSolution.h"

#include <filesystem>

class LoadManager : public AbstractManager
{
private:
    using CallbackFunc = std::function<void(size_t, objType)>;

public:
    ~LoadManager() override = default;

    LoadManager() = default;

    LoadManager(std::shared_ptr<SceneManager> sceneManager) : sceneManager(sceneManager)
    {
    }

    void loadScene(const std::filesystem::path &path, CallbackFunc callback);
    void setSceneManager(std::shared_ptr<SceneManager> sceneManager);

private:
    static void registerCreators(std::shared_ptr<SceneParserSolution> sceneParserSolution,
                                 std::shared_ptr<ModelParserSolution> modelParserSolution,
                                 std::shared_ptr<CameraParserSolution> cameraParserSolution,
                                 std::shared_ptr<FileLoaderSolution> fileLoaderSolution,
                                 std::shared_ptr<ModelBuilderDirectorSolution> modelBuilderDirectorSolution);

    std::shared_ptr<SceneManager> sceneManager;
};