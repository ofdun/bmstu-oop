#pragma once

#include <cstddef>

class AbstractMatrixIterator
{
public:
    using size_type = size_t;

    virtual ~AbstractMatrixIterator() = 0;

protected:
    size_type columns = 0;
    size_type rows = 0;
    size_type pos = 0;
};