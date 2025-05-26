#pragma once

#include <memory>

#include "AbstractManagerCreator.h"
#include "TransformManager.h"

class TransformManagerCreator : public AbstractManagerCreator
{
public:
    std::shared_ptr<AbstractManager> createProduct() override
    {
        return std::make_shared<TransformManager>();
    };
};