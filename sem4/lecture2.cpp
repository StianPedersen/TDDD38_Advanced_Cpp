#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

template <typename T>
void fun(T) { cout << 1 << endl; }
template <typename T>
void fun(T *) { cout << 3 << endl; }
template <>
void fun(int *) { cout << 2 << endl; }

int main()
{
    int *x{};
    double *y{};
    fun(1); // 1
    fun(x); // 2
    fun(y); // 3
}