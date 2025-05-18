#ifndef BASEMATRIXITERATOR_H
#define BASEMATRIXITERATOR_H

#include <cstddef>

class BaseMatrixIterator
{
public:
    using sizeType = size_t;

    virtual ~BaseMatrixIterator() = 0;

protected:
    sizeType columns = 0;
    sizeType rows = 0;
    sizeType pos = 0;
};

#endif // BASEMATRIXITERATOR_H