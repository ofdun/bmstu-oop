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
    using const_pointer = const T *;
    using const_reference = const T &;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::random_access_iterator_tag;
    
    MatrixConstIterator();
    explicit MatrixConstIterator(const Matrix<T> &m);
    MatrixConstIterator(const MatrixConstIterator &it);

    ~MatrixConstIterator() override = default;

    const_reference operator*() const;
    const_pointer operator->() const;
    const_reference operator[](difference_type index) const;

    MatrixConstIterator &operator=(const MatrixConstIterator &it) noexcept;

    MatrixConstIterator operator+(difference_type n) const noexcept;
    MatrixConstIterator &operator+=(difference_type n) noexcept;
    MatrixConstIterator operator-(difference_type n) const noexcept;
    MatrixConstIterator &operator-=(difference_type n) noexcept;

    MatrixConstIterator &operator++() noexcept;
    MatrixConstIterator operator++(int) noexcept;
    MatrixConstIterator &operator--() noexcept;
    MatrixConstIterator operator--(int) noexcept;

    difference_type operator-(const MatrixConstIterator &it) const noexcept;

    operator bool() const noexcept;

    std::strong_ordering operator<=>(const MatrixConstIterator &it) const noexcept;
    bool operator==(const MatrixConstIterator &it) const noexcept;

private:
    pointer get() const;
    std::weak_ptr<T[]> ptr;

    void validateInBounds(size_t index, const char *filename, const char *funcName, int line) const;
    void validateExpired(const char *filename, const char *funcName, int line) const;
};

template <typename T>
MatrixConstIterator<T> operator+(typename MatrixConstIterator<T>::difference_type n, const MatrixConstIterator<T> &it) noexcept
{
    return it + n;
}

static_assert(std::random_access_iterator<MatrixConstIterator<int>>);

#endif // MATRIXCONSTITERATOR_H