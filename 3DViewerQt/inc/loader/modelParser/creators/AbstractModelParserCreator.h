#pragma once


#include <memory>
#include <filesystem>
#include <istream>

#include "AbstractModelParser.h"

class AbstractModelParserCreator
{
public:
    virtual ~AbstractModelParserCreator() = 0;

    virtual std::shared_ptr<AbstractModelParser> create(std::shared_ptr<std::istream> stream) = 0;
};
