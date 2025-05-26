#pragma once

#include <memory>

#include "AbstractManagerCreator.h"
#include "SelectManager.h"

class SelectManagerCreator : public AbstractManagerCreator
{
public:
    std::shared_ptr<AbstractManager> createProduct() override
    {
        return std::make_shared<SelectManager>();
    };
};