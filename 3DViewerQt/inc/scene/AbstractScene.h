#pragma once

#include "AbstractObject.h"

#include <vector>

class AbstractScene
{
public:
    using value_type = PtrObject;
    using size_type = size_t;
    using iterator = std::vector<value_type>::const_iterator;

    virtual ~AbstractScene() = 0;

    virtual iterator begin() const = 0;
    virtual iterator end() const = 0;
    virtual bool addObject(PtrObject obj) = 0;
    virtual bool removeObject(size_t id) = 0;

protected:
    std::vector<value_type> container;
};