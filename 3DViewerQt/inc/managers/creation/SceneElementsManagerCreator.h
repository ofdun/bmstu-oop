#pragma once

#include <memory>

#include "AbstractManagerCreator.h"
#include "SceneElementsManager.h"

class SceneElementsManagerCreator : public AbstractManagerCreator
{
public:
    std::shared_ptr<AbstractManager> createProduct() override
    {
        return std::make_shared<SceneElementsManager>();
    };
};