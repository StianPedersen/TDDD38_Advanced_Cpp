// #include "print.h"
#include <iostream>
using namespace std;

struct X
{
};

ostream &operator<<(ostream &os, X const &)
{
    return os << "X";
}

void print_helper(){};

template <typename T, typename... Ts>
void print_helper(T first, Ts... rest)
{
    std::cout << first << " ";
    print_helper(rest...);
};

template <typename... Ts>
void print(Ts... p)
{
    print_helper(p...);
    std::cout << std::endl;
}

int main()
{
    // should produce an empty line
    print();

    // should produce:
    // a 3.5 100 hello
    print('a', 3.5, 100, "hello");

    // should produce:
    // a b
    print('a', 'b');

    // should produce:
    // X Y Z
    print(X{}, "Y", "Z");
}