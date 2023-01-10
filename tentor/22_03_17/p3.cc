#include <iostream>
#include <cmath> // for std::sqrt
#include <iterator>
#include <vector>
#include <fstream>
#include <numeric>
#include <algorithm>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
	std::cerr << "Usage: " << argv[0] << " FILE" << std::endl;
	return 1;
    }

    // filename is stored in argv[1]

    // implement the steps here
    // 1
    std::ifstream ifs{argv[1]};
    
    //2
    if(!ifs.is_open())
        {std::cerr<<"File not open";
        return 0;}
    float dx{};
    
    // 3
    ifs>>dx;
    
    // 4
    std::vector<double> values {
        std::istream_iterator<float>(ifs),
        std::istream_iterator<float>()
    };
    
    // 5
    std::vector<double> lengths{};
    std::adjacent_difference(values.begin(),values.end(), std::back_inserter(lengths));

    // 6
    std::transform(lengths.begin(),lengths.end(),lengths.begin(),
    [dx](float dy)
    {

        return std::sqrt(dx*dx + dy*dy);
    });
    
    // 6 
    std::cout << std::accumulate(std::next(lengths.begin()),lengths.end(),0.0)<<std::endl;
}