#ifndef MATRIXREVERSEITERATOR_H
#define MATRIXREVERSEITERATOR_H

#include "BaseMatrixIterator.h"
#include "MatrixIterator.h"
#include "MatrixConcepts.h"
#include "IteratorExceptions.h"

#include <memory>
#include <iterator>

template <Storable T> class Matrix;

template <typename T> class MatrixReverseIterator final : public BaseMatrixIterator
{
public:
    using value_type = T;
    using pointer = T *;
    using reference = T &;
    using iterator = MatrixIterator<T>;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::random_access_iterator_tag;
    
    MatrixReverseIterator();
    explicit MatrixReverseIterator(Matrix<value_type> &m);
    MatrixReverseIterator(const MatrixReverseIterator &it);

    ~MatrixReverseIterator() override = default;

    reference operator*() const;
    pointer operator->() const;
    reference operator[](difference_type index) const;

    MatrixReverseIterator &operator=(const MatrixReverseIterator &it) noexcept;
    
    MatrixReverseIterator operator+(difference_type n) const noexcept;
    MatrixReverseIterator &operator+=(difference_type n) noexcept;
    MatrixReverseIterator operator-(difference_type n) const noexcept;
    MatrixReverseIterator &operator-=(difference_type n) noexcept;
    
    MatrixReverseIterator &operator++() noexcept;
    MatrixReverseIterator operator++(int) noexcept;
    MatrixReverseIterator &operator--() noexcept;
    MatrixReverseIterator operator--(int) noexcept;
    
    difference_type operator-(const MatrixReverseIterator &it) const noexcept;
    
    operator bool() const noexcept;
    
    std::strong_ordering operator<=>(const MatrixReverseIterator &it) const noexcept;
    bool operator==(const MatrixReverseIterator &it) const noexcept;

private:
    pointer get() const;
    iterator forwardIterator;
};

template <typename T>
MatrixReverseIterator<T> operator+(typename MatrixReverseIterator<T>::difference_type n, const MatrixReverseIterator<T> &it) noexcept
{
    return it + n;
}

static_assert(std::random_access_iterator<MatrixReverseIterator<int>>);

#endif //MATRIXREVERSEITERATOR_H
