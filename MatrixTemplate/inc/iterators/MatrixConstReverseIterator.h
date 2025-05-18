#ifndef MATRIXCONSTREVERSEITERATOR_H
#define MATRIXCONSTREVERSEITERATOR_H

#include "BaseMatrixIterator.h"
#include "MatrixConstIterator.h"
#include "MatrixConcepts.h"
#include "IteratorExceptions.h"

#include <memory>
#include <iterator>

template <Storable T> class Matrix;

template <typename T> class MatrixConstReverseIterator final : public BaseMatrixIterator
{
public:
    using value_type = T;
    using pointer = const T *;
    using constPointer = const T *;
    using constReference = const T &;
    using constIterator = MatrixConstIterator<T>;
    using difference_type = std::ptrdiff_t;
    
    MatrixConstReverseIterator();
    explicit MatrixConstReverseIterator(const Matrix<value_type> &m);
    MatrixConstReverseIterator(const MatrixConstReverseIterator &it);

    ~MatrixConstReverseIterator() override = default;

    constReference operator*() const;
    constPointer operator->() const;
    constReference operator[](sizeType index) const;

    MatrixConstReverseIterator &operator=(const MatrixConstReverseIterator &it) noexcept;
    
    MatrixConstReverseIterator operator+(difference_type n) const noexcept;
    MatrixConstReverseIterator &operator+=(difference_type n) noexcept;
    MatrixConstReverseIterator operator-(difference_type n) const noexcept;
    MatrixConstReverseIterator &operator-=(difference_type n) noexcept;
    
    MatrixConstReverseIterator &operator++() noexcept;
    MatrixConstReverseIterator operator++(int) noexcept;
    MatrixConstReverseIterator &operator--() noexcept;
    MatrixConstReverseIterator operator--(int) noexcept;
    
    difference_type operator-(const MatrixConstReverseIterator &it) const;
    
    operator bool() const noexcept;
    
    std::strong_ordering operator<=>(const MatrixConstReverseIterator &it) const noexcept;
    bool operator==(const MatrixConstReverseIterator &it) const noexcept;

protected:
    pointer get() const;

private:
    constIterator forwardIterator;
};

template <typename T>
MatrixConstReverseIterator<T> operator+(typename MatrixConstReverseIterator<T>::difference_type n, const MatrixConstReverseIterator<T> &it) noexcept
{
    return it + n;
}

static_assert(std::random_access_iterator<MatrixConstReverseIterator<int>>);

#endif //MATRIXCONSTREVERSEITERATOR_H
