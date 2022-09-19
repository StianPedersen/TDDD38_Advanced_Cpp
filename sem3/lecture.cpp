#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

struct Base
{
    virtual ~Base() = default;
};
struct Derived1 : public Base
{
};
struct Derived11 : public Derived1
{
};
struct Derived2 : public Base
{
};
int main()
{
    Base *bp{new Derived1()};
    if (dynamic_cast<Base *>(bp)) // OK
        cout << "B";
    if (dynamic_cast<Derived1 *>(bp)) // Ok
        cout << "D1";
    if (dynamic_cast<Derived11 *>(bp)) // Not ok
        cout << "D11";
    if (dynamic_cast<Derived2 *>(bp)) // Not OK
        cout << "D2";
}