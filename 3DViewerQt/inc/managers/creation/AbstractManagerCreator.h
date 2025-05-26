#pragma once

#include <memory>

#include "AbstractManager.h"

class AbstractManagerCreator
{
public:
    virtual ~AbstractManagerCreator() = 0;

    virtual std::shared_ptr<AbstractManager> createProduct() = 0;
};