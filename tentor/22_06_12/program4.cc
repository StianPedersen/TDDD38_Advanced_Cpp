#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <map>
#include <algorithm>
#include <utility>
#include <set>

using namespace std;
/*

Example runs:

$ ./a.out example.txt 
The following parameters are not defined:
#0
#1
#2
#3

$ ./a.out example.txt first second
The following parameters are not defined:
#2
#3

$ ./a.out example.txt first second third fourth
In this text first is a parameter, and the same is true for second
meaning that first and second can be whatever we want. Also, as a test
we add fourth as well, thus skipping the third argument (but as a test
we include third here).

 */

int main(int argc, char** argv)
{
    if (argc < 2)
    {
	std::cerr << "USAGE: " << argv[0] << " TEXT [PARAMETERS...]\n";
	return 1;
    }

    std::ifstream ifs { argv[1] };
    if (!ifs)
    {
	    std::cerr << "Error: Unable to open file '" << argv[1] << "'\n";
	    return 2;
    }

    std::vector<std::string> text{
        std::istream_iterator<std::string>(ifs),
        std::istream_iterator<std::string>()
    };

    // 4
    std::map<string,string> parameters;
    int count = 0;

    std::transform(argv+2, argv+argc, std::inserter(parameters,std::begin(parameters)),
    [&count](std::string b){
        auto a = "#"+std::to_string(count++);
        return std::pair<string,string>(a,b);
    });

    // 5
    std::set<std::string> unique;
    std::copy_if(begin(text),end(text),std::inserter(unique,begin(unique)),
    [&parameters](std::string a)
    {   
        if(a.front() == '#')
        {
            auto p= parameters.find(a);
            if(p == end(parameters))
                return true;
            else
                return false;
        }
        return false;
    }
    );
    if(!unique.empty())
    {
        std::copy(begin(unique),end(unique),ostream_iterator<string>(cerr," "));
    }

    std::transform(begin(text),end(text),begin(text),
    [&parameters](std::string replace)
    {
        if(replace.front() == '#')
        {
            auto p = parameters.find(replace);
            return p->second;
        }
        else
        {
            return replace;
        }
    });
        std::copy(begin(text),end(text),ostream_iterator<string>(cout," "));

}