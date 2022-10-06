#include <cstddef>
#include <array>
#include <stdexcept>

class queue_error : std::runtime_error
{
    using std::runtime_error::runtime_error;
};

template <typename T, size_t N>
class Queue
{
public:
    Queue() : array{}, head{}, tail{} {}
    void enqueue(T value);
    T dequeue();
    bool empty() const;
    bool full() const;
    void clear();
    T &front() const;

private:
    T array[N];
    int head;
    int tail;
};