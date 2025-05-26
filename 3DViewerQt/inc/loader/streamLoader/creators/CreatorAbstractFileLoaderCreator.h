#pragma once

#include <memory>

#include "AbstractFileLoaderCreator.h"

class CreatorAbstractFileLoaderCreator
{
public:
    template <typename TCreator>
    static std::shared_ptr<AbstractFileLoaderCreator> createCreator()
    {
        return std::make_shared<TCreator>();
    }
};