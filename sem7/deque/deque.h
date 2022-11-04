#include <stdexcept>
#include <array>
template <typename T, int N>
class deque
{
private:
    int begin;
    int count;
    int capacity;
    int chunk_count;

    T **data;

public:
    deque() : begin{0}, count{0}, capacity{1}, chunk_count{0}, data{new T *[1] {}} {};
    // ~deque();
    int size() const;
    void pop_back();
    void pop_front();
    void push_back(T val);
    T &at(int i);
};

template <typename T, int N>
int deque<T, N>::size() const
{
    return count;
}

template <typename T, int N>
void deque<T, N>::pop_back()
{
    if (count == 0)
        throw std::out_of_range{"Cannot pop empty deque!"};
}

template <typename T, int N>
void deque<T, N>::pop_front()
{
    if (count == 0)
        throw std::out_of_range{"Cannot pop empty deque!"};
}

template <typename T, int N>
T &deque<T, N>::at(int i)
{
    if (i >= count)
        throw std::out_of_range{"Deque out of range for function at!"};
    else
    {
        throw std::out_of_range{"Deque out of range for function at!"};
        T &b = i;
        return b;
    }
}

template <typename T, int N>
void deque<T, N>::push_back(T val)
{
    std::cout << "kommer hit" << std::endl;

    int select_chunk = (begin + count) / N;
    int select_index = (begin + count) % N;
    std::cout << "kommer hit" << select_index << std::endl;

    data[select_chunk][select_index] = val;

    count++;
}