#include <cassert>
#include <iostream>

void test()
{
    std::cout << "Function call!" << std::endl;
}

int add(int a, int b)
{
    return a + b;
}

struct Test
{
    void operator()()
    {
        std::cout << "Function object call!" << std::endl;
    }
};

struct Multiply
{
    int operator()(int a, int b)
    {
        return a * b;
    }
};

template <typename Ret>
class Function
{
};

template <typename Ret, typename... Args>
class Function<Ret(Args...)>
{
public:
    class Callable_Base
    {
    public:
        virtual ~Callable_Base() = default;
        virtual Ret call(Args...) = 0;
    };

    template <typename T>
    class Callable : public Callable_Base
    {
    public:
        Callable(T r) : callback{r} {}
        Ret call(Args... list) override
        {
            return callback(list...);
        };

    private:
        T callback;
    };

    Ret operator()(Args... list)
    {
        return storage->call(list...);
    };

    template <typename T>
    Function &operator=(T obj)
    {
        delete storage;
        auto tmp = new Callable<T>(obj);
        storage = tmp;
        return *this;
    }

    template <typename T>
    Function(T t) : storage{new Callable<T>(t)} {}
    ~Function() { delete storage; }

private:
    Callable_Base *storage{nullptr};
};

/* Expected output:
==== Testcase 1: void() ====
Function call!
Function object call!
x = 5
==== Testcase 2: int(int, int) ====
7 * 4 = 28
3 + 5 = 8
11 - 5 = 6
*/
int main()
{

    std::cout << "==== Testcase 1: void() ====" << std::endl;
    {
        Function<void()> fun{test};
        fun();

        fun = Test{};
        fun();

        int x{5};
        fun = [&x]()
        { std::cout << "x = " << x << std::endl; };
        fun();
    }

    std::cout << "==== Testcase 2: int(int, int) ====" << std::endl;
    {
        Function<int(int, int)> fun{Multiply{}};

        std::cout << "7 * 4 = " << fun(7, 4) << std::endl;

        fun = add;
        std::cout << "3 + 5 = " << fun(3, 5) << std::endl;

        fun = [](int a, int b)
        { return a - b; };
        std::cout << "11 - 5 = " << fun(11, 5) << std::endl;
    }
}