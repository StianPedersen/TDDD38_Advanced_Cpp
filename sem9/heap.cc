#include <algorithm>
#include <vector>
#include <initializer_list>
#include <functional>
#include <iostream>

// Implement Heap here
template <typename T, typename Compare = std::less<T>>
class Heap
{
    using const_iterator = typename std::vector<T>::const_iterator;

public:
    Heap(std::initializer_list<T> d, Compare comp = {}) : data{d.begin(), d.end()}, compare{comp}
    {
        std::make_heap(std::begin(data), std::end(data), compare);
    };

    const_iterator begin()
    {
        return std::begin(data);
    };

    const_iterator end()
    {
        return std::end(data);
    };

    void pop()
    {
        std::pop_heap(std::begin(data), std::end(data), compare);
        data.pop_back();
    }

    T &front()
    {
        return data[0];
    }

    void push(T d)
    {
        data.push_back(d);
        std::push_heap(std::begin(data), std::end(data), compare);
    }

private:
    std::vector<T> data{};
    Compare compare;
};

int main()
{

    {
        Heap<int> heap{1, 3, 4, 7, 9, 10};

        std::cout << "int heap with std::less:" << std::endl;

        std::cout << "\tCreation   : ";
        for (int v : heap)
        {
            std::cout << v << " ";
        }
        std::cout << std::endl;

        std::cout << "\tMax element: " << heap.front() << std::endl;

        heap.pop();

        std::cout << "\tAfter pop  : ";
        for (int v : heap)
        {
            std::cout << v << " ";
        }
        std::cout << std::endl;

        heap.push(11);

        std::cout << "\tPush 11    : ";
        for (int v : heap)
        {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }

    {
        Heap<std::string, std::greater<std::string>> heap{"A", "AB", "C", "DE", "EFG"};

        std::cout << "string heap with std::greater: " << std::endl;

        std::cout << "\tCreation   : ";
        for (std::string const &v : heap)
        {
            std::cout << v << " ";
        }
        std::cout << std::endl;

        std::cout << "\tMax element: " << heap.front() << std::endl;

        heap.pop();

        std::cout << "\tAfter pop  : ";
        for (std::string const &v : heap)
        {
            std::cout << v << " ";
        }
        std::cout << std::endl;

        heap.push("CD");

        std::cout << "\tPush \"CD\"  : ";
        for (std::string const &v : heap)
        {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }
}