#include <type_traits>

namespace details
{
    template <typename T, typename U, typename = std::enable_if_t<!std::is_pointer_v<U>>>
    T add_pointers_helper(){};

    // implement add_pointers function template here
    template <typename T, typename U, typename = std::enable_if_t<std::is_pointer_v<U>>>
    auto add_pointers_helper()
    {
        return details::add_pointers_helper<T *, std::remove_pointer_t<U>>();
    };

}

template <typename T, typename U>
struct add_pointers
{
    using type = decltype(details::add_pointers_helper<T, U>());
};

int main()
{
    static_assert(std::is_same_v<add_pointers<int, int>::type, int>, "int + int = int");
    static_assert(std::is_same_v<add_pointers<int, int *>::type, int *>, "int + int* = int*");
    static_assert(std::is_same_v<add_pointers<int *, int *>::type, int **>, "int* + int* = int**");
    static_assert(std::is_same_v<add_pointers<int **, int *>::type, int ***>, "int** + int* = int**");
    static_assert(std::is_same_v<add_pointers<int **, int ***>::type, int *****>, "int** + int*** = int*****");
}