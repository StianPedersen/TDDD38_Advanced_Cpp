#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>
#include <ranges>

using namespace std;
int main(){

    std::vector<std::string> my_vec{"ja","nej","ja","nej","kanske","ja",};
    std::vector<std::string> jmf_vec = my_vec;

    // Read from cin
    // std::copy(std::istream_iterator<std::string>(std::cin), 
    // std::istream_iterator<std::string>(),
    // std::back_inserter(my_vec));

    // Remove duplicates
    sort(begin(my_vec),end(my_vec));
    my_vec.erase(std::unique(begin(my_vec),end(my_vec)),end(my_vec));

    //Count
    std::vector<int> counter_vec;
    transform(begin(my_vec),end(my_vec),ostream_iterator<string>(cout,"\n"),
    [&jmf_vec](string s){
        int n = count(begin(jmf_vec),end(jmf_vec),s);
        return s +": "+ to_string(n);
    });
} 