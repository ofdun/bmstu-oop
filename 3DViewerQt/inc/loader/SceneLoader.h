#pragma once


#include <memory>
#include <filesystem>

#include "AbstractCameraParser.h"
#include "AbstractModelParser.h"
#include "AbstractScene.h"
#include "AbstractSceneParser.h"
#include "AbstractStreamLoader.h"
#include "CameraParserSolution.h"
#include "FileLoaderSolution.h"
#include "ModelParserSolution.h"
#include "ObjectSelector.h"
#include "SceneParserSolution.h"

class SceneLoader
{
private:
    using CallbackFunc = std::function<void(size_t, objType)>;

public:
    SceneLoader(std::shared_ptr<FileLoaderSolution> fileLoaderSolution,
                std::shared_ptr<SceneParserSolution> sceneParserSolution,
                std::shared_ptr<CameraParserSolution> cameraParserSolution,
                std::shared_ptr<ModelParserSolution> modelParserSolution,
                std::shared_ptr<ModelBuilderDirectorSolution> modelBuilderDirectorSolution,
                const std::filesystem::path &path);

    std::shared_ptr<AbstractScene> loadScene(CallbackFunc callback) const;

private:
    std::shared_ptr<AbstractSceneParser> sceneParser;
    std::shared_ptr<ObjectSelector> objectSelector;
};