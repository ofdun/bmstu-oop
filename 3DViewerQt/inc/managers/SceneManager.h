#pragma once

#include "AbstractManager.h"
#include "AbstractScene.h"

using PtrScene = std::shared_ptr<AbstractScene>;

class SceneManager : public AbstractManager
{
public:
    ~SceneManager() override = default;

    SceneManager() = default;

    explicit SceneManager(PtrScene scene) : scene(scene)
    {
    }

    PtrScene getScene() const;
    void setScene(PtrScene scene);

private:
    PtrScene scene;
};