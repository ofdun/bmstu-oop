#ifndef MATRIX_H
#define MATRIX_H

#include <initializer_list>
#include <memory>

#include "BaseMatrix.h"
#include "MatrixConstIterator.hpp"
#include "MatrixIterator.hpp"
#include "MatrixReverseIterator.hpp"
#include "MatrixConstReverseIterator.hpp"
#include "MatrixConcepts.h"

template <Storable T> class Matrix final : public BaseMatrix
{
private:
    class MatrixRow;
    
public:
#pragma region aliases

    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using iterator = MatrixIterator<T>;
    using reverse_iterator = MatrixReverseIterator<T>;
    using const_reverse_iterator = MatrixConstReverseIterator<T>;
    using const_iterator = MatrixConstIterator<T>;

#pragma endregion

    friend class MatrixIterator<value_type>;
    friend class MatrixConstIterator<value_type>;

#pragma region constructors/destructor
    
    Matrix(size_t rows, size_t cols);
    
    Matrix(std::initializer_list<std::initializer_list<value_type>> lst);
    template <Convertible<T> U>
    Matrix(std::initializer_list<std::initializer_list<U>> lst);
    
    explicit Matrix(const Matrix &m);
    template <Convertible<T> U>
    explicit Matrix(const Matrix<U> &m);

    template <std::ranges::input_range range>
    Matrix(const range &rng, size_t rows, size_t columns) requires std::convertible_to<std::ranges::range_value_t<range>, T>;
    template <Convertible<T> U>
    Matrix(const U *matrix, size_t rows, size_t columns);
    
    Matrix(Matrix &&m) noexcept;

    Matrix &operator=(const Matrix &m);
    template <Convertible<T> U>
    Matrix &operator=(const Matrix<U> &m);
    Matrix &operator=(std::initializer_list<std::initializer_list<value_type>> lst);
    template <Convertible<T> U>
    Matrix &operator=(std::initializer_list<std::initializer_list<U>> lst);

    ~Matrix() override;
    
#pragma endregion

    [[nodiscard]] size_type size() const noexcept override;
    [[nodiscard]] size_t getRows() const noexcept;
    [[nodiscard]] size_t getColumns() const noexcept;

#pragma region statics definitions

    static Matrix initSquare(size_t n);
    static Matrix initZero(size_t rows, size_t columns) requires HasZeroElement<T>;
    static Matrix initIdentity(size_t n) requires IdentityMatrixCompatible<T>;
    static Matrix initDiagonal(size_t n, const_reference elem) requires IdentityMatrixCompatible<T>;

#pragma endregion

#pragma region default operations
    decltype(auto) operator-() const requires Negotiable<T>;
    decltype(auto) negative() const requires Negotiable<T>;

    Matrix &operator+() const;

    template <Addable<T> U>
    decltype(auto) operator+(const Matrix<U> &m) const;
    template <Addable<T> U>
    decltype(auto) addMatrix(const Matrix<U> &m) const;
    template <Addable<T> U>
    decltype(auto) operator+(const U &val) const;
    template <Addable<T> U>
    decltype(auto) addNumber(const U &val) const;

    template <AddableAssignable<T> U>
    Matrix &operator+=(const Matrix<U> &m);
    template <AddableAssignable<T> U>
    Matrix &addMatrixUpd(const Matrix<U> &m);
    template <AddableAssignable<T> U>
    Matrix &operator+=(const U &val);
    template <AddableAssignable<T> U>
    Matrix &addNumberUpd(const U &val);

    template <Subtractable<T> U>
    decltype(auto) operator-(const Matrix<U> &m) const;
    template <Subtractable<T> U>
    decltype(auto) subtractMatrix(const Matrix<U> &m) const;
    template <Subtractable<T> U>
    decltype(auto) operator-(const U &val) const;
    template <Subtractable<T> U>
    decltype(auto) subtractNumber(const U &val) const;

    template <SubtractableAssignable<T> U>
    Matrix &operator-=(const Matrix<U> &m);
    template <SubtractableAssignable<T> U>
    Matrix &subtractMatrixUpd(const Matrix<U> &m);
    template <SubtractableAssignable<T> U>
    Matrix &operator-=(const U &val);
    template <SubtractableAssignable<T> U>
    Matrix &subtractNumberUpd(const U &val);

    template <MatrixMultiplyable<T> U>
    decltype(auto) operator*(const Matrix<U> &m) const;
    template <MatrixMultiplyable<T> U>
    decltype(auto) multiplyMatrix(const Matrix<U> &m) const;
    template <Multiplyable<T> U>
    decltype(auto) multiplyMatrixHadamard(const Matrix<U> &m) const;
    template <Multiplyable<T> U>
    decltype(auto) operator*(const U &val) const;
    template <Multiplyable<T> U>
    decltype(auto) multiplyNumber(const U &val) const;

    template <MatrixMultiplyableAssignable<T> U>
    Matrix &operator*=(const Matrix<U> &m);
    template <MatrixMultiplyableAssignable<T> U>
    Matrix &multiplyMatrixUpd(const Matrix<U> &m);
    template <MultiplyableAssignable<T> U>
    Matrix &multiplyMatrixHadamardUpd(const Matrix<U> &m);
    template <MultiplyableAssignable<T> U>
    Matrix &operator*=(const U &val);
    template <MultiplyableAssignable<T> U>
    Matrix &multiplyNumberUpd(const U &val);

    template <MatrixDivisible<T> U>
    decltype(auto) operator/(const Matrix<U> &m) const;
    template <MatrixDivisible<T> U>
    decltype(auto) divideMatrix(const Matrix<U> &m) const;
    template <Divisible<T> U>
    decltype(auto) divideMatrixHadamard(const Matrix<U> &m) const;
    template <Divisible<T> U>
    decltype(auto) operator/(const U &val) const;
    template <Divisible<T> U>
    decltype(auto) divideNumber(const U &val) const;

    template <MatrixDivisibleAssignable<T> U>
    Matrix &operator/=(const Matrix<U> &m);
    template <MatrixDivisibleAssignable<T> U>
    Matrix &divideMatrixUpd(const Matrix<U> &m);
    template <DivisibleAssignable<T> U>
    Matrix &divideMatrixHadamardUpd(const Matrix<U> &m);
    template <DivisibleAssignable<T> U>
    Matrix &operator/=(const U &val);
    template <DivisibleAssignable<T> U>
    Matrix &divideNumberUpd(const U &val);
    
    decltype(auto) operator~() const requires InvertComputable<T>;
    decltype(auto) operator~() const requires InvertComputable<T> && std::is_arithmetic_v<T>;
    decltype(auto) invert() const requires InvertComputable<T>;
    decltype(auto) invert() const requires InvertComputable<T> && std::is_arithmetic_v<T>;

    template <EqualityComparable<T> U>
    bool operator==(const Matrix<U> &m) const;
    template <EqualityComparable<T> U>
    bool equals(const Matrix<U> &m) const;
    template <EqualityComparable<T> U>
    bool operator==(const Matrix<U> &m) const requires FloatingPointAny<T, U>;
    template <EqualityComparable<T> U>
    bool equals(const Matrix<U> &m) const requires FloatingPointAny<T, U>;

#pragma endregion

#pragma region matrix operations
    [[nodiscard]] value_type trace() const requires SelfAddable<T>;
    Matrix transpose() const;
    Matrix &transposed();
    value_type determinant() const requires DeterminantComputable<T>;
    value_type determinant() const requires DeterminantComputable<T> && std::is_floating_point_v<T>;
    Matrix submatrix(size_t r1, size_t c1, size_t r2, size_t c2) const;
    void swapRows(size_t index1, size_t index2);
    void swapColumns(size_t index1, size_t index2);
    Matrix fill(value_type value) const;

    std::pair<Matrix, Matrix> LU() const requires LUComputable<T>;
    std::pair<Matrix<double>, Matrix<double>> LU() const requires LUComputable<T> && std::is_arithmetic_v<T>;
#pragma endregion

#pragma region indexation
    reference operator()(size_t row, size_t column);
    const_reference operator()(size_t row, size_t column) const;

    MatrixRow operator[](size_t row);
    const MatrixRow operator[](size_t row) const;

    reference get(size_t row, size_t column);
    const_reference get(size_t row, size_t column) const;
    template <Convertible<T> U>
    void set(size_t row, size_t column, const U &value);
#pragma endregion

#pragma region type of matrix
    [[nodiscard]] bool zero() const requires HasZeroElement<T>;
    [[nodiscard]] bool zero() const requires HasZeroElement<T> && std::is_floating_point_v<T>;
    [[nodiscard]] bool square() const noexcept;
    [[nodiscard]] bool identity() const requires IdentityMatrixCompatible<T>;
    [[nodiscard]] bool identity() const requires IdentityMatrixCompatible<T> && std::is_floating_point_v<T>;
    [[nodiscard]] bool diagonal() const requires HasZeroElement<T>;
    [[nodiscard]] bool symmetric() const;
    [[nodiscard]] bool invertible() const requires DeterminantComputable<T>;
#pragma endregion

#pragma region iterators
    iterator begin();
    iterator end();
    reverse_iterator rbegin();
    reverse_iterator rend();

    const_iterator begin() const;
    const_iterator end() const;
    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend() const;

    const_iterator cbegin() const;
    const_iterator cend() const;
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;
#pragma endregion

private:
    void allocNewMem(size_t size);
    std::shared_ptr<T[]> data;

#pragma region proxyClass row

    class MatrixRow
    {
    public:
        MatrixRow() = delete;
        MatrixRow(size_t row, const Matrix &m);
        MatrixRow(const MatrixRow &) = delete;
        MatrixRow(const MatrixRow &&) = delete;
        MatrixRow &operator=(const MatrixRow &) = delete;
        MatrixRow &operator=(const MatrixRow &&) = delete;
        ~MatrixRow() = default;

        reference operator[](size_t column);
        const_reference operator[](size_t column) const;

    private:
        size_t row;
        const Matrix &matrix;
    };

#pragma endregion
};

#pragma region additional overloadings
template <Storable T>
std::ostream &operator<<(std::ostream &os, const Matrix<T> &m) requires Outputable<T>;

#pragma region leftside number operation

template <Storable T, Addable<T> U>
decltype(auto) operator+(const U &val, const Matrix<T> &m);

template <Storable T, Multiplyable<T> U>
decltype(auto) operator*(const U &val, const Matrix<T> &m);

#pragma endregion

#pragma endregion

#endif // MATRIX_H