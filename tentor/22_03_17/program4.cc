#include <iostream>
#include <cassert>
#include <sstream>
#include <vector>
#include <utility>
#include <initializer_list>
#include <ranges>

template <typename T>
class Stack
{
private:
    std::vector<T> my_vec{};

public:
    Stack(std::initializer_list<T> l) : my_vec{l} {}

    Stack<T> &operator<<(T parameter)
    {
        this->my_vec.push_back(parameter);
        return *this;
    };

    Stack<T> &operator>>(T &v)
    {
        v = my_vec.back();
        my_vec.pop_back();
        return *this;
    }

    operator T()
    {
        return my_vec.back();
    };

    operator bool()
    {
        if (my_vec.empty())
            return false;
        else
            return true;
    };

    friend std::ostream &operator<<(std::ostream &os, const Stack &s)
    {
        for (auto it = s.my_vec.rbegin(); it != s.my_vec.rend(); it++)
            os << *it << " ";
        return os;
    };
};

int main()
{
    {
        Stack<int> st{6, 5, 4};

        // 4 should be at the top of the stack
        assert(st == 4);

        // pushing 3, 2 and 1 to the stack
        st << 3 << 2 << 1;

        // now 1 should be at the top
        assert(st == 1);

        // stack must be convertible to bool
        assert(st);

        std::ostringstream oss{};
        oss << st;
        assert(oss.str() == "1 2 3 4 5 6 ");

        // popping into a, b and c as a chained operator call.
        int a, b, c;
        st >> a >> b >> c;
        assert(a == 1);
        assert(b == 2);
        assert(c == 3);

        // pop the values one by one
        int i{4};
        while (st)
        {
            int x;
            st >> x;

            assert(x == i);
            ++i;
        }

        // now the list should be empty
        assert(!st);
    }
}