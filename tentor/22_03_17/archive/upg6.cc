#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
using namespace std::literals;

/* Example output for ./a.out < lorem_ipsum.txt (might differ slightly
 * since there might be multiple different choices for the three most
 * common words:

== Replaced text:
lorem REPLACED dolor sit amet consectetur adipiscing elit donec
efficitur massa eget auctor convallis aenean nibh eros efficitur
eget velit pharetra fringilla imperdiet dolor aliquam nisl justo
scelerisque ac ex REPLACED consectetur efficitur REPLACED REPLACED placerat
leo at tincidunt pretium risus magna ornare ante a ornare nunc elit
vel eros donec porttitor turpis lectus sit amet dignissim REPLACED
molestie ac cras semper sodales REPLACED ut gravida nisl pellentesque
REPLACED vestibulum lobortis enim quis velit gravida vel faucibus magna
ornare aliquam erat volutpat REPLACED at semper enim finibus
consequat sem REPLACED pharetra felis REPLACED diam vestibulum
hendrerit fusce porta urna lacus id molestie leo posuere
quis suspendisse potenti

*/

int main()
{
    std::vector<std::vector<std::string>> lines{};
    // Your code goes here
    std::string line;
    std::string ss_word;
    std::vector<std::string> tmp_vec{};
    std::map<std::string, int> my_map{};
    std::vector<std::pair<std::string, int>> common(3);

    while (std::getline(std::cin, line))
    {
        std::stringstream ss(line);
        for (std::string word; std::getline(ss, word, ' ');)
        {
            tmp_vec.push_back(word);
            ++my_map[word];
        }
        lines.push_back(tmp_vec);
        tmp_vec.clear();
    }
    std::partial_sort_copy(my_map.begin(), my_map.end(),
                           common.begin(), common.end(),
                           [](auto &a, auto &b)
                           {
                               return a.second > b.second;
                           });

    std::string s = "REPLACED";
    std::cout << "Common words: ";
    for (auto e : common)
    {
        std::cout << e.first << "-";
    }

    for (auto &line : lines)
    {
        for (auto e : common)
        {
            std::replace(std::begin(line), std::end(line), e.first, s);
        }
    }

    std::cout << "\n== Replaced text:\n";
    for (auto line : lines)
    {
        for (auto word : line)
        {
            std::cout << word << " ";
        }
        std::cout << "\n";
    }
}