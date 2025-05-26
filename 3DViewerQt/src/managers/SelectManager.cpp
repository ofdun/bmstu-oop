#include "SelectManager.h"

SelectManager::SelectManager()
{
    highlight = std::make_shared<Highlight>();
}

#include <iostream>

bool SelectManager::add(std::shared_ptr<SceneManager> sceneManager, size_t id) const
{
    auto scene = sceneManager->getScene();
    auto it = std::ranges::find_if(scene->begin(), scene->end(), [id](const auto &obj) {
        return obj->id() == id;
    });

    if (it != scene->end())
        return highlight->add({*it});
    return false;
}

bool SelectManager::remove(size_t id) const
{
    return highlight->remove(id);
}

std::shared_ptr<Highlight> SelectManager::getSelected()
{
    return highlight;
}

