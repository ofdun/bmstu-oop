#pragma once

#include <memory>

#include "AbstractManagerCreator.h"
#include "RenderManager.h"

class RenderManagerCreator : public AbstractManagerCreator
{
public:
    std::shared_ptr<AbstractManager> createProduct() override
    {
        return std::make_shared<RenderManager>();
    };
};