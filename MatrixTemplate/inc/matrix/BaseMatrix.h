#ifndef BASEMATRIX_H
#define BASEMATRIX_H

#include <utility>

class BaseMatrix
{
public:
    using size_type = size_t;

    virtual ~BaseMatrix() = default;

    [[nodiscard]] virtual size_type size() const noexcept = 0;

protected:
    size_t rows = 0;
    size_t columns = 0;
};

#endif // BASEMATRIX_H