// Implement is_const, is_pointer, is_array and is_const_pointer here

//
struct false_type
{
    static bool const value{false};
};

struct true_type
{
    static bool const value{true};
};

// Const
template <typename T>
struct is_const : public false_type
{
};

template <typename T>
struct is_const<T const> : public true_type
{
};

// Pointer
template <typename T>
struct is_pointer : public false_type
{
};

template <typename T>
struct is_pointer<T *> : public true_type
{
};

template <typename T>
struct is_pointer<T *const> : public true_type
{
};

// Array
template <typename T>
struct is_array : false_type
{
};

template <typename T, int N>
struct is_array<T[N]> : true_type
{
};

// Const pointer
template <typename T>
struct is_const_pointer : false_type
{
};

template <typename T>
struct is_const_pointer<T *const> : true_type
{
};

int main()
{
    static_assert(is_const<int const>::value, "is_const failed for 'int const'");
    static_assert(is_const<int *const>::value, "is_const failed for 'int* const'");
    static_assert(!is_const<int>::value, "is_const failed for 'int'");
    static_assert(!is_const<int const *>::value, "is_const failed for 'int const*'");

    static_assert(is_pointer<int *>::value, "is_pointer failed for 'int*'");
    static_assert(is_pointer<int const *>::value, "is_pointer failed for 'int const*'");
    static_assert(is_pointer<int *const>::value, "is_pointer failed for 'int* const'");
    static_assert(!is_pointer<int>::value, "is_pointer failed for 'int'");

    static_assert(is_array<int[5]>::value, "is_array failed for 'int[5]'");
    static_assert(is_array<int const[7]>::value, "is_array failed for 'int const[7]'");
    static_assert(!is_array<int>::value, "is_array failed for 'int'");

    static_assert(is_const_pointer<int *const>::value, "is_const_pointer failed for 'int* const'");
    static_assert(!is_const_pointer<int *>::value, "is_const_pointer failed for 'int*'");
    static_assert(!is_const_pointer<int>::value, "is_const_pointer failed for 'int'");
    static_assert(!is_const_pointer<int const>::value, "is_const_pointer failed for 'int const'");
}