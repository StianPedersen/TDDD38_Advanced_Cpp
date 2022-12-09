#include <ostream>
#include <iterator>
#include <utility>
#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <array>
#include <string>

template <typename T>
void print(std::ostream &, T const &);
namespace range_ns
{
    template <typename T>
    auto print_range(std::ostream& os, T const& c)
    -> decltype(std::begin(c), std::declval<void>())
    {
        os<<"{";
        for (auto e : c)
            os<<e;
        os<<"}";
        
    }

    template <typename T>
    void print_range(std::ostream &os, std::map<T, T> c)
    {
        for (auto e : c)
            os << "(" << e.first << "," << e.second << ") ";
    }

    template <typename T>
    void print_range(std::ostream &os, std::vector<T> c)
    {
        for (auto e : c)
            os << e;
    }

    template <typename It>
    void print_range(std::ostream &os, It b, It e)
    {
      while(b != e){
        os<<"{";
        ::print(os,*b++);
        os<<"}";
      }
    }

    template <typename T, int N>
    void print_tuple(std::ostream &os, T const &c, std::integer_sequence<int, N>)
    {
        ::print(os, std::get<N>(c));
    }

    template <typename T, int N, int... Ns>
    void print_tuple(std::ostream &os, T const &c, std::integer_sequence<int, N, Ns...>)
    {
        os << '(';
        ::print(os, std::get<N>(c));
        os << ' ';
        print_tuple(os, c, std::integer_sequence<int, Ns...>{});
        os << ')';
    }
}
namespace my_ns
{   

    template <typename T>
    void print_stuff(std::ostream &os, T const &d, long)
    {
        os << d;
    }

    template <typename T>
    auto print_stuff(std::ostream &os, T const &c, int)
        -> decltype(std::begin(c), std::declval<void>())
    {
        range_ns::print_range(os, c);
    }

    template <typename T>
    auto print_stuff(std::ostream &os, T const &c, int)
        -> decltype(std::tuple_size<T>(), std::declval<void>())
    {
        range_ns::print_tuple(os, c, std::make_integer_sequence<int, std::tuple_size<T>::value>{});
    }

    template <typename T, std::size_t N>
    void print_stuff(std::ostream& os, std::array<T,N> const& a, int)
    {
        os<<"{";
        range_ns::print_range(os, begin(a), end(a));
        os<<"}";
    }
}

template <typename T>
void print(std::ostream &os, T const &data)
{
    my_ns::print_stuff(os, data, 0);
}

/* This should give the following output (or something similar at least):
5
{1, 2, 3}
{(1 1), (2 2), (3 3)}
(5 3.14)
{hello, world}
{{ab, c}, {def, g, hi}}
SFINAE
string literal
 */
int main()
{
    print(std::cout, 5);
    std::cout << std::endl;

    std::vector<int> v{1, 2, 3};
    print(std::cout, v);
    std::cout << std::endl;

    std::map<int, int> m{{1, 1}, {2, 2}, {3, 3}};
    print(std::cout, m);
    std::cout << std::endl;

    std::tuple<int, double> t{5, 3.14};
    print(std::cout, t);
    std::cout << std::endl;

    std::string s[]{"hello", "world"};
    print(std::cout, s);
    std::cout << std::endl;

    std::array<std::vector<std::string>, 2> a{
    std::vector<std::string>{"ab", "c"},
    std::vector<std::string>{"def", "g", "hi"}};
    print(std::cout, a);
    std::cout << std::endl;

    char const *str{"SFINAE"};
    print(std::cout, str);
    std::cout << std::endl;

    print(std::cout, "string literal");
    std::cout << std::endl;
}