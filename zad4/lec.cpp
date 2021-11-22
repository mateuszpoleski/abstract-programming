#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>

// template <typename T, typename = void>
// struct is_incrementable : std::false_type
// {
// };

// template <typename T>
// struct is_incrementable<T, std::void_t<decltype(++std::declval<T &>())>> : std::true_type
// {
// };

template <typename>
using try_to_compile = void; //void_t - zeby sie lepiej czytalo

template <template <typename> class Expr, typename T, typename CompileAttempt = void>
struct is_detected_impl : std::false_type
{
};

template <template <typename> class Expr, typename T>
struct is_detected_impl<Expr, T, try_to_compile<Expr<T>>> : std::true_type
{
};

template <template <typename> class Expr, typename T>
constexpr bool is_detected = is_detected_impl<Expr, T>::value;

template <typename T>
using incrment_expr = decltype(++std::declval<T &>());

template <typename T>
constexpr bool is_incrementable = is_detected<incrment_expr, T>;

//

template <typename T>
using decrement_expr = decltype(--std::declval<T &>());

template <typename T>
constexpr bool is_decrementable = is_detected<decrement_expr, T>;

//

template <typename T>
using evaluate_expr = decltype(&T::evaluate);

template <typename T>
constexpr bool is_class_with_eval = is_detected<evaluate_expr, T>;

class A
{
public:
    double evaluate(double a, double b)
    {
        return a * b;
    }
};

int main()
{
    std::cout << std::boolalpha;
    std::cout << is_incrementable<double> << '\n';
    std::cout << is_incrementable<std::string> << '\n';

    std::cout << is_decrementable<double> << '\n';
    std::cout << is_decrementable<std::string> << '\n';

    std::cout << is_class_with_eval<double> << '\n';
    std::cout << is_class_with_eval<std::string> << '\n';
    std::cout << is_class_with_eval<A> << '\n';
}