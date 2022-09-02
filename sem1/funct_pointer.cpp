#include <iostream>
using namespace std;

int add(int x, int y)
{
    return x + y;
}
int sub(int x, int y)
{
    return x - y;
}

double multiply(double x, double y)
{
    return x * y;
}
int main()
{
    // pointer to function taking
    // two int:s and returning int
    int (*ptr)(int, int);
    double (*myptr)(double, double);
    myptr = multiply;
    ptr = add;
    // print 2
    std::cout << ptr(1, 1) << std::endl;
    ptr = sub;
    // print 0
    std::cout << ptr(1, 1) << std::endl;

    // Print 5
    std::cout << myptr(10, 0.5) << std::endl;
}
