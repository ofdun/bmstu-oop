#ifndef MATRIXITERATOR_HPP
#define MATRIXITERATOR_HPP

#include "IteratorExceptions.h"
#include "MatrixIterator.h"

template <typename T> typename MatrixIterator<T>::reference MatrixIterator<T>::operator[](difference_type index) const
{
    validateInBounds(__FILE__, __FUNCTION__, __LINE__);
    validateExpired(__FILE__, __FUNCTION__, __LINE__);
    
    auto sharedPtr = ptr.lock();
    return *(sharedPtr.get() + index);
}

template <typename T> typename MatrixIterator<T>::reference MatrixIterator<T>::operator*() const
{
    validateInBounds(__FILE__, __FUNCTION__, __LINE__);
    validateExpired(__FILE__, __FUNCTION__, __LINE__);
    
    return *get();
}

template <typename T> typename MatrixIterator<T>::pointer MatrixIterator<T>::operator->() const
{
    validateInBounds(__FILE__, __FUNCTION__, __LINE__);
    validateExpired(__FILE__, __FUNCTION__, __LINE__);

    return get();
}

template <typename T> MatrixIterator<T> &MatrixIterator<T>::operator++() noexcept
{
    pos++;

    return *this;
}

template <typename T> MatrixIterator<T> MatrixIterator<T>::operator++(int) noexcept
{
    return ++*this;
}

template <typename T> MatrixIterator<T> &MatrixIterator<T>::operator--() noexcept
{
    pos--;

    return *this;
}

template <typename T> std::strong_ordering MatrixIterator<T>::operator<=>(const MatrixIterator &it) const noexcept
{
    return pos <=> it.pos;
}

template <typename T> MatrixIterator<T> MatrixIterator<T>::operator--(int) noexcept
{
    return --*this;
}

template <typename T>
typename MatrixIterator<T>::difference_type MatrixIterator<T>::operator-(const MatrixIterator &it) const
{
    return get() - it.get();
}

template <typename T>
MatrixIterator<T>::operator bool() const noexcept
{
    return pos >= 0 && pos < rows * columns;
}

template <typename T> MatrixIterator<T>::MatrixIterator()
{
    ptr.lock() = nullptr;
}

template <typename T> MatrixIterator<T> MatrixIterator<T>::operator+(difference_type n) const noexcept
{
    MatrixIterator it(*this);
    
    it += n;

    return it;
}

template <typename T> MatrixIterator<T> &MatrixIterator<T>::operator+=(difference_type n) noexcept
{
    pos += n;

    return *this;
}

template <typename T> MatrixIterator<T> MatrixIterator<T>::operator-(difference_type n) const noexcept
{
    MatrixIterator it(*this);
    
    it -= n;

    return it;
}

template <typename T> MatrixIterator<T> &MatrixIterator<T>::operator-=(difference_type n) noexcept
{
    pos -= n;

    return *this;
}

template <typename T> MatrixIterator<T> &MatrixIterator<T>::operator=(const MatrixIterator &it) noexcept
{
    pos = it.pos;
    rows = it.rows;
    columns = it.columns;
    ptr = it.ptr;

    return *this;
}

template <typename T> MatrixIterator<T>::MatrixIterator(Matrix<T> &m)
{
    pos = 0;
    rows = m.rows;
    columns = m.columns;
    ptr = m.data;
}

template <typename T> MatrixIterator<T>::MatrixIterator(const MatrixIterator &it)
{
    pos = it.pos;
    rows = it.rows;
    columns = it.columns;
    ptr = it.ptr;
}

template <typename T> bool MatrixIterator<T>::operator==(const MatrixIterator &it) const noexcept
{
    return pos == it.pos;
}

template <typename T> T *MatrixIterator<T>::get() const
{
    validateInBounds(__FILE__, __FUNCTION__, __LINE__);
    validateExpired(__FILE__, __FUNCTION__, __LINE__);
    
    auto sharedPtr = ptr.lock();
    return sharedPtr.get() + pos;
}

template <typename T>
void MatrixIterator<T>::validateInBounds(const char* filename, const char* funcName, int line) const
{
    if (pos < 0 || pos > columns * rows)
        throw OutOfBoundsException(filename, funcName, line, time(nullptr));
}

template <typename T>
void MatrixIterator<T>::validateExpired(const char* filename, const char* funcName, int line) const
{
    if (ptr.expired())
        throw ExpiredException(filename, funcName, line, time(nullptr));
}

#endif // MATRIXITERATOR_HPP