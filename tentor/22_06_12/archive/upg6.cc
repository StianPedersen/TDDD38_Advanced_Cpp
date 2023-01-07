#include <cassert>
#include <iostream>
#include <list>
#include <string>
#include <vector>

namespace ns
{
    template <typename Container, typename T>
    auto prepend_helper(Container &c, T &&val, long, long)
        -> decltype(c.insert(std::begin(c), val), std::declval<void>())
    {
        std::cout << "first" << std::endl;
        c.insert(std::begin(c), val);
    }

    template <typename Container, typename T>
    auto prepend_helper(Container &c, T &&val, long, int)
        -> decltype(c.push_front(val), std::declval<void>())
    {
        std::cout << "second" << std::endl;

        c.push_front(val);
    }

    template <typename Container, typename T>
    auto prepend_helper(Container &c, T &&val, int, int)
        -> decltype(c + val, std::declval<void>())
    {
        std::cout << "third" << std::endl;
        c = val + c;
    }

};

template <typename Container, typename T>
void prepend(Container &c, T &&val)
{
    ns::prepend_helper(c, std::forward<T>(val), 0, 0);
};

int main()
{
    std::vector<int> v{1, 2, 3};

    assert(v.front() == 1);
    prepend(v, 0);
    assert(v.front() == 0);

    std::list<float> d{1.2f, 3.45f, 67.8f, 9.0f};

    assert(d.front() == 1.2f);
    prepend(d, 0);
    assert(d.front() == 0.0f);

    std::string s{"ello world!"};

    assert(s.front() == 'e');
    prepend(s, 'H');
    assert(s.front() == 'H');
}