#include <cstddef> // gives access to size_t
#include <iostream>
#include <string>

using namespace std;

template <typename T>
T add(T const &v1, T const &v2)
{
    return v1 + v2;
}

// Your code here
template <typename T, size_t N>
T reduce(T const (&array)[N], T init = {}, T (*foo)(T const &v1, T const &v2) = add<T>)
{
    T result = init;
    for (int i{}; i < N; i++)
    {
        result = foo(result, array[i]);
    }
    return result;
}

double multiply(double const &lhs, double const &rhs)
{
    return lhs * rhs;
}

int main()
{
    double pi[]{0.0505, 0.0505, 0.0405};
    double factorial[]{1.0, 2.0, 3.0, 4.0, 5.0};
    string concat[]{" ", "world"};
    cout << reduce({1, 2, 3, 4, 5}) << endl;
    cout << reduce(pi, 3.0) << endl;
    cout << reduce(factorial, 1.0, multiply) << endl;
    cout << reduce(concat, "hello"s) << endl;
}