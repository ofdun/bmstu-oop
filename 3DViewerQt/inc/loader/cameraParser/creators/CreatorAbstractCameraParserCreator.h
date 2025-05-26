#pragma once

#include <memory>

#include "AbstractCameraParserCreator.h"

class CreatorAbstractCameraParserCreator
{
public:
    template <typename TCreator>
    static std::shared_ptr<AbstractCameraParserCreator> createCreator()
    {
        return std::make_shared<TCreator>();
    }
};