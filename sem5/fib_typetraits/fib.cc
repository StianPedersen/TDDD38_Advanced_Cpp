#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>
using namespace std;

template <int N>
class Fibonacci
{
public:
    static const int value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;
};

template <>
class Fibonacci<1>
{
public:
    static const int value{1};
};

template <>
class Fibonacci<0>
{
public:
    static const int value{0};
};

int main()
{
    assert(Fibonacci<0>::value == 0);
    assert(Fibonacci<1>::value == 1);
    assert(Fibonacci<5>::value == 5);
    assert(Fibonacci<10>::value == 55);
    assert(Fibonacci<12>::value == 144);
}