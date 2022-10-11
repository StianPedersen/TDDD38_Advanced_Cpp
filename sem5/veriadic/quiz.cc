#include <iostream>

template <typename T, int N>
struct Cls
{
    static void foo() { std::cout << 1; }
};

template <typename T>
struct Cls<T, 0>
{
    static void foo() { std::cout << 2; }
};

template <int N>
struct Cls<int, N>
{
    static void foo() { std::cout << 3; }
};

template <>
struct Cls<int, 0>
{
    static void foo() { std::cout << 4; }
};

int main()
{
    Cls<double, 0>::foo();
    Cls<double, 5>::foo();
    Cls<int, 3>::foo();
    Cls<unsigned, 0>::foo();
}