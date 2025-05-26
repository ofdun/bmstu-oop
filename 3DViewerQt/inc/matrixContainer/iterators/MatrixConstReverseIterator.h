#ifndef MATRIXCONSTREVERSEITERATOR_H
#define MATRIXCONSTREVERSEITERATOR_H

#include "AbstractMatrixIterator.h"
#include "MatrixConstIterator.h"
#include "MatrixConcepts.h"
#include "IteratorExceptions.h"

#include <memory>
#include <iterator>

template <Storable T> class Matrix;

template <typename T> class MatrixConstReverseIterator final : public AbstractMatrixIterator
{
public:
    using value_type = T;
    using pointer = const T *;
    using const_pointer = const T *;
    using const_reference = const T &;
    using const_iterator = MatrixConstIterator<T>;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::random_access_iterator_tag;
    
    MatrixConstReverseIterator();
    explicit MatrixConstReverseIterator(const Matrix<value_type> &m);
    MatrixConstReverseIterator(const MatrixConstReverseIterator &it);

    ~MatrixConstReverseIterator() override = default;

    const_reference operator*() const;
    const_pointer operator->() const;
    const_reference operator[](difference_type index) const;

    MatrixConstReverseIterator &operator=(const MatrixConstReverseIterator &it) noexcept;
    
    MatrixConstReverseIterator operator+(difference_type n) const noexcept;
    MatrixConstReverseIterator &operator+=(difference_type n) noexcept;
    MatrixConstReverseIterator operator-(difference_type n) const noexcept;
    MatrixConstReverseIterator &operator-=(difference_type n) noexcept;
    
    MatrixConstReverseIterator &operator++() noexcept;
    MatrixConstReverseIterator operator++(int) noexcept;
    MatrixConstReverseIterator &operator--() noexcept;
    MatrixConstReverseIterator operator--(int) noexcept;
    
    difference_type operator-(const MatrixConstReverseIterator &it) const noexcept;
    
    operator bool() const noexcept;
    
    std::strong_ordering operator<=>(const MatrixConstReverseIterator &it) const noexcept;
    bool operator==(const MatrixConstReverseIterator &it) const noexcept;

private:
    pointer get() const;
    const_iterator iter;
};

template <typename T>
MatrixConstReverseIterator<T> operator+(typename MatrixConstReverseIterator<T>::difference_type n, const MatrixConstReverseIterator<T> &it) noexcept
{
    return it + n;
}

static_assert(std::random_access_iterator<MatrixConstReverseIterator<int>>);

#endif //MATRIXCONSTREVERSEITERATOR_H
