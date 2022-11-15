#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <functional>

int fun1()
{ return 1; }
int fun2(int a) { return a * 3; }
int main() {
std::function<int()> fun{fun1};
fun = std::bind([](int a, int b) {
return a + b;
}, 1, fun());
fun = [fun]() { return 2 * fun(); };
std::cout << std::bind([](int x, int y, int z) 
{
    return fun2(x) + y;
}, _2, _1, 17)(fun(), 3);
}