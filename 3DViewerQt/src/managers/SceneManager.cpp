#include "SceneManager.h"

PtrScene SceneManager::getScene() const
{
    return scene;
}

void SceneManager::setScene(PtrScene scene)
{
    this->scene = scene;
}
