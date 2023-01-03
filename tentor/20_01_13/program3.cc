#include <cmath>
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>
using namespace std;

int main()
{
    double const length {10.0};
    vector<double> road {};

    std::copy(istream_iterator<double>(cin),istream_iterator<double>(),back_inserter(road));

    vector<double> result(road);

    std::rotate(road.rbegin(), road.rbegin() + 1, road.rend());

    transform(begin(result),end(result),begin(road),begin(result),
    [&length](double b, double a)
    {
        return  sqrt((a - b) * (a - b) + length * length);
    });

    std::copy(begin(result),end(result),ostream_iterator<double>(cout,"m\n"));

    double total  = accumulate(begin(result),end(result),0.0);

    cout << "Total distance: " << total << " m" << endl;
}