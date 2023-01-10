#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>

/* Example output for ./a.out < lorem_ipsum.txt (might differ slightly
 * since there might be multiple different choices for the three most
 * common words:

{
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
}

*/

int main()
{
    std::vector<std::vector<std::string>> lines { };
    // Your code goes here
    // 2
    std::string line;
    std::string word;
    std::map<std::string,int> tracker;

    while(std::getline(std::cin,line))
    {
        std::istringstream ss{line};
        std::vector<std::string>tmp{};
        while(ss>>word)
        {
            tmp.push_back(word);
            ++tracker[word];
        }
        lines.push_back(tmp);
    }
    
    std::vector<std::pair<std::string,int>> tracker_intermediate{tracker.begin(),tracker.end()};
    std::vector<std::pair<std::string,int>> common(3);

    std::partial_sort_copy(tracker_intermediate.begin(),tracker_intermediate.end(),common.begin(),common.end(),
    [](std::pair<std::string,int>a,std::pair<std::string,int>b)
    {
        return a.second>b.second;
    });

    for(auto& line : lines)
        {
            for(auto& word : line)
            {
                for(auto e : common)
                {
                    if(e.first== word)
                    {
                        word = "REPLACED";
                    }
                }
                std::cout<<word<<" ";
            }
            std::cout<<"\n";
        }
    

}