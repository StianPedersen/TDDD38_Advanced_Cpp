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

void print(){};

template <typename T, typename... Ts>
void print(T t, Ts... list)
{
    std::cout << std::forward<T>(t);
    ((std::cout << ' ' << std::forward<Ts>(list)), ...);
    std::cout << std::endl;
};

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