#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "Matrix.h"
#include "MatrixExceptions.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>

template <Storable T> void Matrix<T>::swapRows(const size_t index1, const size_t index2)
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

template <Storable T> void Matrix<T>::swapColumns(const size_t index1, const size_t index2)
{
    if (index1 >= rows || index2 >= rows || index1 < 0 || index2 < 0)
        throw InvalidRowIndexException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    std::ranges::for_each(std::views::iota(size_t{0}, rows), [this, index1, index2](const auto &r) {
        std::swap((*this)[r][index1], (*this)[r][index2]);
    });
}

template <Storable T> typename Matrix<T>::value_type Matrix<T>::determinant() const requires DeterminantComputable<T>
{
    if (!square())
        throw IncompatibleSizeException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    auto res = value_type{0};

    size_t n = rows;
    Matrix tmpMatrix(*this);

    for (auto k = 0; k < n - 1; k++)
    {
        if (tmpMatrix[k][k] == value_type{0})
        {
            bool found = false;
            for (auto i = k + 1; i < n && !found; i++)
            {
                if (tmpMatrix[i][k] != value_type{0})
                {
                    tmpMatrix.swapRows(k, i);
                    found = true;
                }
            }
            if (!found)
                return value_type{0};
        }

        for (auto r = k + 1; r < n; r++)
        {
            for (auto c = k + 1; c < n; c++)
            {
                tmpMatrix[r][c] = tmpMatrix[k][k] * tmpMatrix[r][c] - tmpMatrix[r][k] * tmpMatrix[k][c];
                if (k > 0)
                    tmpMatrix[r][c] /= tmpMatrix[k - 1][k - 1];
            }
            tmpMatrix[r][k] = value_type{0};
        }
    }

    return tmpMatrix[n - 1][n - 1];
}

template <Storable T> typename Matrix<T>::value_type Matrix<T>::determinant() const requires
    DeterminantComputable<T> && std::is_floating_point_v<T>
{
    if (!square())
        throw IncompatibleSizeException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    size_t n = rows;
    Matrix tmpMatrix(*this);

    for (auto k = 0; k < n - 1; k++)
    {
        if (std::abs(tmpMatrix[k][k]) < DBL_EPSILON)
        {
            bool found = false;
            for (auto i = k + 1; i < n && !found; i++)
            {
                if (std::abs(tmpMatrix[i][k]) < DBL_EPSILON)
                {
                    tmpMatrix.swapRows(k, i);
                    found = true;
                }
            }
            if (!found)
                return value_type{0};
        }

        for (auto r = k + 1; r < n; r++)
        {
            for (auto c = k + 1; c < n; c++)
            {
                tmpMatrix[r][c] = tmpMatrix[k][k] * tmpMatrix[r][c] - tmpMatrix[r][k] * tmpMatrix[k][c];
                if (k > 0)
                    tmpMatrix[r][c] /= tmpMatrix[k - 1][k - 1];
            }
            tmpMatrix[r][k] = value_type{0};
        }
    }

    return tmpMatrix[n - 1][n - 1];
}

template <Storable T> T Matrix<T>::trace() const requires SelfAddable<T>
{
    if (!square())
        throw IncompatibleSizeException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    value_type sum = get(0, 0);

    std::ranges::for_each(std::views::iota(size_t{1}, rows), [&](auto i) {
        sum += get(i, i);
    });

    return sum;
}

template <Storable T> Matrix<T> Matrix<T>::transpose() const
{
    auto newMatrix = Matrix(columns, rows);

    std::ranges::for_each(std::views::iota(size_t{0}, columns), [this, &newMatrix](size_t r) {
        std::ranges::for_each(std::views::iota(size_t{0}, rows), [this, &newMatrix, r](size_t c) {
            newMatrix[r][c] = get(c, r);
        });
    });

    return newMatrix;
}

template <Storable T>
Matrix<T> &Matrix<T>::transposed()
{
    if (!square())
        throw IncompatibleSizeException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    std::ranges::for_each(std::views::iota(size_t{0}, rows), [this](const auto &r) {
        std::ranges::for_each(std::views::iota(r + 1, columns), [this, r](const auto &c) {
            std::swap((*this)[r][c], (*this)[c][r]);
        });
    });

    return *this;
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

template <Storable T> Matrix<T> Matrix<T>::fill(value_type value) const
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
typename Matrix<T>::reverse_iterator Matrix<T>::rbegin()
{
    return reverse_iterator(*this);
}

template <Storable T>
typename Matrix<T>::reverse_iterator Matrix<T>::rend()
{
    auto it = reverse_iterator(*this);
    it += rows * columns;
    return it;
}

template <Storable T>
typename Matrix<T>::const_reverse_iterator Matrix<T>::rbegin() const
{
    return const_reverse_iterator(*this);
}

template <Storable T>
typename Matrix<T>::const_reverse_iterator Matrix<T>::rend() const
{
    auto it = const_reverse_iterator(*this);
    it += rows * columns;
    return it;
}

template <Storable T> typename Matrix<T>::const_iterator Matrix<T>::begin() const
{
    return const_iterator(*this);
}

template <Storable T> typename Matrix<T>::const_iterator Matrix<T>::end() const
{
    auto it = const_iterator(*this);
    it += rows * columns;
    return it;
}

template <Storable T> typename Matrix<T>::const_iterator Matrix<T>::cbegin() const
{
    return begin();
}

template <Storable T>
typename Matrix<T>::const_reverse_iterator Matrix<T>::crbegin() const
{
    return rbegin();
}

template <Storable T> typename Matrix<T>::const_iterator Matrix<T>::cend() const
{
    return end();
}

template <Storable T>
typename Matrix<T>::const_reverse_iterator Matrix<T>::crend() const
{
    return rend();
}

template <Storable T> Matrix<T> Matrix<T>::submatrix(size_t r1, size_t c1, size_t r2, size_t c2) const
{
    if (c1 > c2)
        std::swap(c1, c2);

    if (r1 > r2)
        std::swap(r1, r2);

    Matrix res(r2 - r1 + 1, c2 - c1 + 1);

    std::ranges::for_each(std::views::iota(r1, r2 + 1), [&](size_t r) {
        std::ranges::for_each(std::views::iota(c1, c2 + 1), [&](size_t c) {
            res[r - r1][c - c1] = get(r, c);
        });
    });

    return res;
}

template <Storable T> bool Matrix<T>::zero() const requires HasZeroElement<T>
{
    return std::ranges::all_of(*this, [](const auto &e) {
        return e == value_type{0};
    });
}

template <Storable T> bool Matrix<T>::zero() const requires HasZeroElement<T> && std::is_floating_point_v<T>
{
    return std::ranges::all_of(*this, [](const auto &e) {
        return std::abs(e) < DBL_EPSILON;
    });
}

template <Storable T> bool Matrix<T>::identity() const requires IdentityMatrixCompatible<T>
{
    if (!square())
        return false;

    int cur = 0;
    return std::ranges::all_of(*this, [this, &cur](const auto &elem) {
        size_t r = cur / columns;
        size_t c = cur % columns;

        cur++;
        if (r == c)
            return elem == value_type{1};
        return elem == value_type{0};
    });
}

template <Storable T> bool Matrix<T>::identity() const requires
    IdentityMatrixCompatible<T> && std::is_floating_point_v<T>
{
    if (!square())
        return false;

    int cur = 0;
    return std::ranges::all_of(*this, [this, &cur](const auto &elem) {
        size_t r = cur / columns;
        size_t c = cur % columns;

        cur++;
        if (r == c)
            return std::abs(elem - value_type{1}) < DBL_EPSILON;
        return std::abs(elem) < DBL_EPSILON;
    });
}

template <Storable T> bool Matrix<T>::symmetric() const
{
    if (!square())
        return false;

    return std::ranges::all_of(std::views::iota(size_t{0}, rows), [this](size_t r) {
        return std::ranges::all_of(std::views::iota(size_t{r + 1}, rows), [this, r](size_t c) {
            return get(r, c) == get(c, r);
        });
    });
}

template <Storable T> bool Matrix<T>::diagonal() const requires HasZeroElement<T>
{
    if (!square())
        return false;

    return std::ranges::all_of(std::views::iota(size_t{0}, rows), [this](size_t r) {
        return std::ranges::all_of(std::views::iota(size_t{0}, columns), [this, r](size_t c) {
            return r == c || get(r, c) == value_type{0};
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
bool Matrix<T>::equals(const Matrix<U> &m) const requires FloatingPointAny<T, U>
{
    return *this == m;
}

template <Storable T>
template <EqualityComparable<T> U>
bool Matrix<T>::operator==(const Matrix<U> &m) const
{
    auto otherRows = m.getRows();
    auto otherColumns = m.getColumns();
    if (rows != otherRows || columns != otherColumns)
        return false;

    return std::ranges::equal(*this, m);
}

template <Storable T>
template <EqualityComparable<T> U>
bool Matrix<T>::operator==(const Matrix<U> &m) const requires FloatingPointAny<T, U>
{
    auto otherRows = m.getRows();
    auto otherColumns = m.getColumns();
    if (rows != otherRows || columns != otherColumns)
        return false;

    return std::ranges::equal(*this, m, [](const auto &a, const auto &b) {
        return std::abs(a - b) < DBL_EPSILON;
    });
}

template <Storable T> bool Matrix<T>::invertible() const requires DeterminantComputable<T>
{
    return square() && determinant() != value_type{0};
}

template <Storable T>
template <AddableAssignable<T> U>
Matrix<T> &Matrix<T>::operator+=(const Matrix<U> &m)
{
    auto otherRows = m.getRows();
    auto otherColumns = m.getColumns();

    if (rows != otherRows || columns != otherColumns)
        throw IncompatibleSizeException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    std::ranges::transform(*this, m, begin(), [](const auto &t, const auto &u) {
        return t + u;
    });

    return *this;
}

template <Storable T>
template <SubtractableAssignable<T> U>
Matrix<T> &Matrix<T>::operator-=(const Matrix<U> &m)
{
    auto otherRows = m.getRows();
    auto otherColumns = m.getColumns();
    if (rows != otherRows || columns != otherColumns)
        throw IncompatibleSizeException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    std::ranges::transform(*this, m, begin(), [](const auto &t, const auto &u) {
        return t - u;
    });

    return *this;
}

template <Storable T> typename Matrix<T>::reference Matrix<T>::operator()(const size_t row, const size_t column)
{
    return (*this)[row][column];
}

template <Storable T>
typename Matrix<T>::const_reference Matrix<T>::operator()(const size_t row, const size_t column) const
{
    return get(row, column);
}

template <Storable T>
typename Matrix<T>::MatrixRow Matrix<T>::operator[](size_t row)
{
    return MatrixRow(row, *this);
}

template <Storable T>
const typename Matrix<T>::MatrixRow Matrix<T>::operator[](size_t row) const
{
    return MatrixRow(row, *this);
}

template <Storable T> decltype(auto) Matrix<T>::operator~() const requires InvertComputable<T>
{
    if (!invertible())
        throw NotInvertibleException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    auto [L, U] = this->LU();

    size_t n = rows;
    Matrix invA(n, n);
    Matrix Y(n, n);

    for (auto c = 0; c < n; c++)
        for (auto r = 0; r < n; r++)
        {
            value_type sum = r == c ? value_type{1} : value_type{0};
            for (int k = 0; k < r; k++)
                sum -= L[r][k] * Y[k][c];
            Y[r][c] = sum;
        }

    for (auto c = 0; c < n; c++)
        for (int r = n - 1; r >= 0; r--)
        {
            value_type sum = Y[r][c];
            for (int k = r + 1; k < n; ++k)
                sum -= U[r][k] * invA[k][c];
            invA[r][c] = sum / U[r][r];
        }

    return invA;
}

template <Storable T> decltype(auto) Matrix<T>::operator~() const requires
    InvertComputable<T> && std::is_arithmetic_v<T>
{
    if (!invertible())
        throw NotInvertibleException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    auto [L, U] = this->LU();

    size_t n = rows;
    Matrix<double> invA(n, n);
    Matrix<double> Y(n, n);

    for (auto c = 0; c < n; c++)
        for (auto r = 0; r < n; r++)
        {
            double sum = r == c ? 1 : 0;
            for (int k = 0; k < r; k++)
                sum -= L[r][k] * Y[k][c];
            Y[r][c] = sum;
        }

    for (auto c = 0; c < n; c++)
        for (int r = n - 1; r >= 0; r--)
        {
            double sum = Y[r][c];
            for (int k = r + 1; k < n; ++k)
                sum -= U[r][k] * invA[k][c];
            invA[r][c] = sum / U[r][r];
        }

    return invA;
}

template <Storable T>
template <MatrixDivisibleAssignable<T> U>
Matrix<T> &Matrix<T>::operator/=(const Matrix<U> &m)
{
    if (!square() || !m.square() || rows != m.getRows() || columns != m.getColumns())
        throw ImpossibleToDivideException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));
    
    auto first = m.invert();
    *this = *this * first;
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
decltype(auto) Matrix<T>::multiplyMatrix(const Matrix<U> &m) const
{
    return *this * m;
}

template <Storable T>
template <Multiplyable<T> U>
decltype(auto) Matrix<T>::multiplyMatrixHadamard(const Matrix<U> &m) const
{
    if (!square())
        throw ImpossibleToMultiplyException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));
    
    Matrix<decltype(std::declval<T>() + std::declval<U>())> res = Matrix(rows, columns);

    std::ranges::transform(*this, m, res.begin(), [](const auto &t, const auto &u) {
        return t + u;
    });

    return res;
}

template <Storable T>
template <Divisible<T> U>
decltype(auto) Matrix<T>::divideMatrixHadamard(const Matrix<U> &m) const
{
    auto otherRows = m.getRows();
    auto otherColumns = m.getColumns();

    if (rows != otherRows || columns != otherColumns)
        throw IncompatibleSizeException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    Matrix<decltype(std::declval<T>() / std::declval<U>())> res(rows, columns);

    std::ranges::transform(*this, m, res.begin(), [](const auto &t, const auto &u) {
        return t / u;
    });

    return res;
}

template <Storable T> std::pair<Matrix<double>, Matrix<double>> Matrix<T>::LU() const requires LUComputable<T> && std::is_arithmetic_v<T>
{
    if (!square())
        throw IncompatibleSizeException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    auto U = Matrix<double>(*this);
    auto L = Matrix<double>::initZero(rows, columns);

    size_t n = rows;
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

template <Storable T> std::pair<Matrix<T>, Matrix<T>> Matrix<T>::LU() const requires LUComputable<T>
{
    if (!square())
        throw IncompatibleSizeException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    auto U = Matrix(*this);
    auto L = Matrix::initZero(rows, columns);

    size_t n = rows;
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
decltype(auto) Matrix<T>::invert() const requires InvertComputable<T>
{
    return ~*this;
}

template <Storable T>
decltype(auto) Matrix<T>::invert() const requires InvertComputable<T> && std::is_arithmetic_v<T>
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
template <MultiplyableAssignable<T> U>
Matrix<T> &Matrix<T>::multiplyMatrixHadamardUpd(const Matrix<U> &m)
{
    if (!square())
        throw ImpossibleToMultiplyException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    std::ranges::transform(*this, m, begin(), [](const auto &t, const auto &u) {
        return t + u;
    });

    return *this;
}

template <Storable T>
template <MatrixDivisibleAssignable<T> U>
Matrix<T> &Matrix<T>::divideMatrixUpd(const Matrix<U> &m)
{
    return *this /= m;
}

template <Storable T>
template <DivisibleAssignable<T> U>
Matrix<T> &Matrix<T>::divideMatrixHadamardUpd(const Matrix<U> &m)
{
    auto otherRows = m.getRows();
    auto otherColumns = m.getColumns();

    if (rows != otherRows || columns != otherColumns)
        throw IncompatibleSizeException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    std::ranges::transform(*this, m, begin(), [](const auto &t, const auto &u) {
        return t / u;
    });

    return *this;
}

template <Storable T> std::ostream &operator<<(std::ostream &os, const Matrix<T> &m) requires Outputable<T>
{
    auto columns = m.getColumns();

    size_t cur = 0;
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
    Matrix<decltype(std::declval<T>() + std::declval<U>())> res(rows, columns);

    std::ranges::transform(*this, res.begin(), [&val](const auto &e) {
        return e + val;
    });

    return res;
}

template <Storable T>
template <Subtractable<T> U>
decltype(auto) Matrix<T>::operator-(const U &val) const
{
    Matrix<decltype(std::declval<T>() - std::declval<U>())> res(rows, columns);

    std::ranges::transform(*this, res.begin(), [&val](const auto &e) {
        return e - val;
    });

    return res;
}

template <Storable T>
template <Multiplyable<T> U>
decltype(auto) Matrix<T>::operator*(const U &val) const
{
    Matrix<decltype(std::declval<T>() * std::declval<U>())> res(rows, columns);

    std::ranges::transform(*this, res.begin(), [&val](const auto &e) {
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
Matrix<T>::MatrixRow::MatrixRow(size_t row, const Matrix &m): row(row), matrix(m)
{
}

template <Storable T>
typename Matrix<T>::reference Matrix<T>::MatrixRow::operator[](size_t column)
{
    auto rows = matrix.getRows();
    auto columns = matrix.getColumns();

    if (row >= rows || row < size_t{0})
        throw InvalidRowIndexException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    if (column >= columns || column < 0)
        throw InvalidColumnIndexException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    return matrix.data[row * columns + column];
}

template <Storable T>
typename Matrix<T>::const_reference Matrix<T>::MatrixRow::operator[](size_t column) const
{
    auto rows = matrix.getRows();
    auto columns = matrix.getColumns();

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
    auto otherRows = m.getRows();
    auto otherColumns = m.getColumns();

    if (columns != otherColumns || columns != otherRows)
        throw IncompatibleSizeException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    auto m_ = *this * m;

    *this = m_;

    return *this;
}

template <Storable T>
template <MatrixMultiplyableAssignable<T> U>
Matrix<T> &Matrix<T>::multiplyMatrixUpd(const Matrix<U> &m)
{
    return *this *= m;
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
Matrix<T> &Matrix<T>::operator=(std::initializer_list<std::initializer_list<value_type>> lst)
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

template <Storable T> Matrix<T> &Matrix<T>::operator+() const
{
    return *this;
}

template <Storable T>
template <Addable<T> U>
decltype(auto) Matrix<T>::operator+(const Matrix<U> &m) const
{
    auto otherRows = m.getRows();
    auto otherColumns = m.getColumns();

    if (rows != otherRows || columns != otherColumns)
        throw IncompatibleSizeException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    Matrix<decltype(std::declval<T>() + std::declval<U>())> newMatrix(otherRows, otherColumns);

    std::ranges::transform(*this, m, newMatrix.begin(), [](const auto &t, const auto &u) {
        return t + u;
    });

    return newMatrix;
}

template <Storable T>
template <Subtractable<T> U>
decltype(auto) Matrix<T>::operator-(const Matrix<U> &m) const
{
    auto otherRows = m.getRows();
    auto otherColumns = m.getColumns();

    if (rows != otherRows || columns != otherColumns)
        throw IncompatibleSizeException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    Matrix<decltype(std::declval<T>() - std::declval<U>())> newMatrix(otherRows, otherColumns);

    std::ranges::transform(begin(), end(), m.begin(), m.end(), newMatrix.begin(), [](const auto &t, const auto &u) {
        return t - u;
    });

    return newMatrix;
}

template <Storable T>
template <MatrixMultiplyable<T> U>
decltype(auto) Matrix<T>::operator*(const Matrix<U> &m) const
{
    auto otherRows = m.getRows();
    auto otherColumns = m.getColumns();

    if (columns != otherRows)
        throw ImpossibleToMultiplyException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    using matrix_t = decltype(std::declval<T>() * std::declval<U>() + std::declval<T>() * std::declval<U>());
    Matrix<matrix_t> newMatrix = initZero(rows, otherColumns);

    for (auto r = 0; r < rows; r++)
        for (auto c = 0; c < otherColumns; c++)
            for (auto k = 0; k < columns; k++)
                newMatrix[r][c] += get(r, k) * m[k][c];

    return newMatrix;
}

template <Storable T>
template <MatrixDivisible<T> U>
decltype(auto) Matrix<T>::operator/(const Matrix<U> &m) const
{
    if (!square() || !m.square() || rows != m.getRows() || columns != m.getColumns())
        throw ImpossibleToDivideException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));
    
    auto first = m.invert();
    auto res = *this * first;
    return res;
}

template <Storable T>
template <MatrixDivisible<T> U>
decltype(auto) Matrix<T>::divideMatrix(const Matrix<U> &m) const
{
    return *this / m;
}

template <Storable T> typename Matrix<T>::reference Matrix<T>::get(const size_t row, const size_t column)
{
    auto it = const_iterator(*this);

    it += row * columns + column;

    return *it;
}

template <Storable T> typename Matrix<T>::const_reference Matrix<T>::get(const size_t row, const size_t column) const
{
    auto it = const_iterator(*this);

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
void Matrix<T>::set(const size_t row, const size_t column, const U &value)
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

template <Storable T> Matrix<T>::Matrix(size_t rows, size_t cols)
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
typename Matrix<T>::size_type Matrix<T>::size() const noexcept
{
    return rows * columns;
}

template <Storable T>
size_t Matrix<T>::getRows() const noexcept
{
    return rows;
}

template <Storable T>
size_t Matrix<T>::getColumns() const noexcept
{
    return columns;
}

template <Storable T>
Matrix<T> Matrix<T>::initSquare(size_t n)
{
    return Matrix(n, n);
}

template <Storable T>
Matrix<T> Matrix<T>::initZero(size_t rows, size_t columns) requires HasZeroElement<T>
{
    Matrix m(rows, columns);

    m.fill(value_type{0});

    return m;
}

template <Storable T>
Matrix<T> Matrix<T>::initIdentity(size_t n) requires IdentityMatrixCompatible<T>
{
    auto m = Matrix::initSquare(n);

    std::ranges::for_each(std::views::iota(size_t{0}, n), [&m](size_t i) {
        m[i][i] = value_type{1};
    });

    return m;
}

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
template <std::ranges::input_range range>
Matrix<T>::Matrix(const range &rng, size_t rows, size_t columns) requires std::convertible_to<std::ranges::range_value_t<range>, T>
{
    if (rows <= 0 || columns <= 0)
        throw InvalidInitSizeException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));

    this->rows = rows;
    this->columns = columns;
    allocNewMem(rows * columns);

    std::ranges::copy(rng, begin());
}

template <Storable T> void Matrix<T>::allocNewMem(const size_t size)
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
    auto otherRows = m.getRows();
    auto otherColumns = m.getColumns();

    rows = otherRows;
    columns = otherColumns;

    allocNewMem(rows * columns);

    std::ranges::copy(m, begin());
}

template <Storable T>
template <Convertible<T> U>
Matrix<T>::Matrix(const U *matrix, size_t rows, size_t columns)
{
    if (matrix == nullptr)
        throw NullptrArrayException(__FILE__, __FUNCTION__, __LINE__, time(nullptr));
        
    allocNewMem(rows * columns);
    this->rows = rows;
    this->columns = columns;

    std::ranges::transform(*this, begin(), [&matrix](const auto &) {
        const auto &cur = *matrix;
        ++matrix;
        return cur;
    });
}

template <Storable T>
template <Convertible<T> U>
Matrix<T> &Matrix<T>::operator=(const Matrix<U> &m)
{
    auto otherRows = m.getRows();
    auto otherColumns = m.getColumns();

    rows = otherRows;
    columns = otherColumns;

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