#pragma once

#include <memory>


#include "LoadManager.h"
#include "RenderManager.h"
#include "SceneManager.h"
#include "SelectManager.h"
#include "TransformManager.h"
#include "SceneElementsManager.h"

class AbstractCommand
{
public:
    virtual ~AbstractCommand() = 0;
    virtual void execute() = 0;

    void setManagers(std::shared_ptr<SelectManager> se, std::shared_ptr<SceneManager> sc,
                     std::shared_ptr<LoadManager> l, std::shared_ptr<RenderManager> r,
                     std::shared_ptr<TransformManager> t, std::shared_ptr<SceneElementsManager> sem)
    {
        selectManager = se;
        sceneManager = sc;
        sceneElementsManager = sem;
        loadManager = l;
        renderManager = r;
        transformManager = t;
    }

protected:
    std::shared_ptr<SelectManager> selectManager;
    std::shared_ptr<SceneManager> sceneManager;
    std::shared_ptr<SceneElementsManager> sceneElementsManager;
    std::shared_ptr<LoadManager> loadManager;
    std::shared_ptr<RenderManager> renderManager;
    std::shared_ptr<TransformManager> transformManager;
};