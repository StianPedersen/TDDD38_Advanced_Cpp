#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

int main()
{
    char *c{new char{'s'}};

    int array[10] = {1,
                     2,
                     3,
                     4,
                     5,
                     6,
                     7,
                     8,
                     9,
                     0};

    string word1 = "JABADABADOO";
    string word2 = "nummeros dos";
    string word3 = "numeres tres";
    std::string *array_str[3] = {&word1,
                                 &word2,
                                 &word3};

    char **c_pointpoint{new char *{new char{'s'}}};

    int const i{3};
    cout << i << endl;

    int const *i2{&i};
    cout << *i2 << endl;

    int *const i3{0};
    cout << i3 << endl;
}