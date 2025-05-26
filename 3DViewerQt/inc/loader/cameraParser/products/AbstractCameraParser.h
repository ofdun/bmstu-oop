#pragma once

#include <memory>
#include <istream>

#include "Point.h"

class AbstractCameraParser
{
public:
    virtual ~AbstractCameraParser() = 0;

    virtual void setStream(std::shared_ptr<std::istream> stream) = 0;
    virtual Point getDirection() = 0;
    virtual Point getPosition() = 0;

protected:
    std::shared_ptr<std::istream> stream;
};