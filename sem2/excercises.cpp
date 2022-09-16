#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

int main()
{
    int x{7};
    int &ref{x};
    // int &ref2{7};Not valid
    int const &ref3{x};
    int &&ref4{7};
    // int &&ref5{x};
    int const &&ref6{7};
    // long long &ref7{x};
}