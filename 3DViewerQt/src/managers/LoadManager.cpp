#include "LoadManager.h"

#include "CameraParserCSVCreator.h"
#include "CameraParserTXTCreator.h"
#include "CreatorAbstractCameraParserCreator.h"
#include "CreatorAbstractFileLoaderCreator.h"
#include "CreatorAbstractModelParserCreator.h"
#include "CreatorAbstractSceneParserCreator.h"
#include "CreatorModelBuilderDirector.h"
#include "EdgeListModelDirector.h"
#include "FileLoaderCSVCreator.h"
#include "FileLoaderSolution.h"
#include "FileLoaderTXTCreator.h"
#include "ManagerExceptions.h"
#include "MatrixModelDirector.h"
#include "ModelParserCSVCreator.h"
#include "ModelParserTXTCreator.h"
#include "SceneLoader.h"
#include "SceneParserCSVCreator.h"
#include "SceneParserTXTCreator.h"

void LoadManager::loadScene(const std::filesystem::path &path, CallbackFunc callback)
{
    if (sceneManager == nullptr)
        throw SceneManagerNotSetException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    auto fileLoaderSolution = std::make_shared<FileLoaderSolution>();
    auto sceneParserSolution = std::make_shared<SceneParserSolution>();
    auto modelParserSolution = std::make_shared<ModelParserSolution>();
    auto cameraParserSolution = std::make_shared<CameraParserSolution>();
    auto modelBuilderDirectorSolution = std::make_shared<ModelBuilderDirectorSolution>();

    registerCreators(sceneParserSolution, modelParserSolution,
                     cameraParserSolution, fileLoaderSolution,
                     modelBuilderDirectorSolution);

    auto sceneLoader = std::make_shared<SceneLoader>(fileLoaderSolution, sceneParserSolution, cameraParserSolution,
                                                     modelParserSolution, modelBuilderDirectorSolution, path);
    auto scene = sceneLoader->loadScene(callback);
    sceneManager->setScene(scene);
}

void LoadManager::setSceneManager(std::shared_ptr<SceneManager> sceneManager)
{
    this->sceneManager = sceneManager;
}

void LoadManager::registerCreators(std::shared_ptr<SceneParserSolution> sceneParserSolution,
                                   std::shared_ptr<ModelParserSolution> modelParserSolution,
                                   std::shared_ptr<CameraParserSolution> cameraParserSolution,
                                   std::shared_ptr<FileLoaderSolution> fileLoaderSolution,
                                   std::shared_ptr<ModelBuilderDirectorSolution> modelBuilderDirectorSolution)
{
    modelBuilderDirectorSolution->registrate(EDGELIST,
                                             CreatorModelDirectorCreator::createCreator<EdgeListModelDirector>);
    modelBuilderDirectorSolution->registrate(MATRIX,
                                             CreatorModelDirectorCreator::createCreator<MatrixModelDirector>);

    std::vector<std::string> keys = {".csv", ".txt"};

    std::vector sceneParserCreators = {&CreatorAbstractSceneParserCreator::createCreator<SceneParserCSVCreator>,
                                       &CreatorAbstractSceneParserCreator::createCreator<SceneParserTXTCreator>};

    std::vector modelParserCreators = {&CreatorAbstractModelParserCreator::createCreator<ModelParserCSVCreator>,
                                       &CreatorAbstractModelParserCreator::createCreator<ModelParserTXTCreator>};

    std::vector cameraParserCreators = {&CreatorAbstractCameraParserCreator::createCreator<CameraParserCSVCreator>,
                                        &CreatorAbstractCameraParserCreator::createCreator<CameraParserTXTCreator>};

    std::vector fileLoaderCreators = {&CreatorAbstractFileLoaderCreator::createCreator<FileLoaderCSVCreator>,
                                      &CreatorAbstractFileLoaderCreator::createCreator<FileLoaderTXTCreator>};

    for (auto i = 0; i < keys.size(); i++)
    {
        sceneParserSolution->registrate(keys[i], sceneParserCreators[i]);
        modelParserSolution->registrate(keys[i], modelParserCreators[i]);
        cameraParserSolution->registrate(keys[i], cameraParserCreators[i]);
        fileLoaderSolution->registrate(keys[i], fileLoaderCreators[i]);
    }
}
