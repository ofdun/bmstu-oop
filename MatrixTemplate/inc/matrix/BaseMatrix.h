#ifndef BASEMATRIX_H
#define BASEMATRIX_H

#include <utility>

class BaseMatrix
{
public:
    using sizeType = size_t;

    virtual ~BaseMatrix() = default;

    [[nodiscard]] virtual std::pair<sizeType, sizeType> size() const noexcept = 0;

protected:
    sizeType rows = 0;
    sizeType columns = 0;
};

#endif // BASEMATRIX_H