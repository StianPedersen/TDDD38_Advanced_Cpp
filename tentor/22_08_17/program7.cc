#include <cassert>
#include <cstddef>
#include <iterator>
#include <list>
#include <vector>
#include <iostream>
template<typename T>
int count_bytes(T const& d); 
namespace ns{   
    template<typename T>
    int count_bytes_helper(T const& d, double)
    {
        return sizeof(d);
    }

    template<typename T>
    auto count_bytes_helper(T const& c, int)
    -> decltype(std::begin(c), int{})
    {
    
        int x = 0;
        for(auto const& e : c)
        {
            x += count_bytes(e);
        }
        return x;
    }

}

template<typename T>
int count_bytes(T const&  d) 
{
    return ns::count_bytes_helper(d, 0);
}


int main()
{
    int x { 9 };
    assert(count_bytes(x) == sizeof(int));

    std::vector<int> v { 1, 2, 3 };
    assert(count_bytes(v) == 3 * sizeof(int));

    std::list<std::vector<std::string>> l {
	{ "a", "bc" }, // 3 chars
	{ },           // 0 chars
	{ "defg" },    // 4 chars
    };

    // 3 + 0 + 4 = 7 chars
    assert(count_bytes(l) == 7 * sizeof(char));

    std::vector<int> array[] = {
	{ 1, 2, 3, 4 }, // 4 ints
	{ 5, 6 },       // 2 ints
	{ },            // 0 ints
	{ 7, 8 },       // 2 ints
    };

    // 4 + 2 + 0 + 2 = 8 ints
    assert(count_bytes(array) == 8 * sizeof(int));
}