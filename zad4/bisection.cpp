//Nie zdążyłem dopisać wyjątków. Chyba też źle zrozumiałem koncepcje, bo wydaje mi się, że dodanie ich do takiej implementacji byłoby trudne.
#include <cmath>
#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

template <typename T>
using evaluate_expr = decltype(&T::evaluate);

//

template<typename Functor, typename ArgType>
ArgType functor_val(Functor functor, ArgType arg)
{
    return functor.evaluate(arg);
}

template <typename ArgType>
ArgType functor_val(ArgType function(ArgType), ArgType arg)
{
    return function(arg); 
}

template<typename Functor, typename ArgType>
ArgType functor_val(Functor functor, ArgType arg1, ArgType arg2)
{
    return functor.evaluate(arg1, arg2);
}

template <typename ArgType>
ArgType functor_val(ArgType function(ArgType, ArgType), ArgType arg1, ArgType arg2)
{
    return function(arg1, arg2); 
}

//

template <typename Functor, typename ArgType>
void bisection_impl(Functor functor, ArgType min, ArgType max, double tol)
{
    ArgType fmin = functor_val(functor, min);
    ArgType mid;
    while (mid = (min + max) / 2,
           std::abs(max - min) > tol)
    {
        ArgType fmid = functor_val(functor, min);
        if (fmid * fmin > 0)
            min = mid, fmin = fmid;
        else
            max = mid;
    }
    cout << "Solution is at point x = " << mid << endl;
}

template <typename Functor, typename ArgType>
void bisection_impl(Functor functor, ArgType *min, ArgType *max, double tol)
{
    ArgType min_x = min[0], min_y = min[1];
    ArgType max_x = max[0], max_y = max[1];
    ArgType fmin = functor_val(functor, min_x, min_y);
    ArgType mid_x, mid_y;
    while (mid_x = (min_x + max_x) / 2,
           mid_y = (min_y + max_y) / 2,
           sqrt((max_y - min_y) * (max_y - min_y) + (max_x - min_x) * (max_x - min_x)) > tol)
    {
        ArgType fmid = functor_val(functor, mid_x, mid_y);
        if (fmid * fmin > 0)
            min_x = mid_x, min_y = mid_y, fmin = fmid;
        else
            max_x = mid_x, max_y = mid_y;
    }

    cout << "Solution is at point x = " << mid_x << " y = " << mid_y << endl;
}

//bisekcja dla klasy z metodą evaluate
template <typename Functor, typename ArgType, typename = evaluate_expr<Functor>>
void bisection(Functor functor, ArgType min, ArgType max, double tol)
{    
    bisection_impl(functor, min, max, tol);
}

template <typename Functor, typename ArgType, typename = evaluate_expr<Functor>>
void bisection(Functor functor, ArgType *min, ArgType *max, double tol)
{
    bisection_impl(functor, min, max, tol);
}

//bisekcja dla funkcji
template <typename ArgType>
void bisection(ArgType function(ArgType), ArgType min, ArgType max, double tol)
{
    bisection_impl(function, min, max, tol);
}

template <typename ArgType>
void bisection(ArgType function(ArgType, ArgType), ArgType *min, ArgType *max, double tol)
{
    bisection_impl(function, min, max, tol);
}

//bisekcja dla obiektów z przestrzeni Y
template <typename Functor, typename ArgType, typename... DummyArgs>
void bisection(Functor constant, ArgType min, ArgType max, double tol, DummyArgs... SFINAEDummyArgs)
{
    if (min > 0 or max < 0)
        cout << "There is no solution" << endl;
    else
        cout << "Solution is at point x = 0" << endl;
}

template <typename Functor, typename ArgType, typename... DummyArgs>
void bisection(Functor constant, ArgType *A, ArgType *B, double tol, DummyArgs... SFINAEDummyArgs)
{
    ArgType A_x = A[0], A_y = A[1];
    ArgType B_x = B[0], B_y = B[1];

    // ax + ay == 0 <==> y == -x
    //Współrzędne prostej przechodzącej przez A, B ( y(x) = ax + b )
    ArgType a = (A_y - B_y) / (A_x - B_x);
    ArgType b = A_y - (a * A_x);

    ArgType possible_solution = -b / (a + 1); // Rozwiązując y(x) = -x

    if (possible_solution > min(A_x, B_x) && possible_solution < max(A_x, B_x)) // Sprawdzamy czy rozwiązanie jest w zadanym przedziale
        cout << "Solution is at point x = " << possible_solution << " y = " << -possible_solution << endl;
    else
        cout << "There is no solution" << endl;
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
    bisection(g1, 0., 2., .001);
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