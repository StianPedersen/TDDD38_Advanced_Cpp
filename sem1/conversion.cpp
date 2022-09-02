#include <iostream>
using namespace std;
void foo() { cout << "foo" << endl; }

int main()
{
    int array[5]{1, 2, 3, 4, 5};
    cout << array << endl;

    char str[4]{'h', 'i', '!', '\0'};
    cout << str << endl;

    cout << foo << endl;

    int var(int());
    cout << var << endl;
}
