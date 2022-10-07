#include <iostream>
#include "queue.h"
template <typename T, size_t N>
bool Queue<T, N>::empty() const
{
    return head == tail;
};

template <typename T, size_t N>
bool Queue<T, N>::full() const
{
    return N == tail - head;
}

template <typename T, size_t N>
T &Queue<T, N>::front() const
{
    if (empty())
        throw queue_error{"whatibat"};
    return const_cast<T &>(array[head % 5]);
}
template <typename T, size_t N>
void Queue<T, N>::enqueue(T value)
{
    if (tail - head == N)
        throw queue_error{"Enque into full array"};
    array[tail % 5] = value;
    tail++;
}

template <typename T, size_t N>
T Queue<T, N>::dequeue()
{
    if (empty())
        throw queue_error{"Dequeue empty array"};
    T value = array[head % 5];
    head++;
    return value;
}

template <typename T, size_t N>
template <size_t M>
Queue<T, N + M> Queue<T, N>::copy_and_expand()
{
    Queue<T, N + M> q{};
    Queue<T, N> tmp{};
    tmp = *this;
    while (tmp.head != tmp.tail)
    {
        q.enqueue(tmp.dequeue());
    }

    return q;
}