#include <stdexcept>
#include <array>
#include <algorithm>
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
    deque(deque<T, N> const &d);

    void add_chunk();
    int size() const;
    void pop_back();
    void pop_front();
    void push_back(T val);

    void push_front(T val);
    void add_chunk_front();

    T &at(int i);
    T &at(int i) const;

    T &operator[](int i);
    T &operator[](int i) const;
};

template <typename T, int N>
deque<T, N>::deque(deque<T, N> const &d) : deque{}
{
    for (int i = 0; i < d.size(); i++)
    {
        push_back(d[i]);
    }
}

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
    else
    {
        count--;
    }
}

template <typename T, int N>
void deque<T, N>::pop_front()
{
    if (count == 0)
        throw std::out_of_range{"Cannot pop empty deque!"};
    else
    {
        begin++;
        count--;
    }
}

template <typename T, int N>
T &deque<T, N>::at(int i)
{
    return const_cast<T &>(static_cast<deque const *>(this)->at(i)); // TODO ASK WHY
}

template <typename T, int N>
T &deque<T, N>::at(int i) const
{
    if (i >= count)
        throw std::out_of_range{"Deque out of range for function at!"};
    else
    {
        int select_chunk = (begin + i) / N;
        int select_index = (begin + i) % N;
        return data[select_chunk][select_index];
    }
}

template <typename T, int N>
void deque<T, N>::add_chunk()
{
    // reallocated_chunk_array();
    data[chunk_count] = new T[N];
    chunk_count++;
}
template <typename T, int N>
void deque<T, N>::push_back(T val)
{

    int select_chunk = (begin + count) / N;
    int select_index = (begin + count) % N;
    if (select_index == 0)
    {
        add_chunk();
    }
    data[select_chunk][select_index] = val;
    count++;
}
template <typename T, int N>
T &deque<T, N>::operator[](int i) const
{
    int select_chunk = (begin + i) / N;
    int select_index = (begin + i) % N;
    return data[select_chunk][select_index];
}

template <typename T, int N>
T &deque<T, N>::operator[](int i)
{
    return const_cast<T &>(static_cast<deque const *>(this)->operator[](i));
}

template <typename T, int N>
void deque<T, N>::add_chunk_front()
{
    std::move(data, data + chunk_count, data + 1);
    data[0] = new T[N];
    chunk_count++;
}

template <typename T, int N>
void deque<T, N>::push_front(T val)
{
    if (begin > 0)
    {
        begin--;
    }
    else if (begin <= 0)
    {
        add_chunk_front();
        begin = N - 1;
    }
    data[0][begin] = val;
    ++count;
}
