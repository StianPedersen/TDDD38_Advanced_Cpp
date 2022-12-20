#include <iostream>
#include <cmath> // for std::sqrt
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " FILE" << std::endl;
        return 1;
    }

    // filename is stored in argv[1]

    // implement the steps here
    // Step 1
    std::fstream f{argv[1]};

    // Step 2
    if (!f.is_open())
    {
        std::cerr << "No file found";
        return 1;
    }

    // Step 3
    double dx;
    f >> dx;
    std::cout << dx << std::endl;

    // Step 4
    std::vector<double> values{
        std::istream_iterator<double>(f),
        std::istream_iterator<double>()};

    // Step 5
    std::vector<double> lengths;
    std::transform(std::begin(values) + 1, std::end(values), std::begin(values),
                   std::back_inserter(lengths),
                   [](double one, double two)
                   {
                       return two - one;
                   });

    // Step 6
    std::transform(std::begin(lengths), std::end(lengths),
                   std::begin(lengths),
                   [&dx](double dy)
                   {
                       return std::sqrt((dx * dx) + (dy * dy));
                   });

    // for (auto e : lengths)
    //     std::cout << e << "-";

    double res = std::accumulate(std::begin(lengths), std::end(lengths), 0.0);
    std::cout << res;
}