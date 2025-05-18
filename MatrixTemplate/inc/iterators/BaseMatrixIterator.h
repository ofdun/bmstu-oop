#ifndef BASEMATRIXITERATOR_H
#define BASEMATRIXITERATOR_H

#include <cstddef>

class BaseMatrixIterator
{
public:
    using size_type = size_t;

    virtual ~BaseMatrixIterator() = 0;

protected:
    size_type columns = 0;
    size_type rows = 0;
    size_type pos = 0;
};

#endif // BASEMATRIXITERATOR_H