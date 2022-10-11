#include <type_traits>
#include <iostream>
template <typename... Ts>
class Pack
{
};

template <typename T, typename First, typename... Ts>
bool contains(Pack<First, Ts...>)
{
    if (std::is_same_v<T, First>)
        return true;
    else
    {
        Pack<Ts...> rest;
        return contains<T>(rest);
    }
}
template <typename T>
bool contains(Pack<>)
{
    return false;
}

template <typename T, typename First, typename... Ts>
int index_of(Pack<First, Ts...>, int counter)
{
    if (std::is_same_v<T, First>)
        return counter;
    else
    {
        Pack<Ts...> package;
        return index_of<T>(package, ++counter);
    }
}

template <typename T>
int index_of(Pack<>, int index = 0)
{
    return -1;
}

template <typename T, typename... Ts>
int index_of(Pack<Ts...> p)
{
    return index_of<T>(p, 0);
}

int main()
{
    Pack<int, float, char> p;
    std::cout << contains<int>(p) << std::endl;  // should return true
    std::cout << contains<bool>(p) << std::endl; // should return false
    std::cout << index_of<int>(p) << std::endl;  // should return 0
    std::cout << index_of<char>(p) << std::endl; // should return 2
    std::cout << index_of<bool>(p) << std::endl; // should return -1
}