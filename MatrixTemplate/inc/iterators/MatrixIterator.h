#ifndef MATRIXITERATOR_H
#define MATRIXITERATOR_H

#include <memory>

#include "BaseMatrixIterator.h"

template <Storable T> class Matrix;

template <typename T> class MatrixIterator final : public BaseMatrixIterator
{
public:
    using value_type = T;
    using pointer = T *;
    using reference = T &;
    using difference_type = std::ptrdiff_t;

    MatrixIterator();
    explicit MatrixIterator(Matrix<value_type> &m);
    MatrixIterator(const MatrixIterator &it);

    ~MatrixIterator() override = default;

    reference operator*() const;
    pointer operator->() const;
    reference operator[](difference_type index) const;

    MatrixIterator &operator=(const MatrixIterator &it) noexcept;

    MatrixIterator operator+(difference_type n) const noexcept;
    MatrixIterator &operator+=(difference_type n) noexcept;
    MatrixIterator operator-(difference_type n) const noexcept;
    MatrixIterator &operator-=(difference_type n) noexcept;

    MatrixIterator &operator++() noexcept;
    MatrixIterator operator++(int) noexcept;
    MatrixIterator &operator--() noexcept;
    MatrixIterator operator--(int) noexcept;

    difference_type operator-(const MatrixIterator &it) const;

    operator bool() const noexcept;

    std::strong_ordering operator<=>(const MatrixIterator &it) const noexcept;
    bool operator==(const MatrixIterator &it) const noexcept;

protected:
    pointer get() const;
    
private:
    std::weak_ptr<T[]> ptr;
    
    void validateInBounds(const char* filename, const char* funcName, int line) const;
    void validateExpired(const char* filename, const char* funcName, int line) const;
};

template <typename T>
MatrixIterator<T> operator+(typename MatrixIterator<T>::difference_type n, const MatrixIterator<T> &it) noexcept
{
    return it + n;
}

static_assert(std::random_access_iterator<MatrixIterator<int>>);

#endif // MATRIXITERATOR_H