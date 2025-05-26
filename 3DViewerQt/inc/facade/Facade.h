#pragma once

#include <QGraphicsScene>

#include "AbstractCommand.h"
#include "ManagerSolution.h"

class Facade
{
public:
    Facade(std::shared_ptr<QGraphicsScene> scene, std::shared_ptr<ManagerSolution> solution);

    void execute(std::shared_ptr<AbstractCommand> command);

private:
    std::shared_ptr<LoadManager> loadManager;
    std::shared_ptr<RenderManager> renderManager;
    std::shared_ptr<SceneElementsManager> sceneElementsManager;
    std::shared_ptr<SceneManager> sceneManager;
    std::shared_ptr<SelectManager> selectManager;
    std::shared_ptr<TransformManager> transformManager;
};