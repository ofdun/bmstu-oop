#pragma once

#include "AbstractCameraParser.h"

class AbstractCameraParserCreator
{
public:
    virtual ~AbstractCameraParserCreator() = 0;

    virtual std::shared_ptr<AbstractCameraParser> create(std::shared_ptr<std::istream> stream) = 0;
};