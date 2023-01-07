#include <cassert>
#include <string>
#include <utility>

class Sentinel
{
};

template <int N, typename T>
struct Get_Index
{
    static auto &value(T &psl)
    {
        return Get_Index<N - 1, typename T::second_type>::value(psl.second);
    }
};

template <typename T>
struct Get_Index<0, T>
{
    static auto &value(T &psl)
    {
        return psl.first;
    }
};

auto make_list()
{
    return new Sentinel{};
}

template <typename First, typename... Ts>
auto make_list(First f, Ts... list)
{

    return std::make_pair(f, make_list(list...));
};

template <int N, typename Ts>
auto &get_index(Ts &list)
{
    return Get_Index<N, Ts>::value(list);
};

int main()
{
    std::string last{"54"};
    auto list1 = make_list(1, 2.3, '4', last);
    assert(get_index<0>(list1) == 1);
    assert(get_index<1>(list1) == 2.3);
    assert(get_index<2>(list1) == '4');
    assert(get_index<3>(list1) == "54");

    // // Check that the values can be modified
    get_index<0>(list1) = 10;
    assert(get_index<0>(list1) == 10);
}
// ‘std::pair<int, std::pair<double, std::pair<char, std::pair<std::__cxx11::basic_string<char>, Sentinel*> > > >’
// to
// ‘std::pair<double, std::pair<char, std::pair<std::__cxx11::basic_string<char>, Sentinel*> > >&’
