#ifndef MATRIXCONSTREVERSEITERATOR_HPP
#define MATRIXCONSTREVERSEITERATOR_HPP

#include "MatrixConstReverseIterator.h"

template <typename T>
MatrixConstReverseIterator<T>::MatrixConstReverseIterator()
{
    forwardIterator = constIterator();
}

template <typename T>
MatrixConstReverseIterator<T>::MatrixConstReverseIterator(const Matrix<value_type> &m)
{
    forwardIterator = constIterator(m);
    std::tie(rows, columns) = m.size();
    pos = rows * columns;
}

template <typename T>
MatrixConstReverseIterator<T>::MatrixConstReverseIterator(const MatrixConstReverseIterator &it)
{
    pos = it.pos;
    rows = it.rows;
    columns = it.columns;
    forwardIterator = it.forwardIterator;

    return *this;
}

template <typename T>
typename MatrixConstReverseIterator<T>::constReference MatrixConstReverseIterator<T>::operator*() const
{
    return *get();
}

template <typename T>
typename MatrixConstReverseIterator<T>::constPointer MatrixConstReverseIterator<T>::operator->() const
{
    return get();
}

template <typename T>
typename MatrixConstReverseIterator<T>::constReference MatrixConstReverseIterator<T>::operator[](sizeType index) const
{
    return forwardIterator[rows * columns - index - 1];
}

template <typename T>
MatrixConstReverseIterator<T> & MatrixConstReverseIterator<T>::operator=(const MatrixConstReverseIterator &it) noexcept
{
    pos = it.pos;
    rows = it.rows;
    columns = it.columns;
    forwardIterator = it.forwardIterator;

    return *this;
}

template <typename T>
MatrixConstReverseIterator<T> MatrixConstReverseIterator<T>::operator+(difference_type n) const noexcept
{
    MatrixConstReverseIterator it(*this);

    it.forwardIterator -= n;

    return it;
}

template <typename T>
MatrixConstReverseIterator<T> & MatrixConstReverseIterator<T>::operator+=(difference_type n) noexcept
{
    pos -= n;

    return *this;
}

template <typename T>
MatrixConstReverseIterator<T> MatrixConstReverseIterator<T>::operator-(difference_type n) const noexcept
{
    MatrixConstReverseIterator it(*this);

    it.forwardIterator += n;

    return it;
}

template <typename T>
MatrixConstReverseIterator<T> & MatrixConstReverseIterator<T>::operator-=(difference_type n) noexcept
{
    pos += n;

    return *this;
}

template <typename T>
MatrixConstReverseIterator<T> & MatrixConstReverseIterator<T>::operator++() noexcept
{
    pos--;

    return *this;
}

template <typename T>
MatrixConstReverseIterator<T> MatrixConstReverseIterator<T>::operator++(int) noexcept
{
    return ++*this;
}

template <typename T>
MatrixConstReverseIterator<T> & MatrixConstReverseIterator<T>::operator--() noexcept
{
    pos++;

    return *this;
}

template <typename T>
MatrixConstReverseIterator<T> MatrixConstReverseIterator<T>::operator--(int) noexcept
{
    return --*this;
}

template <typename T>
typename MatrixConstReverseIterator<T>::difference_type MatrixConstReverseIterator<T>::operator-(
    const MatrixConstReverseIterator &it) const
{
    return it.forwardIterator - forwardIterator;
}

template <typename T>
MatrixConstReverseIterator<T>::operator bool() const noexcept
{
    return static_cast<bool>(forwardIterator);
}

template <typename T>
std::strong_ordering MatrixConstReverseIterator<T>::operator<=>(const MatrixConstReverseIterator &it) const noexcept
{
    return pos <=> it.pos;
}

template <typename T>
bool MatrixConstReverseIterator<T>::operator==(const MatrixConstReverseIterator &it) const noexcept
{
    return pos == it.pos;
}

template <typename T>
typename MatrixConstReverseIterator<T>::pointer MatrixConstReverseIterator<T>::get() const
{
    return (forwardIterator + static_cast<difference_type>(pos) - difference_type{1}).operator->();
}

#endif //MATRIXCONSTREVERSEITERATOR_HPP
