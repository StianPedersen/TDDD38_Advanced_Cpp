#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

template <typename T>
void print(T)
{
    cout << "1";
}
template <>
void print<int>(int)
{
    cout << "2";
}
void print(int &&)
{
    cout << "3";
}
int main()
{
    int x{};
    print(1.0); // 1
    print(1);   // 3
    print(x);   // 2
}