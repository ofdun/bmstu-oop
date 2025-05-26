#include "SceneLoader.h"

#include "AbstractModelBuilder.h"
#include "EdgeListModelBuilder.h"
#include "Scene.h"
#include "StreamFileLoader.h"

SceneLoader::SceneLoader(std::shared_ptr<FileLoaderSolution> fileLoaderSolution,
                         std::shared_ptr<SceneParserSolution> sceneParserSolution,
                         std::shared_ptr<CameraParserSolution> cameraParserSolution,
                         std::shared_ptr<ModelParserSolution> modelParserSolution,
                         std::shared_ptr<ModelBuilderDirectorSolution> modelBuilderDirectorSolution,
                         const std::filesystem::path &path)
{
    auto extension = path.extension();

    auto fileLoader = fileLoaderSolution->create(extension)->create(path);
    std::shared_ptr<AbstractStreamLoader> streamLoader = std::make_shared<StreamFileLoader>(fileLoader);
    sceneParser = sceneParserSolution->create(extension)->create(streamLoader->getStream());
    auto cameraParser = cameraParserSolution->create(extension)->create(streamLoader->getStream());
    auto modelParser = modelParserSolution->create(extension)->create(streamLoader->getStream());

    auto cameraDirector = std::make_shared<CameraDirector>(cameraParser);

    std::shared_ptr<AbstractModelDirector> modelDirector = modelBuilderDirectorSolution->create(EDGELIST, modelParser);

    objectSelector = std::make_shared<ObjectSelector>(modelDirector, cameraDirector);
}

std::shared_ptr<AbstractScene> SceneLoader::loadScene(CallbackFunc callback) const
{
    std::shared_ptr<AbstractScene> scene = std::make_shared<Scene>();

    auto curType = sceneParser->getObjectType();
    while (curType != NONE)
    {
        auto object = objectSelector->create(curType);
        scene->addObject(object);
        callback(object->id(), curType);
        curType = sceneParser->getObjectType();
    }

    return scene;
}
