#pragma once

#include <memory>

#include "AbstractSceneParserCreator.h"

class CreatorAbstractSceneParserCreator
{
public:
    template <typename TCreator>
    static std::shared_ptr<AbstractSceneParserCreator> createCreator()
    {
        return std::make_shared<TCreator>();
    }
};