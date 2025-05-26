#pragma once

#include <memory>
#include <istream>
#include <enums.h>

class AbstractSceneParser
{
public:
    virtual ~AbstractSceneParser() = 0;
    virtual objType getObjectType() = 0;

protected:
    std::shared_ptr<std::istream> stream;
};
