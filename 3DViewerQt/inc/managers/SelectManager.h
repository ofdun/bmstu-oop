#pragma once

#include <memory>

#include "AbstractManager.h"
#include "AbstractObject.h"
#include "Highlight.h"
#include "SceneManager.h"

class SelectManager : public AbstractManager
{
public:
    ~SelectManager() override = default;
    SelectManager();

    bool add(std::shared_ptr<SceneManager> sceneManager, size_t id) const;
    bool remove(size_t id) const;
    std::shared_ptr<Highlight> getSelected();

private:
    std::shared_ptr<Highlight> highlight;
};