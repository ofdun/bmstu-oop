#include "Scene.h"

AbstractScene::iterator Scene::begin() const
{
    return container.begin();
}

AbstractScene::iterator Scene::end() const
{
    return container.end();
}

bool Scene::removeObject(size_t id)
{
    auto it = std::ranges::find_if(*this, [id](const auto &obj) {
        return obj->id() == id;
    });

    if (it == end())
        return false;

    container.erase(it);
    return true;
}

bool Scene::addObject(PtrObject obj)
{
    size_t id = obj->id();
    auto it = std::ranges::find_if(*this, [id](const auto &obj) {
        return obj->id() == id;
    });

    if (it != end())
        return false;

    container.push_back(obj);
    return true;
}

