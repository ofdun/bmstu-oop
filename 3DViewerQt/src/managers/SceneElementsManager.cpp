#include "SceneElementsManager.h"

bool SceneElementsManager::add(std::shared_ptr<AbstractScene> scene, PtrObject obj)
{
    return scene->addObject(obj);
}

bool SceneElementsManager::remove(std::shared_ptr<AbstractScene> scene, size_t id)
{
    return scene->removeObject(id);
}

std::shared_ptr<Camera> SceneElementsManager::getActiveCamera()
{
    return camera;
}

void SceneElementsManager::setActiveCamera(std::shared_ptr<AbstractScene> scene, size_t id)
{
    bool found = false;
    auto it = std::ranges::find_if(scene->begin(), scene->end(), [id](const auto &obj) {
        return obj->id() == id;
    });

    if (it == scene->end())
        camera = nullptr;
    else
        camera = std::static_pointer_cast<Camera>(*it);
}

