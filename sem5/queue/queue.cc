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
    return head == tail - 5;
}

template <typename T, size_t N>
T &Queue<T, N>::front() const
{
    if (empty())
        throw queue_error{"whatibat"};
    return const_cast<T &>(array[head]);
}