#pragma once

#include "AbstractManagerCreator.h"

#include <memory>

class CreatorManagerCreator
{
public:
    template <typename TCreator>
    static std::shared_ptr<AbstractManagerCreator> createCreator()
    {
        return std::make_shared<TCreator>();
    }
};