#pragma once

#include <memory>
#include <AbstractCameraParserCreator.h>

#include "AbstractModelParserCreator.h"

class CreatorAbstractModelParserCreator
{
public:
    template <typename TCreator>
    static std::shared_ptr<AbstractModelParserCreator> createCreator()
    {
        return std::make_shared<TCreator>();
    }
};