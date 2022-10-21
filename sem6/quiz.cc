#include <type_traits>
#include <iostream>

template <int N, int M>
void foo(std::enable_if_t<(N > 0 && N < M), int> = {})
{
    std::cout << 1;
};

template <int N, int M>
std::enable_if_t<(N == 0)> foo()
{
    std::cout << 2;
};

template <int N, int M, typename = std::enable_if_t<(N > 0 && N > M)>>
void foo()
{
    std::cout << 3;
};

int main()
{
    foo<1, 3>(0);
    foo<3, 1>();
    foo<0, 1>();
    foo<0, 1, int>();
}