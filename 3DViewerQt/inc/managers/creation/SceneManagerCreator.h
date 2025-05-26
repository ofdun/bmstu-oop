#pragma once

#include <memory>

#include "AbstractManagerCreator.h"
#include "SceneManager.h"

class SceneManagerCreator : public AbstractManagerCreator
{
public:
    std::shared_ptr<AbstractManager> createProduct() override
    {
        return std::make_shared<SceneManager>();
    };
};