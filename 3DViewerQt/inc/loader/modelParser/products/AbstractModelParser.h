#pragma once

#include <memory>
#include <istream>

#include "Edge.h"
#include "Point.h"

class AbstractModelParser
{
public:
    virtual ~AbstractModelParser() = 0;

    virtual void setStream(std::shared_ptr<std::istream> stream) = 0;
    virtual bool anyPointsLeft() = 0;
    virtual bool anyEdgesLeft() = 0;
    virtual Point getNextPoint() = 0;
    virtual Edge getNextEdge() = 0;

protected:
    std::shared_ptr<std::istream> stream;
};
