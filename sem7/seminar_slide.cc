#include <sstream>
#include <iostream>
#include <string>
using namespace std;
int main()
{
    stringstream ss{};
    ss << "123a bc hello";
    int n{};
    char c{};
    string str{};
    if (ss >> n >> n >> c)
        cout << n << "";
    ss.clear();
    if (ss >> c >> c)
        cout << c << "";
    ss.clear();
    if (ss >> str)
        cout << str << "";
}