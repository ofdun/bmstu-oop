#pragma once

#include "AbstractManager.h"
#include "AbstractObject.h"
#include "Camera.h"
#include "SceneManager.h"

class SceneElementsManager : public AbstractManager
{
public:
    bool add(std::shared_ptr<AbstractScene> scene, PtrObject obj);
    bool remove(std::shared_ptr<AbstractScene> scene, size_t id);
    std::shared_ptr<Camera> getActiveCamera();
    void setActiveCamera(std::shared_ptr<AbstractScene> scene, size_t id);

private:
    std::shared_ptr<Camera> camera;
};