#include <cassert>
#include <iostream>
#include <list>
#include <string>
#include <vector>

namespace ns{
    template <typename C, typename T>
    auto prepend_helper(C& c, T&& d,int,int)
    ->decltype(c.push_front(d), std::declval<void>())
    {
        std::cout<<"First called"<<std::endl;
        c.push_front(std::forward<T>(d));
    }

    template <typename C, typename T>
    auto prepend_helper(C& c, T&& d,double,double)
    ->decltype(c.insert(std::begin(c),d),std::declval<void>())
    {
        std::cout<<"Second called"<<std::endl;
        c.insert(std::begin(c),std::forward<T>(d));
    }

    template <typename C, typename T>
    auto prepend_helper(C& c, T&& d, double, int)
    ->decltype(c = d + c, std::declval<void>())
    {
        std::cout<<"Third called"<<std::endl;
        c = std::forward<T>(d) + c;

    }

}


template<typename C, typename T>
void prepend(C& c, T && d)
{
    ns::prepend_helper(c,std::forward<T>(d),0,0);
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