#include <gtest/gtest.h>

#include "Matrix.hpp"

TEST(InitMatrix, initializerList)
{
    Matrix m = {{1, 2, 3}, {4, 5, 6}};

    const int v[] = {1, 2, 3, 4, 5, 6};

    for (auto r = 0; r < 2; r++)
        for (auto c = 0; c < 3; c++)
            GTEST_ASSERT_EQ(m[r][c], v[r * 3 + c]);
    
    std::cout << m;
}

TEST(InitMatrix, rowsCols)
{
    Matrix<int> m(3, 4);

    auto r_ = m.getRows();
    auto c_ = m.getColumns();
    
    GTEST_ASSERT_EQ(r_, 3);
    GTEST_ASSERT_EQ(c_, 4);

    for (auto r = 0; r < 3; r++)
        for (auto c = 0; c < 4; c++)
            GTEST_ASSERT_EQ(int{0}, m[r][c]);
    
    std::cout << m;
}

TEST(InitMatrix, staticSquare)
{
    auto m = Matrix<char>::initSquare(2);

    auto r_ = m.getRows();
    auto c_ = m.getColumns();
    
    GTEST_ASSERT_EQ(r_, 2);
    GTEST_ASSERT_EQ(c_, 2);

    for (auto r = 0; r < 2; r++)
        for (auto c = 0; c < 2; c++)
            GTEST_ASSERT_EQ(char{0}, m[r][c]);
    
    std::cout << m;
}

TEST(InitMatrix, staticZero)
{
    auto rows = 4, columns = 5;
    using type_ = double;
    
    auto m = Matrix<type_>::initZero(rows, columns);

    auto r_ = m.getRows();
    auto c_ = m.getColumns();
    
    GTEST_ASSERT_EQ(r_, rows);
    GTEST_ASSERT_EQ(c_, columns);

    for (auto r = 0; r < rows; r++)
        for (auto c = 0; c < columns; c++)
            GTEST_ASSERT_EQ(type_{0}, m[r][c]);
    
    std::cout << m;
}

TEST(InitMatrix, staticIdentity)
{
    auto n = 3;
    using type_ = double;
    
    auto m = Matrix<type_>::initIdentity(n);

    auto r_ = m.getRows();
    auto c_ = m.getColumns();
    
    GTEST_ASSERT_EQ(r_, n);
    GTEST_ASSERT_EQ(c_, n);

    for (auto r = 0; r < n; r++)
        for (auto c = 0; c < n; c++)
            if (r != c)
                GTEST_ASSERT_EQ(type_{0}, m[r][c]);
            else
                GTEST_ASSERT_EQ(type_{1}, m[r][c]);
    
    std::cout << m;
}

TEST(InitMatrix, staticDiagonal)
{
    auto n = 3;
    auto elem = 5.3;
    using type_ = double;
    
    auto m = Matrix<type_>::initDiagonal(n, elem);

    auto r_ = m.getRows();
    auto c_ = m.getColumns();
    
    GTEST_ASSERT_EQ(r_, n);
    GTEST_ASSERT_EQ(c_, n);

    for (auto r = 0; r < n; r++)
        for (auto c = 0; c < n; c++)
            if (r != c)
                GTEST_ASSERT_EQ(type_{0}, m[r][c]);
            else
                GTEST_ASSERT_EQ(type_{elem}, m[r][c]);
    
    std::cout << m;
}

TEST(Arithmetic, unaryMinus)
{
    Matrix m = {{1, 2, 3}, {4, 5, 6}};

    auto m2 = -m;

    int a[] = {-1, -2, -3, -4, -5, -6};

    for (auto r = 0; r < 2; r++)
        for (auto c = 0; c < 3; c++)
            GTEST_ASSERT_EQ(a[r * 3 + c], m2[r][c]);
    
    std::cout << m2;
}

TEST(Redunant, negativeMatrix)
{
    Matrix m = {{1, 2, 3}, {4, 5, 6}};

    auto m2 = -m;
    auto m3 = m.negative();

    for (auto r = 0; r < 2; r++)
        for (auto c = 0; c < 3; c++)
            GTEST_ASSERT_EQ(m3[r][c], m2[r][c]);
    
    std::cout << m2;
}

TEST(Arithmetic, addNumber)
{
    Matrix m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    auto num = 5;

    auto m2 = m + num;
    int a[] = {6, 7, 8, 9, 10, 11, 12, 13, 14};

    for (auto r = 0; r < 3; r++)
        for (auto c = 0; c < 3; c++)
            GTEST_ASSERT_EQ(a[r * 3 + c], m2[r][c]);
    
    std::cout << m2;
}

TEST(Arithmetic, addNumberUpd)
{
    Matrix m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    auto num = 5;

    m += num;
    int a[] = {6, 7, 8, 9, 10, 11, 12, 13, 14};

    for (auto r = 0; r < 3; r++)
        for (auto c = 0; c < 3; c++)
            GTEST_ASSERT_EQ(a[r * 3 + c], m[r][c]);
    
    std::cout << m;
}

TEST(Redundant, addNumber)
{
    Matrix m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    auto num = 5;

    auto m2 = m + num;
    auto m3 = m.addNumber(num);

    for (auto r = 0; r < 3; r++)
        for (auto c = 0; c < 3; c++)
            GTEST_ASSERT_EQ(m3[r][c], m2[r][c]);
    
    std::cout << m3;
}

TEST(Redundant, addNumberUpd)
{
    Matrix m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix<int> m2(m);
    
    m2 = m;
    auto num = 5;

    m2 += num;
    m.addNumberUpd(num);

    for (auto r = 0; r < 3; r++)
        for (auto c = 0; c < 3; c++)
            GTEST_ASSERT_EQ(m2[r][c], m[r][c]);
    
    std::cout << m;
}

TEST(Arithmetic, addMatrix)
{
    Matrix m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix m1 = {{1, 9, 3}, {7, 5, 6}, {7, 2, 9}};

    auto m2 = m + m1;
    int a[] = {2, 11, 6, 11, 10, 12, 14, 10, 18};

    for (auto r = 0; r < 3; r++)
        for (auto c = 0; c < 3; c++)
            GTEST_ASSERT_EQ(a[r * 3 + c], m2[r][c]);
    
    std::cout << m2;
}

TEST(Arithmetic, addMatrixUpd)
{
    Matrix m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix m1 = {{1, 9, 3}, {7, 5, 6}, {7, 2, 9}};

    m1 += m;
    int a[] = {2, 11, 6, 11, 10, 12, 14, 10, 18};

    for (auto r = 0; r < 3; r++)
        for (auto c = 0; c < 3; c++)
            GTEST_ASSERT_EQ(a[r * 3 + c], m1[r][c]);
    
    std::cout << m1;
}

TEST(Redunant, addMatrixUpd)
{
    Matrix m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix m1 = {{1, 9, 3}, {7, 5, 6}, {7, 2, 9}};

    Matrix m2(m);
    m2 += m1;
    
    m.addMatrixUpd(m1);

    for (auto r = 0; r < 2; r++)
        for (auto c = 0; c < 3; c++)
            GTEST_ASSERT_EQ(m[r][c], m2[r][c]);
    
    std::cout << m2;
}

TEST(Redunant, addMatrix)
{
    Matrix m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix m1 = {{1, 9, 3}, {7, 5, 6}, {7, 2, 9}};

    auto m2 = m + m1;
    auto m3 = m.addMatrix(m1);

    for (auto r = 0; r < 2; r++)
        for (auto c = 0; c < 3; c++)
            GTEST_ASSERT_EQ(m3[r][c], m2[r][c]);
    
    std::cout << m2;
}

TEST(Arithmetic, subtractNumber)
{
    Matrix m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    auto number = 3;;

    auto m2 = m - number;
    int a[] = {-2, -1, 0, 1, 2, 3, 4, 5, 6};

    for (auto r = 0; r < 3; r++)
        for (auto c = 0; c < 3; c++)
            GTEST_ASSERT_EQ(a[r * 3 + c], m2[r][c]);
    
    std::cout << m2;
}

TEST(Arithmetic, subtractNumberUpd)
{
    Matrix m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    auto number = 3;

    m -= number;
    int a[] = {-2, -1, 0, 1, 2, 3, 4, 5, 6};

    std::cout << m;
    
    for (auto r = 0; r < 3; r++)
        for (auto c = 0; c < 3; c++)
            GTEST_ASSERT_EQ(a[r * 3 + c], m[r][c]);
}

TEST(Redundant, subtractNumber)
{
    Matrix m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    auto number = 3;

    auto m2 = m - number;
    auto m3 = m.subtractNumber(number);

    for (auto r = 0; r < 3; r++)
        for (auto c = 0; c < 3; c++)
            GTEST_ASSERT_EQ(m3[r][c], m2[r][c]);
    
    std::cout << m2;
}

TEST(Redundant, subtractNumberUpd)
{
    Matrix m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    auto number = 3;

    Matrix m2(m);
    m2 -= number;
    m.subtractNumberUpd(number);

    for (auto r = 0; r < 3; r++)
        for (auto c = 0; c < 3; c++)
            GTEST_ASSERT_EQ(m[r][c], m[r][c]);
    
    std::cout << m;
}

TEST(Arithmetic, subtractMatrix)
{
    Matrix m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix m1 = {{1, 9, 3}, {7, 5, 6}, {7, 2, 9}};

    auto m2 = m - m1;
    int a[] = {0, -7, 0, -3, 0, 0, 0, 6, 0};

    for (auto r = 0; r < 3; r++)
        for (auto c = 0; c < 3; c++)
            GTEST_ASSERT_EQ(a[r * 3 + c], m2[r][c]);
    
    std::cout << m2;
}

TEST(Arithmetic, subtractMatrixUpd)
{
    Matrix m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix m1 = {{1, 9, 3}, {7, 5, 6}, {7, 2, 9}};

    m -= m1;
    int a[] = {0, -7, 0, -3, 0, 0, 0, 6, 0};

    for (auto r = 0; r < 3; r++)
        for (auto c = 0; c < 3; c++)
            GTEST_ASSERT_EQ(a[r * 3 + c], m[r][c]);
    
    std::cout << m;
}

TEST(Redundant, subtractMatrixUpd)
{
    Matrix m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix m1 = {{1, 9, 3}, {7, 5, 6}, {7, 2, 9}};

    Matrix m2(m);
    m2 -= m1;
    
    m.subtractMatrixUpd(m1);

    for (auto r = 0; r < 2; r++)
        for (auto c = 0; c < 3; c++)
            GTEST_ASSERT_EQ(m[r][c], m2[r][c]);
    
    std::cout << m2;
}

TEST(Redundant, subtractMatrix)
{
    Matrix m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix m1 = {{1, 9, 3}, {7, 5, 6}, {7, 2, 9}};

    auto m2 = m - m1;
    auto m3 = m.subtractMatrix(m1);

    for (auto r = 0; r < 2; r++)
        for (auto c = 0; c < 3; c++)
            GTEST_ASSERT_EQ(m3[r][c], m2[r][c]);
    
    std::cout << m2;
}

TEST(Arithmetic, multiplyNumber)
{
    const Matrix<double> m = {{5, 3, 7, 0}, {7, 1, 9, 2}, {3, 4, 7, 6}};
    auto number = 4;

    auto m1 = m * number;
    double a[] = {20, 12, 28, 0, 28, 4, 36, 8, 12, 16, 28, 24};

    auto r_ = m1.getRows();
    auto c_ = m1.getColumns();
    
    std::cout << m1;
    
    for (auto r = 0; r < r_; r++)
        for (auto c = 0; c < c_; c++)
            ASSERT_FLOAT_EQ(a[r * c_ + c], m1[r][c]);
}

TEST(Arithmetic, multiplyNumberUpd)
{
    Matrix<double> m = {{5, 3, 7, 0}, {7, 1, 9, 2}, {3, 4, 7, 6}};
    auto number = 4;

    m *= number;
    double a[] = {20, 12, 28, 0, 28, 4, 36, 8, 12, 16, 28, 24};

    auto r_ = m.getRows();
    auto c_ = m.getColumns();
    
    std::cout << m;
    
    for (auto r = 0; r < r_; r++)
        for (auto c = 0; c < c_; c++)
            ASSERT_FLOAT_EQ(a[r * c_ + c], m[r][c]);
}

TEST(Redundant, multiplyNumber)
{
    const Matrix<double> m = {{5, 3, 7, 0}, {7, 1, 9, 2}, {3, 4, 7, 6}};
    auto number = 4;

    auto m1 = m * number;
    auto m2 = m.multiplyNumber(number);

    auto r_ = m1.getRows();
    auto c_ = m1.getColumns();
    
    std::cout << m1;
    
    for (auto r = 0; r < r_; r++)
        for (auto c = 0; c < c_; c++)
            ASSERT_FLOAT_EQ(m2[r][c], m1[r][c]);
}

TEST(Redundant, multiplyNumberUpd)
{
    Matrix<double> m = {{5, 3, 7, 0}, {7, 1, 9, 2}, {3, 4, 7, 6}};
    auto number = 4;

    Matrix m1(m);
    m1 *= number;
    m.multiplyNumberUpd(number);

    auto r_ = m1.getRows();
    auto c_ = m1.getColumns();
    
    std::cout << m1;
    
    for (auto r = 0; r < r_; r++)
        for (auto c = 0; c < c_; c++)
            ASSERT_FLOAT_EQ(m[r][c], m1[r][c]);
}

TEST(Arithmetic, multiplyMatrix)
{
    const Matrix<double> m = {{5, 3, 7, 0}, {7, 1, 9, 2}, {3, 4, 7, 6}};
    const Matrix<double> m1 = {{20.3, 1.6}, {18.6, 1.3}, {12.1, 1.0}, {23.0, 1.8}};

    auto m2 = m * m1;
    double a[] = {242, 18.9, 315.6, 25.1, 358, 27.8};

    auto r_ = m2.getRows();
    auto c_ = m2.getColumns();
    
    std::cout << m2;
    
    for (auto r = 0; r < r_; r++)
        for (auto c = 0; c < c_; c++)
            ASSERT_FLOAT_EQ(a[r * c_ + c], m2[r][c]);
}

TEST(Arithmetic, multiplyMatrixUpd)
{
    Matrix<double> m = {{5, 3}, {3, 4}};
    const Matrix<double> m1 = {{20.3, 1.6}, {18.6, 1.3}};

    m *= m1;
    double a[] = {157.3, 11.9, 135.3, 10};

    auto r_ = m.getRows();
    auto c_ = m.getColumns();
    
    std::cout << m;
    
    for (auto r = 0; r < r_; r++)
        for (auto c = 0; c < c_; c++)
            ASSERT_FLOAT_EQ(a[r * c_ + c], m[r][c]);
}

TEST(Redundant, multiplyMatrixUpd)
{
    Matrix<double> m = {{5, 3}, {3, 4}};
    const Matrix<double> m1 = {{20.3, 1.6}, {18.6, 1.3}};

    Matrix m2(m);
    m2 *= m1;
    
    m.multiplyMatrixUpd(m1);

    auto r_ = m2.getRows();
    auto c_ = m2.getColumns();
    
    std::cout << m2;
    
    for (auto r = 0; r < r_; r++)
        for (auto c = 0; c < c_; c++)
            ASSERT_FLOAT_EQ(m[r][c], m2[r][c]);
}

TEST(Redundant, multiplyMatrix)
{
    const Matrix<double> m = {{5, 3, 7, 0}, {7, 1, 9, 2}, {3, 4, 7, 6}};
    const Matrix<double> m1 = {{20.3, 1.6}, {18.6, 1.3}, {12.1, 1.0}, {23.0, 1.8}};

    auto m2 = m * m1;
    auto m3 = m.multiplyMatrix(m1);

    auto r_ = m2.getRows();
    auto c_ = m2.getColumns();
    
    std::cout << m2;
    
    for (auto r = 0; r < r_; r++)
        for (auto c = 0; c < c_; c++)
            ASSERT_FLOAT_EQ(m3[r][c], m2[r][c]);
}

TEST(Arithmetic, divideNumber)
{
    Matrix<double> m = {{5, 3, 7, 0}, {7, 1, 9, 2}, {3, 4, 7, 6}};
    auto number = 3;

    auto m2 = m / number;
    double a[] = {5/3.0, 3/3.0, 7/3.0, 0, 7/3.0, 1/3.0, 9/3.0, 2/3.0, 1, 4/3.0, 7.0/3.0, 2};

    auto r_ = m2.getRows();
    auto c_ = m2.getColumns();
    
    std::cout << m2;
    
    for (auto r = 0; r < r_; r++)
        for (auto c = 0; c < c_; c++)
            ASSERT_FLOAT_EQ(a[r * c_ + c], m2[r][c]);
}

TEST(Arithmetic, divideNumberUpd)
{
    Matrix<double> m = {{5, 3, 7, 0}, {7, 1, 9, 2}, {3, 4, 7, 6}};
    double number = 3;

    m /= number;
    double a[] = {5/3.0, 3/3.0, 7/3.0, 0, 7/3.0, 1/3.0, 9/3.0, 2/3.0, 1, 4/3.0, 7.0/3.0, 2};

    auto r_ = m.getRows();
    auto c_ = m.getColumns();
    
    std::cout << m;
    
    for (auto r = 0; r < r_; r++)
        for (auto c = 0; c < c_; c++)
            ASSERT_FLOAT_EQ(a[r * c_ + c], m[r][c]);
}

TEST(Redundant, divideNumber)
{
    Matrix<double> m = {{5, 3, 7, 0}, {7, 1, 9, 2}, {3, 4, 7, 6}};
    auto number = 3;

    auto m2 = m / number;
    auto m3 = m.divideNumber(number);

    auto r_ = m2.getRows();
    auto c_ = m2.getColumns();
    
    std::cout << m2;
    
    for (auto r = 0; r < r_; r++)
        for (auto c = 0; c < c_; c++)
            ASSERT_FLOAT_EQ(m3[r][c], m2[r][c]);
}

TEST(Redundant, divideNumberUpd)
{
    Matrix<double> m = {{5, 3, 7, 0}, {7, 1, 9, 2}, {3, 4, 7, 6}};
    double number = 3;

    Matrix m2(m);
    m2 /= number;
    m.divideNumberUpd(number);

    auto r_ = m.getRows();
    auto c_ = m.getColumns();
    
    std::cout << m;
    
    for (auto r = 0; r < r_; r++)
        for (auto c = 0; c < c_; c++)
            ASSERT_FLOAT_EQ(m2[r][c], m[r][c]);
}

TEST(Arithmetic, divideMatrix)
{
    const Matrix<double> m = {{5, 3}, {7, 1}};
    const Matrix<double> m1 = {{5.2, 1.2}, {4.3, 2.2}};

    auto m2 = m / m1;
    double a[] = {-95.0/314, 240.0/157, 555.0/314, -80.0/157};

    auto r_ = m2.getRows();
    auto c_ = m2.getColumns();
    
    std::cout << m2;
    
    for (auto r = 0; r < r_; r++)
        for (auto c = 0; c < c_; c++)
            ASSERT_FLOAT_EQ(a[r * c_ + c], m2[r][c]);
}

TEST(Arithmetic, divideMatrixUpd)
{
    Matrix<double> m = {{5, 3, 7, 0}, {7, 1, 9, 2}, {3, 4, 7, 6}, {1, 7, 4, 2}};
    const Matrix<double> m1 = {{5.2, 1.2, 8.7, 1.1}, {4.3, 2.2, 7.8, 9.8}, {9, 1.8, 20, 3}, {1, 9, 9, 0}};
    
    Matrix<double> a = m / m1;
    m /= m1;

    auto r_ = m.getRows();
    auto c_ = m.getColumns();
    
    std::cout << m;
    
    for (auto r = 0; r < r_; r++)
        for (auto c = 0; c < c_; c++)
            ASSERT_FLOAT_EQ(a[r][c], m[r][c]);
    
}

TEST(Redundant, divideMatrixUpd)
{
    Matrix<double> m = {{5, 3, 7, 0}, {7, 1, 9, 2}, {3, 4, 7, 6}, {1, 7, 4, 2}};
    const Matrix<double> m1 = {{5.2, 1.2, 8.7, 1.1}, {4.3, 2.2, 7.8, 9.8}, {9, 1.8, 20, 3}, {1, 9, 9, 0}};
    
    Matrix<double> a = m / m1;
    m.divideMatrixUpd(m1);

    auto r_ = m.getRows();
    auto c_ = m.getColumns();
    
    std::cout << m;
    
    for (auto r = 0; r < r_; r++)
        for (auto c = 0; c < c_; c++)
            ASSERT_FLOAT_EQ(a[r][c], m[r][c]);
    
}

TEST(Redundant, divideMatrixHadamard)
{
    const Matrix<double> m = {{5, 3, 7, 0}, {7, 1, 9, 2}, {3, 4, 7, 6}};
    const Matrix<double> m1 = {{5.2, 1.2, 8.7, 1.1}, {4.3, 2.2, 7.8, 9.8}, {9, 1.8, 20, 3}};

    double m3[] = {5/5.2, 3/1.2, 7/8.7, 0, 7/4.3, 1/2.2, 9/7.8, 2/9.8, 3.0/9, 4/1.8, 7.0/20, 6.0/3};
    auto m2 = m.divideMatrixHadamard(m1);

    auto r_ = m2.getRows();
    auto c_ = m2.getColumns();
    
    std::cout << m2;
    
    for (auto r = 0; r < r_; r++)
        for (auto c = 0; c < c_; c++)
            ASSERT_FLOAT_EQ(m3[r * c_ + c], m2[r][c]);
    
}

TEST(Arithmetic, invertMatrix)
{
    const Matrix<double> m = {{5, 3, 7, 0}, {7, 1, 9, 2}, {3, 4, 7, 6}, {5, 9, 0, 2}};

    auto m2 = ~m;
    double a[] = {-151.0/605, 182.0/605, -83.0/605, 67.0/605, 122.0/605, -119.0/605, 31.0/605, 26.0/605, 142.0/605, -79.0/605, 46.0/605, -59.0/605, -343.0/1210, 161.0/1210, 68.0/605, 18.0/605};

    auto r_ = m2.getRows();
    auto c_ = m2.getColumns();
    
    std::cout << m2;
    
    for (auto r = 0; r < r_; r++)
        for (auto c = 0; c < c_; c++)
            ASSERT_FLOAT_EQ(a[r * c_ + c], m2[r][c]);
    
}

TEST(TypeOfMatrix, zeroMatrix)
{
    const auto m = Matrix<int>::initZero(5, 5);
    
    std::cout << m;
    
    ASSERT_TRUE(m.zero());
}

TEST(TypeOfMatrix, squareMatrix)
{
    const auto m = Matrix<int>::initSquare(5);
    
    std::cout << m;
    
    ASSERT_TRUE(m.square());
}

TEST(TypeOfMatrix, identityMatrix)
{
    const auto m = Matrix<int>::initIdentity(4);
    
    std::cout << m;
    
    ASSERT_TRUE(m.identity());
}

TEST(TypeOfMatrix, diagonalMatrix)
{
    const auto m = Matrix<int>::initIdentity(4);
    
    std::cout << m;
    
    ASSERT_TRUE(m.diagonal());
}

TEST(TypeOfMatrix, symmetricMatrix)
{
    const auto m = Matrix{{1, 2, 3}, {2, 3, 4}, {3, 4, 5}};
    
    std::cout << m;
    
    ASSERT_TRUE(m.symmetric());
}

TEST(TypeOfMatrix, invertibleMatrix)
{
    const auto m = Matrix{{1, 2, 3}, {2, 3, 4}, {3, 4, 9}};
    
    std::cout << m;
    
    ASSERT_TRUE(m.invertible());
}

TEST(additionalOperation, trace)
{
    const auto m = Matrix{{1, 2}, {3, 4}};

    auto res = m.trace();
    
    std::cout << m;
    
    ASSERT_EQ(res, 5);
}

TEST(additionalOperation, transpose)
{
    const auto m = Matrix{{1, 2, 3}, {4, 5, 6}};

    auto res = m.transpose();

    const auto expected = Matrix{{1, 4}, {2, 5}, {3, 6}};
    
    std::cout << res;

    auto r_ = res.getRows();
    auto c_ = res.getColumns();

    for (auto r = 0; r < r_; r++)
        for (auto c = 0; c < c_; c++)
            GTEST_ASSERT_EQ(res[r][c], expected[r][c]);
}

TEST(additionalOperation, determinant)
{
    const auto m = Matrix<double>{{1, 0, 0}, {0, 2, 0}, {0, 0, 3}};

    auto res = m.determinant();

    const double expected = 6;

    std::cout << res << std::endl;

    ASSERT_EQ(res, expected);
}

TEST(additionalOperation, submatrix)
{
    const auto m = Matrix{{1, 0, 0}, {0, 2, 0}, {0, 0, 3}};

    auto res = m.submatrix(1, 2, 1, 1);

    const auto expected = Matrix{{2, 0}};

    std::cout << res << std::endl;

    auto r_ = res.getRows();
    auto c_ = res.getColumns();

    for (auto r = 0; r < r_; r++)
        for (auto c = 0; c < c_; c++)
            ASSERT_EQ(res[r][c], expected[r][c]);
}

TEST(additionalOperation, swapRows)
{
    auto m = Matrix{{1, 0, 0}, {0, 2, 0}, {0, 0, 3}};

    m.swapRows(0, 1);

    const auto expected = Matrix{{0, 2, 0}, {1, 0, 0}, {0, 0, 3}};

    std::cout << m << std::endl;

    auto r_ = m.getRows();
    auto c_ = m.getColumns();

    for (auto r = 0; r < r_; r++)
        for (auto c = 0; c < c_; c++)
            ASSERT_EQ(m[r][c], expected[r][c]);
}

TEST(additionalOperation, swapColumns)
{
    auto m = Matrix{{1, 0, 0}, {0, 2, 0}, {0, 0, 3}};

    m.swapColumns(0, 2);

    const auto expected = Matrix{{0, 0, 1}, {0, 2, 0}, {3, 0, 0}};

    std::cout << m << std::endl;

    auto r_ = m.getRows();
    auto c_ = m.getColumns();

    for (auto r = 0; r < r_; r++)
        for (auto c = 0; c < c_; c++)
            ASSERT_EQ(m[r][c], expected[r][c]);
}

TEST(additionalOperation, fill)
{
    auto m = Matrix<int>(3, 3);

    m = m.fill(2);

    std::cout << m << std::endl;

    auto r_ = m.getRows();
    auto c_ = m.getColumns();

    for (auto r = 0; r < r_; r++)
        for (auto c = 0; c < c_; c++)
            ASSERT_EQ(m[r][c], 2);
}

TEST(additionalOperation, LU)
{
    auto m = Matrix<int>{{4, 5, 2}, {2, 3, 8}, {0, 10, 12}};

    const auto [L, U] = m.LU();

    std::cout << "L:\n" <<  L << "\nU:\n" << U << std::endl;

    auto Lexpected = Matrix<double>{{1, 0, 0}, {0.5, 1, 0}, {0, 20, 1}};
    auto Uexpected = Matrix<double>{{4, 5, 2}, {0, 0.5, 7}, {0, 0, -128}};

    auto r_ = Lexpected.getRows();
    auto c_ = Lexpected.getColumns();

    for (auto r = 0; r < r_; r++)
        for (auto c = 0; c < c_; c++)
            ASSERT_EQ(L[r][c], Lexpected[r][c]);

    for (auto r = 0; r < r_; r++)
        for (auto c = 0; c < c_; c++)
            ASSERT_EQ(U[r][c], Uexpected[r][c]);
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}