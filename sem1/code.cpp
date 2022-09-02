#include <iostream>
using namespace std;

// int &get()
// {
//     int x{5};
//     return x;
// }
int const *get2()
{
    return new int{5};
}
int main()
{
    // cout << get() << endl;
    int const *const x{get2()};
    cout << x << endl;
    delete x;
}
