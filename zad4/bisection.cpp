#include <cmath>
#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

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

//
template <typename T>
using evaluate_expr = decltype(&T::evaluate);

template <typename T>
constexpr bool is_class_with_eval = is_detected<evaluate_expr, T>;

//

template <typename T>
T bisectionFunction(T function(T), T min, T max, T tol)
{
    T fmin = function(min), mid;
    while (mid = (min + max) / 2,
           std::abs(max - min) > tol)
    {
        T fmid = function(mid);
        if (fmid * fmin > 0)
            min = mid, fmin = fmid;
        else
            max = mid;
    }
    return mid;
}

template <typename T>
T *bisectionFunction(T function(T, T), T *min, T *max, T tol)
{
    T min_x = min[0], min_y = min[1];
    T max_x = max[0], max_y = max[1];
    T fmin = function(min_x, min_y);
    T mid_x, mid_y;
    while (mid_x = (min_x + max_x) / 2,
           mid_y = (min_y + max_y) / 2,
           sqrt((max_y - min_y) * (max_y - min_y) + (max_x - min_x) * (max_x - min_x)) > tol)
    {
        T fmid = function(mid_x, mid_y);
        if (fmid * fmin > 0)
            min_x = mid_x, min_y = mid_y, fmin = fmid;
        else
            max_x = mid_x, max_y = mid_y;
        //cout << mid_x << ' ' << mid_y << ' ' << sqrt((max_y - min_y) * (max_y - min_y) + (max_x - min_x) * (max_x - min_x)) << "    " << min_x << ' ' << min_y << ' ' << max_x << ' ' << max_y << endl;
    }
    T *mid = new T[2];
    mid[0] = mid_x, mid[1] = mid_y;
    cout << mid_x << ' ' << mid_y << endl;
    return mid;
}

template <typename T>
T bisectionObj(T function(T), T min, T max, T tol)
{
    T fmin = function(min), mid;
    while (mid = (min + max) / 2,
           std::abs(max - min) > tol)
    {
        T fmid = function(mid);
        if (fmid * fmin > 0)
            min = mid, fmin = fmid;
        else
            max = mid;
    }
    return mid;
}
template <typename T>
T bisectionClass(T function(T), T min, T max, T tol)
{
    T fmin = function(min), mid;
    while (mid = (min + max) / 2,
           std::abs(max - min) > tol)
    {
        T fmid = function(mid);
        if (fmid * fmin > 0)
            min = mid, fmin = fmid;
        else
            max = mid;
    }
    return mid;
}

//

template <typename Functor, typename ArgType, typename = evaluate_expr<Functor>>
void bisection(Functor functor, ArgType min, ArgType max, double tol)
{
    cout << "evalate" << endl;
    ArgType fmin = functor.evaluate(min), mid;
    while (mid = (min + max) / 2,
           std::abs(max - min) > tol)
    {
        ArgType fmid = functor.evaluate(mid);
        if (fmid * fmin > 0)
            min = mid, fmin = fmid;
        else
            max = mid;
    }
    cout << "Solution is at point x = " << mid << endl;
}

template <typename Functor, typename ArgType, typename = evaluate_expr<Functor>>
void bisection(Functor functor, ArgType *min, ArgType *max, double tol)
{
    cout << "evaluate2" << endl;
    ArgType min_x = min[0], min_y = min[1];
    ArgType max_x = max[0], max_y = max[1];
    ArgType fmin = functor.evaluate(min_x, min_y);
    ArgType mid_x, mid_y;
    while (mid_x = (min_x + max_x) / 2,
           mid_y = (min_y + max_y) / 2,
           sqrt((max_y - min_y) * (max_y - min_y) + (max_x - min_x) * (max_x - min_x)) > tol)
    {
        ArgType fmid = functor.evaluate(mid_x, mid_y);
        if (fmid * fmin > 0)
            min_x = mid_x, min_y = mid_y, fmin = fmid;
        else
            max_x = mid_x, max_y = mid_y;
        //cout << mid_x << ' ' << mid_y << ' ' << sqrt((max_y - min_y) * (max_y - min_y) + (max_x - min_x) * (max_x - min_x)) << "    " << min_x << ' ' << min_y << ' ' << max_x << ' ' << max_y << endl;
    }

    cout << "Solution is at x = " << mid_x << " y = " << mid_y << endl;
}

template <typename ArgType>
void bisection(ArgType function(ArgType), ArgType min, ArgType max, double tol)
{
    cout << "function" << endl;
    ArgType fmin = function(min), mid;
    while (mid = (min + max) / 2,
           std::abs(max - min) > tol)
    {
        ArgType fmid = function(mid);
        if (fmid * fmin > 0)
            min = mid, fmin = fmid;
        else
            max = mid;
    }
    cout << "Solution is at point x = " << mid << endl;
}

template <typename ArgType>
void bisection(ArgType function(ArgType, ArgType), ArgType *min, ArgType *max, double tol)
{
    cout << "function2" << endl;
    ArgType min_x = min[0], min_y = min[1];
    ArgType max_x = max[0], max_y = max[1];
    ArgType fmin = function(min_x, min_y);
    ArgType mid_x, mid_y;
    while (mid_x = (min_x + max_x) / 2,
           mid_y = (min_y + max_y) / 2,
           sqrt((max_y - min_y) * (max_y - min_y) + (max_x - min_x) * (max_x - min_x)) > tol)
    {
        ArgType fmid = function(mid_x, mid_y);
        if (fmid * fmin > 0)
            min_x = mid_x, min_y = mid_y, fmin = fmid;
        else
            max_x = mid_x, max_y = mid_y;
        //cout << mid_x << ' ' << mid_y << ' ' << sqrt((max_y - min_y) * (max_y - min_y) + (max_x - min_x) * (max_x - min_x)) << "    " << min_x << ' ' << min_y << ' ' << max_x << ' ' << max_y << endl;
    }

    cout << "Solution is at x = " << mid_x << " y = " << mid_y << endl;
}

template <typename Functor, typename ArgType, typename... Args>
void bisection(Functor constant, ArgType min, ArgType max, double tol, Args... args)
{
    cout << "nothing" << endl;
    if (min > 0 or max < 0)
        cout << "There is no solution" << endl;
    else
        cout << "Solution is at point x = 0" << endl;
}

template <typename Functor, typename ArgType, typename... Args>
void bisection(Functor constant, ArgType *A, ArgType *B, double tol, Args... args)
{
    cout << "nothing" << endl;
    ArgType A_x = A[0], A_y = A[1];
    ArgType B_x = B[0], B_y = B[1];

    // ax + ay == 0 <==> y == -x
    //Współrzędne prostej przechodzącej przez A, B ( y(x) = ax + b )
    ArgType a = (A_y - B_y) / (A_x - B_x);
    ArgType b = A_y - (a * A_x);

    ArgType possible_solution = -b / (a + 1); // Rozwiązując y(x) = -x

    if (possible_solution > min(A_x, B_x) && possible_solution < max(A_x, B_x)) // Sprawdzamy czy rozwiązanie jest w zadanym przedziale
        cout << "Solution is at x = " << possible_solution << " y = " << -possible_solution << endl;
    else
        cout << "There is no solution" << endl;
}

// template <typename Functor, typename ArgType>
// ArgType bisection(Functor functor, ArgType min, ArgType max, double tol)
// {
//     if (is_class_with_eval<Functor>)
//     {
//         cout << "eval" << endl;
//         return bisectionClass(functor, min, max, tol);
//     }
//     else if (std::is_function<Functor>::value)
//     {
//         cout << "function" << endl;
//         return bisectionFunction(functor, min, max, tol);
//     }
//     else
//     {
//         cout << "obj" << endl;
//         return bisectionObj(functor, min, max, tol);
//     }
// }

template <typename K>
K f(K T)
{
    K p_atm = 50;
    K e_s = std::pow(10, 7.5 * T / (T + 237.3));
    e_s *= .611;
    return p_atm - e_s;
}

double g1(double x)
{
    return x * x - 1;
}

double g2(double x, double y)
{
    return x * x + y * y - 4;
}

struct A1
{
    double evaluate(double x)
    {
        return x * x - 1;
    }
};

struct A2
{
    double evaluate(double x, double y)
    {
        return x * x + y * y - 4;
    }
};

int main()
{
    cout << std::is_function<decltype(g2)>::value << endl;
    cout << is_class_with_eval<decltype(g2)> << endl;
    bisection<>(g1, 0., 2., .001);
    double start[2] = {0., 0.}, stop[2] = {5., 0.};
    bisection(g2, start, stop, .001);
    bisection(5, -2., 3., 0.1);
    double start2[2] = {0., -5.}, stop2[2] = {5., 0.};
    bisection(5, start2, stop2, 0.1);
    A1 a1;
    A2 a2;
    bisection(a1, 0., 2., 0.001);
    bisection(a2, start, stop, 0.001);
}