#include <cassert>
#include <iostream>
#include "deque.h"

int main()
{

    deque<int, 3> d{};
    deque<int, 3> const &c{d};

    assert(d.size() == 0);
    assert(c.size() == 0);

    try
    {
        d.pop_back();
        assert(false);
    }
    catch (...)
    {
    }

    try
    {
        d.pop_front();
        assert(false);
    }
    catch (...)
    {
    }

    try
    {
        d.at(0);
        assert(false);
    }
    catch (...)
    {
    }

    d.push_back(1);
    std::cout << "kommer hit" << std::endl;

    assert(d.size() == 1);
    assert(d.at(0) == 1);
    // assert(d[0] == 1);
    // assert(c.at(0) == 1);
    // assert(c[0] == 1);

    // int *ptr1{&d[0]};

    // d.push_back(3);
    // d.push_back(5);
    // d.push_back(2);

    // int *ptr2{&d[3]};

    // assert(d.size() == 4);
    // assert(d[0] == 1);
    // assert(d[1] == 3);
    // assert(d[2] == 5);
    // assert(d[3] == 2);

    // d.push_front(7);
    // assert(d[0] == 7);
    // assert(d[1] == 1);
    // assert(d[2] == 3);
    // assert(d[3] == 5);
    // assert(d[4] == 2);

    // d.push_front(12);
    // assert(d[0] == 12);
    // assert(d[1] == 7);
    // assert(d[2] == 1);
    // assert(d[3] == 3);
    // assert(d[4] == 5);
    // assert(d[5] == 2);

    // d.push_front(-5);
    // assert(d[0] == -5);
    // assert(d[1] == 12);
    // assert(d[2] == 7);
    // assert(d[3] == 1);
    // assert(d[4] == 3);
    // assert(d[5] == 5);
    // assert(d[6] == 2);

    // d.push_back(-99);
    // assert(d[0] == -5);
    // assert(d[1] == 12);
    // assert(d[2] == 7);
    // assert(d[3] == 1);
    // assert(d[4] == 3);
    // assert(d[5] == 5);
    // assert(d[6] == 2);
    // assert(d[7] == -99);

    // assert(d.size() == 8);

    // {W
    //     auto cpy{d};

    //     cpy.pop_front();
    //     assert(cpy[0] == 12);
    //     assert(cpy[1] == 7);
    //     assert(cpy[2] == 1);
    //     assert(cpy[3] == 3);
    //     assert(cpy[4] == 5);
    //     assert(cpy[5] == 2);
    //     assert(cpy[6] == -99);
    //     assert(cpy.size() == 7);

    //     cpy.pop_front();
    //     assert(cpy[0] == 7);
    //     assert(cpy[1] == 1);
    //     assert(cpy[2] == 3);
    //     assert(cpy[3] == 5);
    //     assert(cpy[4] == 2);
    //     assert(cpy[5] == -99);
    //     assert(cpy.size() == 6);

    //     cpy.pop_front();
    //     assert(cpy[0] == 1);
    //     assert(cpy[1] == 3);
    //     assert(cpy[2] == 5);
    //     assert(cpy[3] == 2);
    //     assert(cpy[4] == -99);
    //     assert(cpy.size() == 5);

    //     cpy.pop_front();
    //     assert(cpy[0] == 3);
    //     assert(cpy[1] == 5);
    //     assert(cpy[2] == 2);
    //     assert(cpy[3] == -99);
    //     assert(cpy.size() == 4);

    //     cpy.pop_front();
    //     assert(cpy[0] == 5);
    //     assert(cpy[1] == 2);
    //     assert(cpy[2] == -99);
    //     assert(cpy.size() == 3);

    //     cpy.pop_front();
    //     assert(cpy[0] == 2);
    //     assert(cpy[1] == -99);
    //     assert(cpy.size() == 2);

    //     cpy.pop_front();
    //     assert(cpy[0] == -99);
    //     assert(cpy.size() == 1);

    //     cpy.pop_front();
    //     assert(cpy.size() == 0);
    // }

    // {
    //     auto cpy{d};

    //     cpy.pop_back();
    //     assert(cpy[0] == -5);
    //     assert(cpy[1] == 12);
    //     assert(cpy[2] == 7);
    //     assert(cpy[3] == 1);
    //     assert(cpy[4] == 3);
    //     assert(cpy[5] == 5);
    //     assert(cpy[6] == 2);
    //     assert(cpy.size() == 7);

    //     cpy.pop_back();
    //     assert(cpy[0] == -5);
    //     assert(cpy[1] == 12);
    //     assert(cpy[2] == 7);
    //     assert(cpy[3] == 1);
    //     assert(cpy[4] == 3);
    //     assert(cpy[5] == 5);
    //     assert(cpy.size() == 6);

    //     cpy.pop_back();
    //     assert(cpy[0] == -5);
    //     assert(cpy[1] == 12);
    //     assert(cpy[2] == 7);
    //     assert(cpy[3] == 1);
    //     assert(cpy[4] == 3);
    //     assert(cpy.size() == 5);

    //     cpy.pop_back();
    //     assert(cpy[0] == -5);
    //     assert(cpy[1] == 12);
    //     assert(cpy[2] == 7);
    //     assert(cpy[3] == 1);
    //     assert(cpy.size() == 4);

    //     cpy.pop_back();
    //     assert(cpy[0] == -5);
    //     assert(cpy[1] == 12);
    //     assert(cpy[2] == 7);
    //     assert(cpy.size() == 3);

    //     cpy.pop_back();
    //     assert(cpy[0] == -5);
    //     assert(cpy[1] == 12);
    //     assert(cpy.size() == 2);

    //     cpy.pop_back();
    //     assert(cpy[0] == -5);
    //     assert(cpy.size() == 1);

    //     cpy.pop_back();
    //     assert(cpy.size() == 0);
    // }

    // assert(*ptr1 == 1);
    // assert(*ptr2 == 2);
}