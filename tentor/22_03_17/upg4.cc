#include <iostream>
#include <cassert>
#include <sstream>
#include <vector>
#include <utility>

template <typename T>
class Stack
{
public:
    template <typename... Ts>
    Stack(Ts... list) : data{std::forward<Ts>(list)...} {}

    bool operator==(T const &d) const
    {
        if (d == data.back())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    Stack &operator<<(T const d)
    {
        data.emplace_back(d);
        return *this;
    }

    Stack &operator>>(T &d)
    {
        d = data.back();
        data.pop_back();
        return *this;
    }

    explicit operator bool()
    {
        if (!data.empty())
            return true;
        else
            return false;
    };

    template <typename T2>
    friend std::ostream &operator<<(std::ostream &os, Stack<T2> &st);

private:
    std::vector<T> data;
};
template <typename T>
std::ostream &operator<<(std::ostream &os, Stack<T> &st)
{
    for (int i = st.data.size() - 1; i >= 0; i--)
    {
        os << st.data.at(i) << " ";
    }
    return os;
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