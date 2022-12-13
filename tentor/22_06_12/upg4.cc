#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <map>
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
    
    // Step 1
    std::vector<std::string> text{};
    std::copy(std::istream_iterator<std::string>(ifs),std::istream_iterator<std::string>(),
    std::back_inserter(text));

    // Step 2
    std::map<string,string> parameters;
    int val{0};
    std::transform(argv+2, argv+argc,inserter(parameters,end(parameters)),
    [&val](string const& arg){
        return make_pair("#"+to_string(val++), arg);
    }
    );

    // Step 3
    set<string> no_association;
    copy_if(begin(text),end(text),inserter(no_association,end(no_association)),
    [&parameters](std::string s){
        if(s.front() != '#')
            return false;
        auto search = parameters.find(s);
        if(search != end(parameters))
        {
            return false;
        }
        else
            return true;
       
    }
    );
    
    if(!no_association.empty())
    {
        copy(begin(no_association),end(no_association),
        ostream_iterator<string>(cerr," "));
        return 1;
    }

    // Step 5
    std::transform(begin(text),end(text),begin(text),
    [&parameters](std::string const& s)
    {
        if(s.front() != '#')
            return s;
        auto search = parameters.find(s);
        return search->second;
    }
    );
    
    copy(begin(text),end(text),ostream_iterator<string>(cout," "));
return 0;
}