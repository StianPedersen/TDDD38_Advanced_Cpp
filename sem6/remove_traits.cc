#include <type_traits>

template <typename T>
struct remove_reference
{
    using type = T;
};

// implement your specializations here
template <typename T>
struct remove_reference<T &&>
{
    using type = T;
};

template <typename T>
struct remove_reference<T &>
{
    using type = T;
};
// implement remove_pointers here
template <typename T>
struct remove_pointers
{
    using type = T;
};

template <typename T>
struct remove_pointers<T *>
{
    using type = typename remove_pointers<T>::type;
};

template <typename T>
struct remove_pointers<T const>
{
    using type = typename remove_pointers<T>::type;
};

int main()
{
    static_assert(std::is_same<
                      remove_reference<int &&>::type, int>::value,
                  "remove_reference failed for 'int&&'");
    static_assert(std::is_same<
                      remove_reference<int &>::type, int>::value,
                  "remove_reference failed for 'int&'");
    static_assert(std::is_same<
                      remove_reference<int>::type, int>::value,
                  "remove_reference failed for 'int'");
    static_assert(std::is_same<
                      remove_reference<int const &>::type, int const>::value,
                  "remove_reference failed for 'int const&'");

    static_assert(std::is_same<
                      remove_pointers<int>::type, int>::value,
                  "remove_pointers failed for 'int'");
    static_assert(std::is_same<
                      remove_pointers<int *>::type, int>::value,
                  "remove_pointers failed for 'int*'");
    static_assert(std::is_same<
                      remove_pointers<int *const>::type, int>::value,
                  "remove_pointers failed for 'int* const'");
    static_assert(std::is_same<
                      remove_pointers<int *const *>::type, int>::value,
                  "remove_pointers failed for 'int* const*'");
    static_assert(std::is_same<
                      remove_pointers<int ***>::type, int>::value,
                  "remove_pointers failed for 'int***'");
}