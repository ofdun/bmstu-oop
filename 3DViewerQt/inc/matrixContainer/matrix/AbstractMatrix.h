#pragma once

#include <utility>

class AbstractMatrix
{
public:
    using size_type = size_t;

    virtual ~AbstractMatrix() = default;

    [[nodiscard]] virtual size_type size() const noexcept = 0;

protected:
    size_t rows = 0;
    size_t columns = 0;
};
