#pragma once

#include <memory>

#include "AbstractManagerCreator.h"
#include "LoadManager.h"

class LoadManagerCreator : public AbstractManagerCreator
{
public:
    std::shared_ptr<AbstractManager> createProduct() override
    {
        return std::make_shared<LoadManager>();
    };
};