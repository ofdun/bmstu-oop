#include "Facade.h"

#include "CreatorManagerCreator.h"
#include "LoadManagerCreator.h"
#include "ManagerSolution.h"
#include "QtFactoryRenderer.h"
#include "RenderManagerCreator.h"
#include "Scene.h"
#include "SceneElementsManagerCreator.h"
#include "SceneManagerCreator.h"
#include "SelectManagerCreator.h"
#include "TransformManagerCreator.h"

Facade::Facade(std::shared_ptr<QGraphicsScene> scene, std::shared_ptr<ManagerSolution> solution)
{
    loadManager = std::static_pointer_cast<LoadManager>(solution->create(LOAD)->createProduct());
    renderManager = std::static_pointer_cast<RenderManager>(solution->create(RENDER)->createProduct());
    sceneElementsManager = std::static_pointer_cast<SceneElementsManager>(
        solution->create(SCENE_ELEMENTS)->createProduct());
    sceneManager = std::static_pointer_cast<SceneManager>(solution->create(SCENE)->createProduct());
    selectManager = std::static_pointer_cast<SelectManager>(solution->create(SELECT)->createProduct());
    transformManager = std::static_pointer_cast<TransformManager>(solution->create(TRANSFORM)->createProduct());

    std::shared_ptr<AbstractFactoryRenderer> abstractFactoryRenderer = std::make_shared<QtFactoryRenderer>(scene);
    renderManager->setFactory(abstractFactoryRenderer);

    std::shared_ptr<AbstractScene> myScene = std::make_shared<Scene>();
    sceneManager->setScene(myScene);

    loadManager->setSceneManager(sceneManager);
    transformManager->setSelectManager(selectManager);
}


void Facade::execute(std::shared_ptr<AbstractCommand> command)
{
    command->setManagers(selectManager, sceneManager, loadManager,
                         renderManager, transformManager, sceneElementsManager);

    command->execute();
}
