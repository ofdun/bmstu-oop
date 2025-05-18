#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "Matrix.h"
#include "MatrixExceptions.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>

template <Storable T> void Matrix<T>::swapRows(const sizeType index1, const sizeType index2)
{
    if (index1 >= rows || index2 >= rows || index1 < 0 || index2 < 0)
        throw InvalidRowIndexException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    auto row1Begin = begin() + static_cast<typename iterator::difference_type>(index1 * columns);
    auto row2Begin = begin() + static_cast<typename iterator::difference_type>(index2 * columns);

    std::ranges::swap_ranges(
        std::ranges::subrange(row1Begin, row1Begin + static_cast<typename iterator::difference_type>(columns)),
        std::ranges::subrange(row2Begin, row2Begin + static_cast<typename iterator::difference_type>(columns))
        );
}

template <Storable T> typename Matrix<T>::valueType Matrix<T>::determinant() const requires DeterminantComputable<T>
{
    if (!square())
        throw IncompatibleSizeException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    auto res = valueType{0};

    sizeType n = rows;
    Matrix tmpMatrix(*this);

    for (auto k = 0; k < n - 1; k++)
    {
        if (tmpMatrix[k][k] == valueType{0})
        {
            bool found = false;
            for (auto i = k + 1; i < n && !found; i++)
            {
                if (tmpMatrix[i][k] != valueType{0})
                {
                    tmpMatrix.swapRows(k, i);
                    found = true;
                }
            }
            if (!found)
                return valueType{0};
        }

        for (auto r = k + 1; r < n; r++)
        {
            for (auto c = k + 1; c < n; c++)
            {
                tmpMatrix[r][c] = tmpMatrix[k][k] * tmpMatrix[r][c] - tmpMatrix[r][k] * tmpMatrix[k][c];
                if (k > 0)
                    tmpMatrix[r][c] /= tmpMatrix[k - 1][k - 1];
            }
            tmpMatrix[r][k] = valueType{0};
        }
    }

    return tmpMatrix[n - 1][n - 1];
}

template <Storable T> T Matrix<T>::trace() const requires SelfAddable<T>
{
    if (!square())
        throw IncompatibleSizeException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    valueType sum = get(0, 0);

    std::ranges::for_each(std::views::iota(sizeType{1}, rows), [&](auto i) {
        sum += get(i, i);
    });

    return sum;
}

template <Storable T> Matrix<T> Matrix<T>::transpose() const
{
    auto newMatrix = Matrix(columns, rows);
    
    std::ranges::for_each(std::views::iota(sizeType{0}, columns), [&](int r) {
        std::ranges::for_each(std::views::iota(sizeType{0}, rows), [&](int c) {
            newMatrix[r][c] = get(c, r);
        });
    });

    return newMatrix;
}

template <Storable T> Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> lst)
{
    rows = lst.size();
    if (rows > 0)
        columns = lst.begin()->size();

    std::ranges::for_each(lst, [this](const auto &cur) {
        if (columns != cur.size())
            throw InvalidInitializerListException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));
    });

    allocNewMem(rows * columns);

    auto flatten = lst | std::ranges::views::join;
    std::ranges::copy(flatten, begin());
}

template <Storable T> Matrix<T> Matrix<T>::fill(valueType value) const
{
    Matrix res(rows, columns);

    std::ranges::fill(res, value);

    return res;
}

template <Storable T> typename Matrix<T>::iterator Matrix<T>::begin()
{
    return iterator(*this);
}

template <Storable T> typename Matrix<T>::iterator Matrix<T>::end()
{
    auto it = iterator(*this);
    it += rows * columns;
    return it;
}

template <Storable T>
typename Matrix<T>::reverseIterator Matrix<T>::rbegin()
{
    return reverseIterator(*this);
}

template <Storable T>
typename Matrix<T>::reverseIterator Matrix<T>::rend()
{
    auto it = reverseIterator(*this);
    it += rows * columns;
    return it;
}

template <Storable T>
typename Matrix<T>::constReverseIterator Matrix<T>::rbegin() const
{
    return constReverseIterator(*this);
}

template <Storable T>
typename Matrix<T>::constReverseIterator Matrix<T>::rend() const
{
    auto it = constReverseIterator(*this);
    it += rows * columns;
    return it;
}

template <Storable T> typename Matrix<T>::constIterator Matrix<T>::begin() const
{
    return constIterator(*this);
}

template <Storable T> typename Matrix<T>::constIterator Matrix<T>::end() const
{
    auto it = constIterator(*this);
    it += rows * columns;
    return it;
}

template <Storable T> typename Matrix<T>::constIterator Matrix<T>::cbegin() const
{
    return begin();
}

template <Storable T>
typename Matrix<T>::constReverseIterator Matrix<T>::rcbegin() const
{
    return rbegin();
}

template <Storable T> typename Matrix<T>::constIterator Matrix<T>::cend() const
{
    return end();
}

template <Storable T>
typename Matrix<T>::constReverseIterator Matrix<T>::rcend() const
{
    return rend();
}

template <Storable T> Matrix<T> Matrix<T>::submatrix(sizeType r1, sizeType c1, sizeType r2, sizeType c2) const
{
    if (c1 > c2)
        std::swap(c1, c2);

    if (r1 > r2)
        std::swap(r1, r2);

    Matrix res(r2 - r1 + 1, c2 - c1 + 1);

    std::ranges::for_each(std::views::iota(r1, r2 + 1), [&](sizeType r) {
        std::ranges::for_each(std::views::iota(c1, c2 + 1), [&](sizeType c) {
            res[r - r1][c - c1] = get(r, c);
        });
    });

    return res;
}

template <Storable T> bool Matrix<T>::zero() const requires HasZeroElement<T>
{
    return std::ranges::all_of(*this, [](const auto &e) {
        return e == valueType{0};
    });
}

template <Storable T> bool Matrix<T>::identity() const requires HasZeroElement<T> && HasIdentityElement<T>
{
    if (!square())
        return false;

    int cur = 0;
    return std::ranges::all_of(*this, [this, &cur](const auto &elem) {
        sizeType r = cur / columns;
        sizeType c = cur % columns;

        cur++;
        if (r == c)
            return elem == valueType{1};
        return elem == valueType{0};
    });
}

template <Storable T> bool Matrix<T>::symmetric() const
{
    if (!square())
        return false;

    return std::ranges::all_of(std::views::iota(sizeType{0}, rows), [this](sizeType r) {
        return std::ranges::all_of(std::views::iota(sizeType{r + 1}, rows), [this, r](sizeType c) {
            return get(r, c) == get(c, r);
        });
    });
}

template <Storable T> bool Matrix<T>::diagonal() const requires HasZeroElement<T>
{
    if (!square())
        return false;

    return std::ranges::all_of(std::views::iota(sizeType{0}, rows), [this](sizeType r) {
        return std::ranges::all_of(std::views::iota(sizeType{0}, columns), [this, r](sizeType c) {
            return r == c || get(r, c) == valueType{0};
        });
    });
}

template <Storable T> bool Matrix<T>::square() const noexcept
{
    return rows == columns;
}

template <Storable T>
template <EqualityComparable<T> U>
bool Matrix<T>::equals(const Matrix<U> &m) const
{
    return *this == m;
}

template <Storable T>
template <EqualityComparable<T> U>
bool Matrix<T>::equals(const Matrix<U> &m) const requires std::is_floating_point_v<U> || std::is_floating_point_v<T>
{
    return *this == m;
}

template <Storable T>
template <EqualityComparable<T> U>
bool Matrix<T>::operator==(const Matrix<U> &m) const
{
    const auto [otherRows, otherColumns] = m.size();
    if (rows != otherRows || columns != otherColumns)
        return false;

    return std::ranges::equal(*this, m);
}

template <Storable T>
template <EqualityComparable<T> U>
bool Matrix<T>::operator==(const Matrix<U> &m) const requires std::is_floating_point_v<U> || std::is_floating_point_v<T>
{
    const auto [otherRows, otherColumns] = m.size();
    if (rows != otherRows || columns != otherColumns)
        return false;

    return std::ranges::equal(*this, m, [](const auto &a, const auto &b) {
        constexpr double eps = 1e-8;

        return std::abs(a - b) < eps;
    });
}

template <Storable T> bool Matrix<T>::invertible() const requires DeterminantComputable<T>
{
    return square() && determinant() != valueType{0};
}

template <Storable T>
template <AddableAssignable<T> U>
Matrix<T> &Matrix<T>::operator+=(const Matrix<U> &m)
{
    const auto [otherRows, otherCols] = m.size();
    if (rows != otherRows || columns != otherCols)
        throw IncompatibleSizeException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    auto m_ = *this + m;

    *this = m_;

    return *this;
}

template <Storable T>
template <SubtractableAssignable<T> U>
Matrix<T> &Matrix<T>::operator-=(const Matrix<U> &m)
{
    const auto [otherRows, otherCols] = m.size();
    if (rows != otherRows || columns != otherCols)
        throw IncompatibleSizeException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    auto m_ = *this - m;

    *this = m_;

    return *this;
}

template <Storable T> typename Matrix<T>::reference Matrix<T>::operator()(const sizeType row, const sizeType column)
{
    return (*this)[row][column];
}

template <Storable T>
typename Matrix<T>::constReference Matrix<T>::operator()(const sizeType row, const sizeType column) const
{
    return get(row, column);
}

template <Storable T>
typename Matrix<T>::MatrixRow Matrix<T>::operator[](sizeType row)
{
    return MatrixRow(row, *this);
}

template <Storable T>
const typename Matrix<T>::MatrixRow Matrix<T>::operator[](sizeType row) const
{
    return MatrixRow(row, *this);
}

template <Storable T> decltype(auto) Matrix<T>::operator~() const requires HasZeroElement<T> && HasIdentityElement<T>
{
    if (!invertible())
        throw NotInvertibleException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    auto [L, U] = this->LU();

    sizeType n = rows;
    Matrix invA(n, n);
    Matrix Y(n, n);

    for (auto c = 0; c < n; c++)
        for (auto r = 0; r < n; r++)
        {
            valueType sum = r == c ? valueType{1} : valueType{0};
            for (int k = 0; k < r; k++)
                sum -= L[r][k] * Y[k][c];
            Y[r][c] = sum;
        }

    for (auto c = 0; c < n; c++)
        for (int r = n - 1; r >= 0; r--)
        {
            valueType sum = Y[r][c];
            for (int k = r + 1; k < n; ++k)
                sum -= U[r][k] * invA[k][c];
            invA[r][c] = sum / U[r][r];
        }

    return invA;
}

template <Storable T>
template <DivisibleAssignable<T> U>
Matrix<T> &Matrix<T>::operator/=(const Matrix<U> &m)
{
    const auto [otherRows, otherCols] = m.size();

    if (rows != otherRows || columns != otherCols)
        throw IncompatibleSizeException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    auto m_ = *this / m;

    *this = m_;

    return *this;
}

template <Storable T>
decltype(auto) Matrix<T>::negative() const requires Negotiable<T>
{
    return -*this;
}

template <Storable T>
template <Addable<T> U>
decltype(auto) Matrix<T>::addMatrix(const Matrix<U> &m) const
{
    return *this + m;
}

template <Storable T>
template <Subtractable<T> U>
decltype(auto) Matrix<T>::subtractMatrix(const Matrix<U> &m) const
{
    return *this - m;
}

template <Storable T>
template <MatrixMultiplyable<T> U>
decltype(auto) Matrix<T>::multiplyMatrix(const Matrix<U> &m) const requires HasZeroElement<decltype(
    std::declval<T>() + std::declval<U>())>
{
    return *this * m;
}

template <Storable T>
template <Divisible<T> U>
decltype(auto) Matrix<T>::divideMatrix(const Matrix<U> &m) const
{
    return *this / m;
}

template <Storable T> std::pair<Matrix<T>, Matrix<T>> Matrix<T>::LU() const requires LUComputable<T>
{
    if (!square())
        throw IncompatibleSizeException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    auto U = Matrix(*this);
    auto L = Matrix::initZero(rows, columns);

    sizeType n = rows;
    for (auto r = 0; r < n; r++)
        for (int c = r; c < n; c++)
            L[c][r] = U[c][r] / U[r][r];

    for (auto k = 1; k < n; k++)
    {
        for (int c = k - 1; c < n; c++)
            for (int r = c; r < n; r++)
                L[r][c] = U[r][c] / U[c][c];

        for (int r = k; r < n; r++)
            for (int c = k - 1; c < n; c++)
                U[r][c] = U[r][c] - L[r][k - 1] * U[k - 1][c];
    }

    return std::make_pair(L, U);
}

template <Storable T>
decltype(auto) Matrix<T>::invert() const requires HasZeroElement<T> && HasIdentityElement<T>
{
    return ~*this;
}

template <Storable T>
template <AddableAssignable<T> U>
Matrix<T> &Matrix<T>::addMatrixUpd(const Matrix<U> &m)
{
    return *this += m;
}

template <Storable T>
template <SubtractableAssignable<T> U>
Matrix<T> &Matrix<T>::subtractMatrixUpd(const Matrix<U> &m)
{
    return *this -= m;
}

template <Storable T>
template <MatrixMultiplyableAssignable<T> U>
Matrix<T> &Matrix<T>::multiplyMatrixUpd(const Matrix<U> &m)
{
    return *this *= m;
}

template <Storable T>
template <DivisibleAssignable<T> U>
Matrix<T> &Matrix<T>::divideMatrixUpd(const Matrix<U> &m)
{
    return *this /= m;
}

template <Storable T> std::ostream &operator<<(std::ostream &os, const Matrix<T> &m) requires Outputable<T>
{
    const auto [rows, columns] = m.size();

    typename Matrix<T>::sizeType cur = 0;
    std::ranges::for_each(m, [&os, &cur, columns](const auto &e) {
        os << e << ' ';
        cur++;

        if (cur % columns == 0)
            os << '\n';
    });

    return os;
}

template <Storable T>
template <Addable<T> U>
decltype(auto) Matrix<T>::operator+(const U &val) const
{
    Matrix<decltype(std::declval<T>() + std::declval<U>())> res(*this);

    std::ranges::transform(res, res.begin(), [&val](const auto &e) {
        return e + val;
    });

    return res;
}

template <Storable T>
template <Subtractable<T> U>
decltype(auto) Matrix<T>::operator-(const U &val) const
{
    Matrix<decltype(std::declval<T>() - std::declval<U>())> res(*this);

    std::ranges::transform(res, res.begin(), [&val](const auto &e) {
        return e - val;
    });

    return res;
}

template <Storable T>
template <Multiplyable<T> U>
decltype(auto) Matrix<T>::operator*(const U &val) const
{
    Matrix<decltype(std::declval<T>() * std::declval<U>())> res(*this);

    std::ranges::transform(res, res.begin(), [&val](const auto &e) {
        return e * val;
    });

    return res;
}

template <Storable T>
template <Divisible<T> U>
decltype(auto) Matrix<T>::operator/(const U &val) const
{
    Matrix<decltype(std::declval<T>() / std::declval<U>())> res(*this);

    std::ranges::transform(res, res.begin(), [&val](const auto &e) {
        return e / val;
    });

    return res;
}

template <Storable T>
template <AddableAssignable<T> U>
Matrix<T> &Matrix<T>::operator+=(const U &val)
{
    std::ranges::transform(*this, begin(), [&val](const auto &e) {
        return e + val;
    });

    return *this;
}

template <Storable T>
template <SubtractableAssignable<T> U>
Matrix<T> &Matrix<T>::operator-=(const U &val)
{
    std::ranges::transform(*this, begin(), [&val](const auto &e) {
        return e - val;
    });

    return *this;
}

template <Storable T>
template <MultiplyableAssignable<T> U>
Matrix<T> &Matrix<T>::operator*=(const U &val)
{
    std::ranges::transform(*this, begin(), [&val](const auto &e) {
        return e * val;
    });

    return *this;
}

template <Storable T>
template <DivisibleAssignable<T> U>
Matrix<T> &Matrix<T>::operator/=(const U &val)
{
    std::ranges::transform(*this, begin(), [&val](const auto &e) {
        return e / val;
    });

    return *this;
}

template <Storable T>
Matrix<T>::MatrixRow::MatrixRow(sizeType row, const Matrix &m): row(row), matrix(m)
{
}

template <Storable T>
typename Matrix<T>::reference Matrix<T>::MatrixRow::operator[](sizeType column)
{
    const auto [rows, columns] = matrix.size();

    if (row >= rows || row < 0)
        throw InvalidRowIndexException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    if (column >= columns || column < 0)
        throw InvalidColumnIndexException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    return matrix.data[row * columns + column];
}

template <Storable T>
typename Matrix<T>::constReference Matrix<T>::MatrixRow::operator[](sizeType column) const
{
    const auto [rows, columns] = matrix.size();

    if (row >= rows || row < 0)
        throw InvalidRowIndexException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    if (column >= columns || column < 0)
        throw InvalidColumnIndexException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    return matrix.data[row * columns + column];
}

template <Storable T>
template <MatrixMultiplyableAssignable<T> U>
Matrix<T> &Matrix<T>::operator*=(const Matrix<U> &m)
{
    const auto [otherRows, otherCols] = m.size();

    if (columns != otherCols || rows != otherRows)
        throw IncompatibleSizeException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    auto m_ = *this * m;

    *this = m_;

    return *this;
}

template <Storable T> Matrix<T> &Matrix<T>::operator=(const Matrix &m)
{
    rows = m.rows;
    columns = m.columns;

    allocNewMem(rows * columns);

    std::ranges::copy(m, begin());

    return *this;
}

template <Storable T>
Matrix<T> &Matrix<T>::operator=(std::initializer_list<std::initializer_list<valueType>> lst)
{
    rows = lst.size();
    if (rows > 0)
        columns = lst.begin()->size();

    std::ranges::for_each(lst, [this](const auto &cur) {
        if (columns != cur.size())
            throw InvalidInitializerListException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));
    });

    allocNewMem(rows * columns);

    auto flatten = lst | std::ranges::views::join;
    std::ranges::copy(flatten, begin());

    return *this;
}

template <Storable T> Matrix<T>::Matrix(const Matrix &m)
{
    rows = m.rows;
    columns = m.columns;

    allocNewMem(rows * columns);

    std::ranges::copy(m, begin());
}

template <Storable T> decltype(auto) Matrix<T>::operator-() const requires Negotiable<T>
{
    Matrix<decltype(-std::declval<T>())> newMatrix(*this);

    std::ranges::copy(*this, newMatrix.begin());

    std::ranges::transform(newMatrix, newMatrix.begin(), [](const auto &e) {
        return -e;
    });

    return newMatrix;
}

template <Storable T> Matrix<T> Matrix<T>::operator+() const
{
    Matrix newMatrix(*this);

    return newMatrix;
}

template <Storable T>
template <Addable<T> U>
decltype(auto) Matrix<T>::operator+(const Matrix<U> &m) const
{
    const auto [otherRows, otherCols] = m.size();
    if (rows != otherRows || columns != otherCols)
        throw IncompatibleSizeException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    Matrix<decltype(std::declval<T>() + std::declval<U>())> newMatrix(rows, columns);

    sizeType cur = sizeType{0};
    std::ranges::transform(newMatrix, newMatrix.begin(), [this, &cur, &m](const auto &) {
        sizeType r = cur / columns;
        sizeType c = cur % columns;
        cur++;
        return this->get(r, c) + m[r][c];
    });

    return newMatrix;
}

template <Storable T>
template <Subtractable<T> U>
decltype(auto) Matrix<T>::operator-(const Matrix<U> &m) const
{
    const auto [otherRows, otherCols] = m.size();
    if (rows != otherRows || columns != otherCols)
        throw IncompatibleSizeException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    Matrix<decltype(std::declval<T>() - std::declval<U>())> newMatrix(rows, columns);
    sizeType cur = sizeType{0};
    std::ranges::transform(newMatrix, newMatrix.begin(), [this, &cur, &m](const auto &) {
        sizeType r = cur / columns;
        sizeType c = cur % columns;
        cur++;
        return this->get(r, c) - m[r][c];
    });

    return newMatrix;
}

template <Storable T>
template <MatrixMultiplyable<T> U>
decltype(auto) Matrix<T>::operator*(const Matrix<U> &m) const requires HasZeroElement<decltype(
    std::declval<T>() + std::declval<U>())>
{
    const auto [otherRows, otherCols] = m.size();
    if (columns != otherRows)
        throw IncompatibleSizeException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    Matrix<decltype(std::declval<T>() * std::declval<U>() + std::declval<T>() * std::declval<U>())> newMatrix = initZero(rows, otherCols);

    for (auto r = 0; r < rows; r++)
        for (auto c = 0; c < otherCols; c++)
            for (auto k = 0; k < columns; k++)
                newMatrix[r][c] += get(r, k) * m[k][c];

    return newMatrix;
}

template <Storable T>
template <Divisible<T> U>
decltype(auto) Matrix<T>::operator/(const Matrix<U> &m) const
{
    const auto [otherRows, otherCols] = m.size();
    if (rows != otherRows || columns != otherCols)
        throw IncompatibleSizeException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    Matrix<decltype(std::declval<T>() / std::declval<U>())> res(*this);

    sizeType cur = sizeType{0};
    std::ranges::transform(res, res.begin(), [this, &cur, &m](const auto &) {
        sizeType r = cur / columns;
        sizeType c = cur % columns;
        cur++;
        return this->get(r, c) / m[r][c];
    });

    return res;
}

template <Storable T> typename Matrix<T>::valueType Matrix<T>::get(const sizeType row, const sizeType column) const
{
    auto it = constIterator(*this);

    it += row * columns + column;

    return *it;
}

template <Storable T>
template <Addable<T> U>
decltype(auto) Matrix<T>::addNumber(const U &val) const
{
    return *this + val;
}

template <Storable T>
template <Subtractable<T> U>
decltype(auto) Matrix<T>::subtractNumber(const U &val) const
{
    return *this - val;
}

template <Storable T>
template <Multiplyable<T> U>
decltype(auto) Matrix<T>::multiplyNumber(const U &val) const
{
    return *this * val;
}

template <Storable T>
template <Divisible<T> U>
decltype(auto) Matrix<T>::divideNumber(const U &val) const
{
    return *this / val;
}

template <Storable T>
template <AddableAssignable<T> U>
Matrix<T> &Matrix<T>::addNumberUpd(const U &val)
{
    return *this += val;
}

template <Storable T>
template <SubtractableAssignable<T> U>
Matrix<T> &Matrix<T>::subtractNumberUpd(const U &val)
{
    return *this -= val;
}

template <Storable T>
template <MultiplyableAssignable<T> U>
Matrix<T> &Matrix<T>::multiplyNumberUpd(const U &val)
{
    return *this *= val;
}

template <Storable T>
template <DivisibleAssignable<T> U>
Matrix<T> &Matrix<T>::divideNumberUpd(const U &val)
{
    return *this /= val;
}

template <Storable T>
template <Convertible<T> U>
void Matrix<T>::set(const sizeType row, const sizeType column, const U &value)
{
    auto it = iterator(*this);

    it += row * columns + column;

    *it = value;
}

template <Storable T> Matrix<T>::Matrix(Matrix &&m) noexcept
{
    rows = m.rows;
    columns = m.columns;
    data = m.data;

    m.data = nullptr;
}

template <Storable T> Matrix<T>::Matrix(sizeType rows, sizeType cols)
{
    if (rows <= 0 || cols <= 0)
        throw InvalidInitSizeException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    this->rows = rows;
    this->columns = cols;

    allocNewMem(rows * cols);
}

template <Storable T, Addable<T> U>
decltype(auto) operator+(const U &val, const Matrix<T> &m)
{
    return m + val;
}

template <Storable T, Multiplyable<T> U>
decltype(auto) operator*(const U &val, const Matrix<T> &m)
{
    return m * val;
}

template <Storable T>
std::pair<typename Matrix<T>::sizeType, typename Matrix<T>::sizeType> Matrix<T>::size() const noexcept
{
    return std::make_pair(rows, columns);
}

template <Storable T>
Matrix<T> Matrix<T>::initSquare(sizeType n)
{
    return Matrix(n, n);
}

template <Storable T>
Matrix<T> Matrix<T>::initZero(sizeType rows, sizeType columns) requires HasZeroElement<T>
{
    Matrix m(rows, columns);

    m.fill(valueType{0});

    return m;
}

template <Storable T>
Matrix<T> Matrix<T>::initIdentity(sizeType n) requires HasZeroElement<T> && HasIdentityElement<T>
{
    auto m = Matrix::initSquare(n);

    std::ranges::for_each(std::views::iota(sizeType{0}, n), [&m](sizeType i) {
        m[i][i] = valueType{1};
    });

    return m;
}

<<<<<<< Updated upstream
template <Storable T> void Matrix<T>::allocNewMem(const sizeType size)
=======
template <Storable T>
Matrix<T> Matrix<T>::initDiagonal(size_t n, const T &elem) requires IdentityMatrixCompatible<T>
{
    auto m = Matrix::initZero(n, n);

    std::ranges::for_each(std::views::iota(size_t{0}, n), [&m, &elem](size_t i) {
        m[i][i] = elem;
    });

    return m;
}

template <Storable T>
template <std::ranges::input_range range> Matrix<T>::Matrix(const range &rng, size_t rows, size_t columns)  requires std::convertible_to<std::ranges::range_value_t<range>, T>
{
    if (rows <= 0 || columns <= 0)
        throw InvalidInitSizeException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    this->rows = rows;
    this->columns = columns;
    allocNewMem(rows * columns);

    std::ranges::copy(rng, begin());
}

template <Storable T> void Matrix<T>::allocNewMem(const size_t size)
>>>>>>> Stashed changes
{
    try
    {
        auto tmp = std::make_shared<T[]>(size);
        data.reset();
        data = tmp;
    }
    catch (std::bad_alloc &_)
    {
        throw MemoryAllocationException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));
    }
}

template <Storable T>
Matrix<T>::~Matrix()
{
    data.reset();
}

template <Storable T>
template <Convertible<T> U>
Matrix<T>::Matrix(const Matrix<U> &m)
{
    const auto [otherRows, otherColumns] = m.size();

    rows = otherRows;
    columns = otherColumns;

    allocNewMem(rows * columns);

    std::ranges::copy(m, begin());
}

template <Storable T>
template <Convertible<T> U>
Matrix<T> &Matrix<T>::operator=(const Matrix<U> &m)
{
    const auto [otherRows, otherCols] = m.size();
    rows = otherRows;
    columns = otherCols;

    allocNewMem(rows * columns);

    std::ranges::copy(m, begin());

    return *this;
}

template <Storable T>
template <Convertible<T> U>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<U>> lst)
{
    rows = lst.size();
    if (rows > 0)
        columns = lst.begin()->size();

    std::ranges::for_each(lst, [this](const auto &cur) {
        if (columns != cur.size())
            throw InvalidInitializerListException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));
    });

    allocNewMem(rows * columns);

    auto flatten = lst | std::ranges::views::join;
    std::ranges::copy(flatten, begin());
}

template <Storable T>
template <Convertible<T> U>
Matrix<T> &Matrix<T>::operator=(std::initializer_list<std::initializer_list<U>> lst)
{
    rows = lst.size();
    if (rows > 0)
        columns = lst.begin()->size();

    std::ranges::for_each(lst, [this](const auto &cur) {
        if (columns != cur.size())
            throw InvalidInitializerListException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));
    });

    allocNewMem(rows * columns);

    auto flatten = lst | std::ranges::views::join;
    std::ranges::copy(flatten, begin());

    return *this;
}

#endif // MATRIX_HPP