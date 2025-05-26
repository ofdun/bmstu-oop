#pragma once

#include <memory>
#include <filesystem>

#include "AbstractSceneParser.h"

class AbstractSceneParserCreator
{
public:
    virtual ~AbstractSceneParserCreator() = 0;

    virtual std::shared_ptr<AbstractSceneParser> create(std::shared_ptr<std::istream> stream) = 0;
};
