#include "list.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

int main()
{
    List l{};
    for (int i = 0; i < 10; i++)
        l.insert(i);
    for (int i = 2; i < 10; i = i + 2)
        l.remove(i);

    l.print_list();
    std::cout << l.at(2) << std::endl;
}