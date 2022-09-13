#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

void fun(int const &) { cout << 1; }
void fun(int &) { cout << 2; }
void fun(int &&) { cout << 3; }
int main()
{
    int a;
    int const c{};
    fun(23); // Prints 3
    fun(a);  // Prints 2
    fun(c);  // Prints 1
}