#include <iostream>
#include <cassert>
#include <sstream>
#include <vector>
#include <utility>
using namespace std;

template <typename T>
class Stack{
    public:
        template<typename... Ts>
        Stack(Ts&&... list) : storage{list...}{}
        
        explicit operator bool()
        {
            return !storage.empty();
        }


        bool operator ==(int i)
        {
            return this->storage.back() == i;
        }

        Stack& operator <<(T param)
        {
            this->storage.push_back(param);
            return *this;
        }

        Stack& operator >>(T& param)
        {
            param = storage.back();
            storage.erase(storage.end()-1);
            return *this;
        }
        template <typename U>
        friend ostream& operator <<(ostream& os, Stack<U>& p);
    private:
        std::vector<T> storage;
};

template <typename U>
ostream& operator <<(ostream& os, Stack<U>& p)
{  
    for(auto it = end(p.storage)-1;it != begin(p.storage)-1;--it)
    {
        os<<*it<<" ";
    }    
return os;
}

int main()
{
    {
	Stack<int> st { 6, 5, 4 };
    
	// 4 should be at the top of the stack
	assert( st == 4 );
	
	// pushing 3, 2 and 1 to the stack
	st << 3 << 2 << 1;

	// now 1 should be at the top
	assert( st == 1 );
	
	// stack must be convertible to bool
	assert( st );

	std::ostringstream oss { };
	oss << st;
	assert( oss.str() == "1 2 3 4 5 6 ");

	// popping into a, b and c as a chained operator call.
	int a, b, c;
	st >> a >> b >> c;

	assert( a == 1 );
	assert( b == 2 );
	assert( c == 3 );

	// pop the values one by one
	int i { 4 };
	while (st)
	{
	    int x;
	    st >> x;

	    assert(x == i);
	    ++i;
	}

	// now the list should be empty
	assert( !st );
    }

}