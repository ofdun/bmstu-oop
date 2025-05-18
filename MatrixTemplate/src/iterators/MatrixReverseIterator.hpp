#ifndef MATRIXREVERSEITERATOR_HPP
#define MATRIXREVERSEITERATOR_HPP

#include "MatrixReverseIterator.h"

template <typename T>
MatrixReverseIterator<T>::MatrixReverseIterator()
{
    forwardIterator = iterator();
}

template <typename T>
MatrixReverseIterator<T>::MatrixReverseIterator(Matrix<value_type> &m)
{
    forwardIterator = iterator(m);
    rows = m.getRows();
    columns = m.getColumns();
    pos = rows * columns;
}

template <typename T>
MatrixReverseIterator<T> &MatrixReverseIterator<T>::operator=(const MatrixReverseIterator &it) noexcept
{
    pos = it.pos;
    rows = it.rows;
    columns = it.columns;
    forwardIterator = it.forwardIterator;

    return *this;
}

template <typename T>
MatrixReverseIterator<T> MatrixReverseIterator<T>::operator+(difference_type n) const noexcept
{
    MatrixReverseIterator it(*this);

    it.forwardIterator -= n;

    return it;
}

template <typename T>
MatrixReverseIterator<T> &MatrixReverseIterator<T>::operator+=(difference_type n) noexcept
{
    pos -= n;

    return *this;
}

template <typename T>
MatrixReverseIterator<T> MatrixReverseIterator<T>::operator-(difference_type n) const noexcept
{
    MatrixReverseIterator it(*this);

    it.forwardIterator += n;

    return it;
}

template <typename T>
MatrixReverseIterator<T> &MatrixReverseIterator<T>::operator-=(difference_type n) noexcept
{
    pos += n;

    return *this;
}

template <typename T>
MatrixReverseIterator<T> &MatrixReverseIterator<T>::operator++() noexcept
{
    pos--;

    return *this;
}

template <typename T>
MatrixReverseIterator<T> MatrixReverseIterator<T>::operator++(int) noexcept
{
    MatrixReverseIterator copy(*this);
    ++*this;
    return copy;
}

template <typename T>
MatrixReverseIterator<T> &MatrixReverseIterator<T>::operator--() noexcept
{
    pos++;

    return *this;
}

template <typename T>
MatrixReverseIterator<T> MatrixReverseIterator<T>::operator--(int) noexcept
{
    MatrixReverseIterator copy(*this);
    --*this;
    return copy;
}

template <typename T>
typename MatrixReverseIterator<T>::difference_type MatrixReverseIterator<T>::operator-(
    const MatrixReverseIterator &it) const noexcept
{
    return it.forwardIterator - forwardIterator;
}

template <typename T>
MatrixReverseIterator<T>::operator bool() const noexcept
{
    return static_cast<bool>(forwardIterator);
}

template <typename T>
std::strong_ordering MatrixReverseIterator<T>::operator<=>(const MatrixReverseIterator &it) const noexcept
{
    return pos <=> it.pos;
}

template <typename T>
bool MatrixReverseIterator<T>::operator==(const MatrixReverseIterator &it) const noexcept
{
    return pos == it.pos && forwardIterator == it.forwardIterator;
}

template <typename T>
typename MatrixReverseIterator<T>::pointer MatrixReverseIterator<T>::get() const
{
    return (forwardIterator + static_cast<difference_type>(pos) - difference_type{1}).operator->();
}


template <typename T>
MatrixReverseIterator<T>::MatrixReverseIterator(const MatrixReverseIterator &it)
{
    forwardIterator = it.forwardIterator;
    rows = it.rows;
    columns = it.columns;
    pos = rows * columns;
}

template <typename T>
typename MatrixReverseIterator<T>::reference MatrixReverseIterator<T>::operator*() const
{
    return *get();
}

template <typename T>
typename MatrixReverseIterator<T>::pointer MatrixReverseIterator<T>::operator->() const
{
    return get();
}

template <typename T>
typename MatrixReverseIterator<T>::reference MatrixReverseIterator<T>::operator[](difference_type index) const
{
    return forwardIterator[rows * columns - index - 1];
}

#endif //MATRIXREVERSEITERATOR_HPP