#ifndef MATRIXCONSTITERATOR_H
#define MATRIXCONSTITERATOR_H

#include "BaseMatrixIterator.h"

#include "MatrixConcepts.h"

template <Storable T> class Matrix;

template <typename T> class MatrixConstIterator final : public BaseMatrixIterator
{
public:
    using value_type = T;
    using pointer = const T *;
    using constPointer = const T *;
    using constReference = const T &;
    using difference_type = std::ptrdiff_t;

    MatrixConstIterator();
    explicit MatrixConstIterator(const Matrix<T> &m);
    MatrixConstIterator(const MatrixConstIterator &it);

    ~MatrixConstIterator() override = default;

    constReference operator*() const;
    constPointer operator->() const;
    constReference operator[](int index) const;

    MatrixConstIterator &operator=(const MatrixConstIterator &it) noexcept;

    MatrixConstIterator operator+(difference_type n) const noexcept;
    MatrixConstIterator &operator+=(difference_type n) noexcept;
    MatrixConstIterator operator-(difference_type n) const noexcept;
    MatrixConstIterator &operator-=(difference_type n) noexcept;

    MatrixConstIterator &operator++() noexcept;
    MatrixConstIterator operator++(int) noexcept;
    MatrixConstIterator &operator--() noexcept;
    MatrixConstIterator operator--(int) noexcept;

    difference_type operator-(const MatrixConstIterator &it) const;

    operator bool() const noexcept;

    std::strong_ordering operator<=>(const MatrixConstIterator &it) const noexcept;
    bool operator==(const MatrixConstIterator &it) const noexcept;

protected:
    pointer get() const;

private:
    std::weak_ptr<T[]> ptr;

    void validateInBounds(const char *filename, const char *funcName, int line) const;
    void validateExpired(const char *filename, const char *funcName, int line) const;
};

template <typename T>
MatrixConstIterator<T> operator+(typename MatrixConstIterator<T>::difference_type n, const MatrixConstIterator<T> &it) noexcept
{
    return it + n;
}

static_assert(std::random_access_iterator<MatrixConstIterator<int>>);

#endif // MATRIXCONSTITERATOR_H