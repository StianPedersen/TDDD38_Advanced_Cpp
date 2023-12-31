#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

struct Cls
{
    Cls() = default;
    Cls(Cls const &)
    {
        cout << "C";
    }
    Cls(Cls &&)
    {
        cout << "M";
    }
    ~Cls() = default;
};
Cls ident(Cls c)
{
    return c;
}
int main()
{
    Cls c1{Cls{}};     // Cout C
    Cls c2{ident(c1)}; // Cout M? Copy elision?
    Cls c3{c2};        // Cout C
}