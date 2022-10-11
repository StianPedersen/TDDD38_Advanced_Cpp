#include <iostream>

template <int N, typename... Ts>
struct Cls;

template <int N, typename T, typename... Ts>
struct Cls<N, T, Ts...>
{
    static const int value{N + Cls<N - 1, Ts...>::value};
};

template <typename T, typename... Ts>
struct Cls<1, T, Ts...>
{
    static const int value{0};
};

template <int N>
struct Cls<N>
{
    static const int value{N};
};

int main()
{
    std::cout << Cls<4, int>::value
              << Cls<3, int, float, double>::value
              << Cls<2, double, float, Cls<3>>::value
              << Cls<4, int, float>::value;
}