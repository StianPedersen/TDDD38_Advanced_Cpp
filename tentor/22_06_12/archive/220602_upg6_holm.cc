#include <cassert>
#include <iostream>
#include <list>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace details
{

    template <typename Container, typename T>
    auto prepend(Container& container, T&& value, int, int)
	-> decltype( container.push_front(value), std::declval<void>() )
    {
	container.push_front(std::forward<T>(value));
    }
    
    template <typename Container, typename T>
    auto prepend(Container& container, T&& value, int, float)
	-> decltype( container = value + container, std::declval<void>() )
    {
	container = std::forward<T>(value) + container;
    }

    template <typename Container, typename T>
    auto prepend(Container& container, T&& value, float, float)
	-> decltype( container.insert(container.begin(), value), std::declval<void>() )
    {
	container.insert(container.begin(), std::forward<T>(value));
    }
    
}

template <typename Container, typename T>
void prepend(Container& container, T&& value)
{
    details::prepend(container, std::forward<T>(value), 0, 0);
}

int main()
{
    std::vector<int> v { 1, 2, 3 };

    assert(v.front() == 1);
    prepend(v, 0);
    assert(v.front() == 0);
    
    std::list<float> d { 1.2f, 3.45f, 67.8f, 9.0f };

    assert(d.front() == 1.2f);
    prepend(d, 0);
    assert(d.front() == 0.0f);

    std::string s { "ello world!" };

    assert(s.front() == 'e');
    prepend(s, 'H');
    assert(s.front() == 'H');
}