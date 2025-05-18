#ifndef MATRIXCONSTITERATOR_HPP
#define MATRIXCONSTITERATOR_HPP

#include "IteratorExceptions.h"
#include "MatrixConstIterator.h"

template <typename T> MatrixConstIterator<T>::MatrixConstIterator()
{
    ptr.lock() = nullptr;
}

template <typename T> MatrixConstIterator<T>::MatrixConstIterator(const Matrix<T> &m)
{
    pos = 0;
    rows = m.rows;
    columns = m.columns;
    ptr = m.data;
}

template <typename T> std::strong_ordering MatrixConstIterator<T>::operator<=>(const MatrixConstIterator &it) const noexcept
{
    return pos <=> it.pos;
}

template <typename T> MatrixConstIterator<T>::MatrixConstIterator(const MatrixConstIterator &it)
{
    pos = it.pos;
    rows = it.rows;
    columns = it.columns;
    ptr = it.ptr;
}

template <typename T> typename MatrixConstIterator<T>::pointer MatrixConstIterator<T>::get() const
{
    validateInBounds(pos, __FILE__, __FUNCTION__, __LINE__);
    validateExpired(__FILE__, __FUNCTION__, __LINE__);
    
    auto sharedPtr = ptr.lock();
    return sharedPtr.get() + pos;
}

template <typename T> MatrixConstIterator<T> &MatrixConstIterator<T>::operator=(const MatrixConstIterator &it) noexcept
{
    pos = it.pos;
    rows = it.rows;
    columns = it.columns;
    ptr = it.ptr;

    return *this;
}

template <typename T> MatrixConstIterator<T> MatrixConstIterator<T>::operator+(difference_type n) const noexcept
{
    MatrixConstIterator it(*this);

    it += n;

    return it;
}

template <typename T> MatrixConstIterator<T> &MatrixConstIterator<T>::operator+=(difference_type n) noexcept
{
    pos += n;

    return *this;
}

template <typename T> MatrixConstIterator<T> MatrixConstIterator<T>::operator-(difference_type n) const noexcept
{
    MatrixConstIterator<T> it(*this);

    it -= n;

    return it;
}

template <typename T> bool MatrixConstIterator<T>::operator==(const MatrixConstIterator &it) const noexcept
{
    return pos == it.pos && ptr.lock().get() == it.ptr.lock().get();
}

template <typename T> MatrixConstIterator<T> &MatrixConstIterator<T>::operator++() noexcept
{
    pos++;

    return *this;
}

template <typename T> MatrixConstIterator<T> MatrixConstIterator<T>::operator++(int) noexcept
{
    MatrixConstIterator copy(*this);
    ++*this;
    return copy;
}

template <typename T> MatrixConstIterator<T> &MatrixConstIterator<T>::operator--() noexcept
{
    pos--;

    return *this;
}

template <typename T> MatrixConstIterator<T> MatrixConstIterator<T>::operator--(int) noexcept
{
    MatrixConstIterator copy(*this);
    --*this;
    return copy;
}

template <typename T>
typename MatrixConstIterator<T>::difference_type MatrixConstIterator<T>::operator-(const MatrixConstIterator &it) const noexcept
{
    return pos - it.pos;
}

template <typename T>
MatrixConstIterator<T>::operator bool() const noexcept
{
    return pos >= 0 && pos < rows * columns;
}

template <typename T> MatrixConstIterator<T> &MatrixConstIterator<T>::operator-=(difference_type n) noexcept
{
    pos -= n;

    return *this;
}

template <typename T> typename MatrixConstIterator<T>::const_reference MatrixConstIterator<T>::operator*() const
{
    validateInBounds(pos, __FILE__, __FUNCTION__, __LINE__);
    validateExpired(__FILE__, __FUNCTION__, __LINE__);
    
    return *get();
}

template <typename T> typename MatrixConstIterator<T>::const_pointer MatrixConstIterator<T>::operator->() const
{
    validateInBounds(pos, __FILE__, __FUNCTION__, __LINE__);
    validateExpired(__FILE__, __FUNCTION__, __LINE__);
    
    return get();
}

template <typename T>
void MatrixConstIterator<T>::validateInBounds(size_t index, const char* filename, const char* funcName, int line) const
{
    if (index < 0 || index > columns * rows)
        throw OutOfBoundsException(filename, funcName, line, time(nullptr));
}

template <typename T>
void MatrixConstIterator<T>::validateExpired(const char* filename, const char* funcName, int line) const
{
    if (ptr.expired())
        throw ExpiredException(filename, funcName, line, time(nullptr));
}

template <typename T> const T &MatrixConstIterator<T>::operator[](difference_type index) const
{
    validateInBounds(pos + index, __FILE__, __FUNCTION__, __LINE__);
    validateExpired(__FILE__, __FUNCTION__, __LINE__);
    
    auto sharedPtr = ptr.lock();
    return *(sharedPtr.get() + index);
}

#endif // MATRIXCONSTITERATOR_HPP
