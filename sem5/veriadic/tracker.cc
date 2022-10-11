#include <string>
#include <iostream>
#include <utility>

// Forward decleration
template <typename T>
int count();

template <typename T>
class Tracker : public T
{
public:
    template <typename... Ts>
    Tracker(Ts... list) : T(list...) { counter++; };

    Tracker(Tracker<T> &&) = default;
    Tracker(Tracker<T> const &other) : T(other) { counter++; };
    Tracker &operator=(Tracker<T> const &other)
    {
        Tracker<T> tmp{other};
        return *this = std::move(tmp);
    };
    ~Tracker() { counter--; };

    static int counter;
};

template <typename T>
int Tracker<T>::counter{0};

template <typename T>
int count()
{
    return Tracker<T>::counter;
}

struct Hello_Worlder
{
    std::string get()
    {
        return "hello world!";
    }
};

/* The output should be:

0
str1 str2
hello world!
++++++++++
3
1
2

*/

int main()
{
    using std::cout;
    using std::endl;
    using std::string;

    cout << count<string>() << endl;

    Tracker<string> str1{};
    str1 += "str1";
    for (char c : str1)
    {
        cout << c;
    }
    Tracker<string> str2{"str2"};
    cout << " " << str2 << endl;

    Tracker<Hello_Worlder> hw{};
    cout << hw.get() << endl;

    {
        Tracker<string> str3(10u, '+');
        cout << str3 << endl;
        cout << count<string>() << endl;
    }
    cout << count<Hello_Worlder>() << endl;
    cout << count<string>() << endl;
}