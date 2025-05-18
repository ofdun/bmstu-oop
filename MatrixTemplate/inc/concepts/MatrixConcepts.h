#ifndef MATRIXCONCEPTS_H
#define MATRIXCONCEPTS_H

#include <concepts>

template <typename T>
concept Storable = std::semiregular<T>;

template <typename T, typename U>
concept Addable = requires(const T &t, const U &u)
{
    { t + u } -> std::same_as<decltype(t + u)>;
};

template <typename T, typename U>
concept AddableAssignable = Addable<T, U> && requires(const T &t, const U &u)
{
    std::is_assignable_v<T, decltype(t + u)>;
};

template <typename T, typename U>
concept Subtractable = requires(const T &t, const U &u)
{
    { t - u } -> std::same_as<decltype(t - u)>;
};

template <typename T, typename U>
concept SubtractableAssignable = Subtractable<T, U> && requires(const T &t, const U &u)
{
    std::is_assignable_v<T, decltype(t - u)>;
};

template <typename T, typename U>
concept Multiplyable = requires(const T &t, const U &u)
{
    { t * u } -> std::same_as<decltype(t * u)>;
};

template <typename T, typename U>
concept MultiplyableAssignable = Multiplyable<T, U> && requires(const T &t, const U &u)
{
    std::is_assignable_v<T, decltype(t * u)>;
};

template <typename T, typename U>
concept Divisible = requires(const T &t, const U &u)
{
    { t / u } -> std::same_as<decltype(t / u)>;
};

template <typename T, typename U>
concept DivisibleAssignable = Addable<T, U> && requires(const T &t, const U &u)
{
    std::is_assignable_v<T, decltype(t / u)>;
};

template <typename T>
concept Negotiable = requires(const T &t)
{
    { -t } -> std::same_as<decltype(-t)>;
};

template <typename T>
concept HasZeroElement = requires
{
    { T{0} } -> std::convertible_to<T>;
};

template <typename T>
concept HasIdentityElement = requires
{
    { T{1} } -> std::convertible_to<T>;
};

template <typename T, typename U>
concept MatrixMultiplyable = Multiplyable<T, U>
                             && HasZeroElement<decltype(std::declval<T>() + std::declval<U>())>
                             && Addable<decltype(std::declval<T>() * std::declval<U>()), decltype(
                                            std::declval<T>() * std::declval<U>())>;

template <typename T, typename U>
concept MatrixMultiplyableAssignable = MatrixMultiplyable<T, U> && requires(const T &t, const U &u)
{
    std::is_assignable_v<T, decltype(t * u + t * u)>;
};

template <typename T, typename U>
concept EqualityComparable = std::equality_comparable_with<T, U>;

template <typename T, typename U>
concept Convertible = std::convertible_to<U, T>;

template <typename T>
concept SelfAddable = requires (const T &t)
{
  { t + t } -> std::same_as<decltype(t + t)>;  
};

template <typename T>
concept DeterminantComputable = HasZeroElement<T> && requires (const T &a, const T &b)
{
    { a + b } -> std::convertible_to<T>;
    { a / b } -> std::convertible_to<T>;
    { a - b } -> std::convertible_to<T>;
    { a * b } -> std::convertible_to<T>;
};

template <typename T>
concept LUComputable = HasZeroElement<T> && requires (const T &a, const T &b)
{
    { a / b } -> std::convertible_to<T>;
    { a - b } -> std::convertible_to<T>;
    { a * b } -> std::convertible_to<T>;
};

template <typename T>
concept Outputable = requires (std::ostream &stream, const T &t)
{
    { stream << t } -> std::same_as<std::ostream &>;
};

#endif //MATRIXCONCEPTS_H