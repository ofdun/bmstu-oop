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
public:
#pragma region aliases

    using valueType = T;
    using reference = T &;
    using constReference = const T &;
    using iterator = MatrixIterator<T>;
    using reverseIterator = MatrixReverseIterator<T>;
    using constReverseIterator = MatrixConstReverseIterator<T>;
    using constIterator = MatrixConstIterator<T>;

#pragma endregion

    friend class MatrixIterator<valueType>;
    friend class MatrixConstIterator<valueType>;
    friend class MatrixReverseIterator<valueType>;

#pragma region constructors/destructor
<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream
    
    Matrix(std::initializer_list<std::initializer_list<valueType>> lst);
    Matrix(sizeType rows, sizeType cols);
=======
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes

    Matrix(size_t rows, size_t cols);
    
    Matrix(std::initializer_list<std::initializer_list<value_type>> lst);
    template <Convertible<T> U>
    Matrix(std::initializer_list<std::initializer_list<U>> lst);
    
    Matrix(const Matrix &m);
    template <Convertible<T> U>
    Matrix(const Matrix<U> &m);

    template <std::ranges::input_range range>
    Matrix(const range &rng, size_t rows, size_t columns) requires std::convertible_to<std::ranges::range_value_t<range>, T>;
    template <Convertible<T> U>
    Matrix(const U *matrix, size_t rows, size_t columns);
    
>>>>>>> Stashed changes
    Matrix(Matrix &&m) noexcept;
    explicit Matrix(const Matrix &m);
    Matrix &operator=(const Matrix &m);
    Matrix &operator=(std::initializer_list<std::initializer_list<valueType>> lst);

    ~Matrix() override;

    template <Convertible<T> U>
    explicit Matrix(const Matrix<U> &m);
    template <Convertible<T> U>
    Matrix &operator=(const Matrix<U> &m);

    template <Convertible<T> U>
    Matrix(std::initializer_list<std::initializer_list<U>> lst);
    template <Convertible<T> U>
    Matrix &operator=(std::initializer_list<std::initializer_list<U>> lst);
    
#pragma endregion

    [[nodiscard]] std::pair<sizeType, sizeType> size() const noexcept override;

#pragma region statics definitions

    static Matrix initSquare(sizeType n);
    static Matrix initZero(sizeType rows, sizeType columns) requires HasZeroElement<T>;
    static Matrix initIdentity(sizeType n) requires HasZeroElement<T> && HasIdentityElement<T>;

#pragma endregion

#pragma region matrix operator overloading
    decltype(auto) operator-() const requires Negotiable<T>;
    Matrix operator+() const;

    template <Addable<T> U>
    decltype(auto) operator+(const Matrix<U> &m) const;

    template <Subtractable<T> U>
    decltype(auto) operator-(const Matrix<U> &m) const;

    template <MatrixMultiplyable<T> U>
    decltype(auto) operator*(const Matrix<U> &m) const requires HasZeroElement<decltype(std::declval<T>() + std::declval<U>())>;

    template <Divisible<T> U>
    decltype(auto) operator/(const Matrix<U> &m) const;
    
    decltype(auto) operator~() const requires HasZeroElement<T> && HasIdentityElement<T>; //todo LU concept

    template <AddableAssignable<T> U>
    Matrix &operator+=(const Matrix<U> &m);

    template <SubtractableAssignable<T> U>
    Matrix &operator-=(const Matrix<U> &m);

    template <MatrixMultiplyableAssignable<T> U>
    Matrix &operator*=(const Matrix<U> &m);

    template <DivisibleAssignable<T> U>
    Matrix &operator/=(const Matrix<U> &m);

    template <EqualityComparable<T> U>
    bool operator==(const Matrix<U> &m) const;

    template <EqualityComparable<T> U>
    bool operator==(const Matrix<U> &m) const requires std::is_floating_point_v<U> || std::is_floating_point_v<T>;

#pragma endregion

#pragma region redundant
    decltype(auto) negative() const requires Negotiable<T>;

    template <Addable<T> U>
    decltype(auto) addMatrix(const Matrix<U> &m) const;

    template <Subtractable<T> U>
    decltype(auto) subtractMatrix(const Matrix<U> &m) const;

    template <MatrixMultiplyable<T> U>
    decltype(auto) multiplyMatrix(const Matrix<U> &m) const requires HasZeroElement<decltype(std::declval<T>() + std::declval<U>())>;

    template <Divisible<T> U>
    decltype(auto) divideMatrix(const Matrix<U> &m) const;
    
    decltype(auto) invert() const requires HasZeroElement<T> && HasIdentityElement<T>; //todo

    template <AddableAssignable<T> U>
    Matrix &addMatrixUpd(const Matrix<U> &m);

    template <SubtractableAssignable<T> U>
    Matrix &subtractMatrixUpd(const Matrix<U> &m);

    template <MatrixMultiplyableAssignable<T> U>
    Matrix &multiplyMatrixUpd(const Matrix<U> &m);

    template <DivisibleAssignable<T> U>
    Matrix &divideMatrixUpd(const Matrix<U> &m);

    template <EqualityComparable<T> U>
    bool equals(const Matrix<U> &m) const;

    template <EqualityComparable<T> U>
    bool equals(const Matrix<U> &m) const requires std::is_floating_point_v<U> || std::is_floating_point_v<T>;

#pragma endregion

#pragma region number operator overloading
    template <Addable<T> U>
    decltype(auto) operator+(const U &val) const;

    template <Subtractable<T> U>
    decltype(auto) operator-(const U &val) const;

    template <Multiplyable<T> U>
    decltype(auto) operator*(const U &val) const;

    template <Divisible<T> U>
    decltype(auto) operator/(const U &val) const;

    template <AddableAssignable<T> U>
    Matrix &operator+=(const U &val);

    template <SubtractableAssignable<T> U>
    Matrix &operator-=(const U &val);

    template <MultiplyableAssignable<T> U>
    Matrix &operator*=(const U &val);

    template <DivisibleAssignable<T> U>
    Matrix &operator/=(const U &val);
#pragma endregion

#pragma region number operator redundant
    template <Addable<T> U>
    decltype(auto) addNumber(const U &val) const;

    template <Subtractable<T> U>
    decltype(auto) subtractNumber(const U &val) const;

    template <Multiplyable<T> U>
    decltype(auto) multiplyNumber(const U &val) const;

    template <Divisible<T> U>
    decltype(auto) divideNumber(const U &val) const;

    template <AddableAssignable<T> U>
    Matrix &addNumberUpd(const U &val);

    template <SubtractableAssignable<T> U>
    Matrix &subtractNumberUpd(const U &val);

    template <MultiplyableAssignable<T> U>
    Matrix &multiplyNumberUpd(const U &val);

    template <DivisibleAssignable<T> U>
    Matrix &divideNumberUpd(const U &val);
#pragma endregion

#pragma region proxyClass row

    class MatrixRow
    {
    public:
        MatrixRow(sizeType row, const Matrix &m);
        MatrixRow(const MatrixRow &) = delete;
        MatrixRow(const MatrixRow &&) = delete;

        reference operator[](sizeType column);
        constReference operator[](sizeType column) const;

    private:
        sizeType row;
        const Matrix &matrix;
    };

#pragma endregion

#pragma region indexation
    reference operator()(sizeType row, sizeType column);
    constReference operator()(sizeType row, sizeType column) const;

    MatrixRow operator[](sizeType row);
    const MatrixRow operator[](sizeType row) const;

    valueType get(sizeType row, sizeType column) const;

    template <Convertible<T> U>
    void set(sizeType row, sizeType column, const U &value);
#pragma endregion

#pragma region type of matrix
    [[nodiscard]] bool zero() const requires HasZeroElement<T>;
    [[nodiscard]] bool square() const noexcept;
    [[nodiscard]] bool identity() const requires HasZeroElement<T> && HasIdentityElement<T>;
    [[nodiscard]] bool diagonal() const requires HasZeroElement<T>;
    [[nodiscard]] bool symmetric() const;
    [[nodiscard]] bool invertible() const requires DeterminantComputable<T>;
#pragma endregion

#pragma region additional methods
    [[nodiscard]] valueType trace() const requires SelfAddable<T>;
    Matrix transpose() const;
    valueType determinant() const requires DeterminantComputable<T>;
    Matrix submatrix(sizeType r1, sizeType c1, sizeType r2, sizeType c2) const;
    void swapRows(sizeType index1, sizeType index2);
    Matrix fill(valueType value) const;

    std::pair<Matrix, Matrix> LU() const requires LUComputable<T>;
#pragma endregion

#pragma region iterators
    iterator begin();
    iterator end();
    reverseIterator rbegin();
    reverseIterator rend();

    constReverseIterator rbegin() const;
    constReverseIterator rend() const;
    constIterator begin() const;
    constIterator end() const;

    constIterator cbegin() const;
    constReverseIterator rcbegin() const;
    constIterator cend() const;
    constReverseIterator rcend() const;
#pragma endregion

protected:
    void allocNewMem(sizeType size);

private:
    std::shared_ptr<T[]> data;
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