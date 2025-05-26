#pragma once

#include <istream>
#include <memory>

class AbstractStreamLoader
{
public:
    virtual ~AbstractStreamLoader() = 0;

    virtual std::shared_ptr<std::istream> getStream() = 0;
    virtual void closeStream() = 0;

protected:
    std::shared_ptr<std::istream> stream;
};
