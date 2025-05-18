#ifndef MATRIXCONSTREVERSEITERATOR_HPP
#define MATRIXCONSTREVERSEITERATOR_HPP

#include "MatrixConstReverseIterator.h"

template <typename T>
MatrixConstReverseIterator<T>::MatrixConstReverseIterator()
{
    iter = const_iterator();
}

template <typename T>
MatrixConstReverseIterator<T>::MatrixConstReverseIterator(const Matrix<value_type> &m)
{
    iter = const_iterator(m);
    rows = m.getRows();
    columns = m.getColumns();
    pos = rows * columns;
}

template <typename T>
MatrixConstReverseIterator<T>::MatrixConstReverseIterator(const MatrixConstReverseIterator &it)
{
    pos = it.pos;
    rows = it.rows;
    columns = it.columns;
    iter = it.iter;
}

template <typename T>
typename MatrixConstReverseIterator<T>::const_reference MatrixConstReverseIterator<T>::operator*() const
{
    return *get();
}

template <typename T>
typename MatrixConstReverseIterator<T>::const_pointer MatrixConstReverseIterator<T>::operator->() const
{
    return get();
}

template <typename T>
typename MatrixConstReverseIterator<T>::const_reference MatrixConstReverseIterator<T>::operator[](difference_type index) const
{
    return iter[rows * columns - index - 1];
}

template <typename T>
MatrixConstReverseIterator<T> & MatrixConstReverseIterator<T>::operator=(const MatrixConstReverseIterator &it) noexcept
{
    pos = it.pos;
    rows = it.rows;
    columns = it.columns;
    iter = it.iter;

    return *this;
}

template <typename T>
MatrixConstReverseIterator<T> MatrixConstReverseIterator<T>::operator+(difference_type n) const noexcept
{
    MatrixConstReverseIterator it(*this);

    it.iter -= n;

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

    it.iter += n;

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
    MatrixConstReverseIterator copy(*this);
    ++*this;
    return copy;
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
    MatrixConstReverseIterator copy(*this);
    --*this;
    return copy;
}

template <typename T>
typename MatrixConstReverseIterator<T>::difference_type MatrixConstReverseIterator<T>::operator-(
    const MatrixConstReverseIterator &it) const noexcept
{
    return it.iter - iter;
}

template <typename T>
MatrixConstReverseIterator<T>::operator bool() const noexcept
{
    return static_cast<bool>(iter);
}

template <typename T>
std::strong_ordering MatrixConstReverseIterator<T>::operator<=>(const MatrixConstReverseIterator &it) const noexcept
{
    return pos <=> it.pos;
}

template <typename T>
bool MatrixConstReverseIterator<T>::operator==(const MatrixConstReverseIterator &it) const noexcept
{
    return pos == it.pos && iter == it.iter;
}

template <typename T>
typename MatrixConstReverseIterator<T>::pointer MatrixConstReverseIterator<T>::get() const
{
    return (iter + static_cast<difference_type>(pos) - difference_type{1}).operator->();
}

#endif //MATRIXCONSTREVERSEITERATOR_HPP
