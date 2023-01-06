#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <algorithm>
#include <iterator>
// TODO: Figure out what containers to use

std::map<std::string,std::set<std::string>> read_table(std::istream& is)
{
    std::map<std::string,std::set<std::string>> result { };
    
    std::string line;
    while (std::getline(is, line))
    {
	std::istringstream iss { line };
	std::string entry { };
	std::string tag   { };

    std::set<std::string> tags { };
	
	iss >> entry;
	while (iss >> tag)
	    tags.insert(tag); 
    result[entry] = tags;
	/* store an association between 'entry' and 'tags' into 'result' */
    }

    return result;
}

/* Expected output:

$ ./a.out names.txt Male Female
Alex
Austin
Avery
Blake
Brooklyn
Charlie
Drew
Jordan
Kennedy
Parker
Taylor

$ ./a.out names.txt Female
Abigail
Alex
Amelia
Austin
Ava
Avery
Blake
Brooklyn
Camila
Charlie
Charlotte
Drew
Eleanor
Elizabeth
Ella
Emma
Evelyn
Gianna
Harper
Isabella
Jordan
Kennedy
Luna
Mia
Olivia
Parker
Scarlett
Sofia
Sophia
Taylor

 */

int main(int argc, char* argv[])
{
    if (argc <= 2)
    {
	std::cerr << "Usage: " << argv[0] << " FILE [TAGS...]" << std::endl;
	return 1;
    }
    
    std::ifstream ifs { argv[1] };
    std::set<std::string> tags { &argv[2], &argv[argc] };

    auto table = read_table(ifs);

    /* implement the program here */
    // 1 
    std::vector<std::pair<std::string, std::set<std::string>>> filt
    {std::begin(table),std::end(table)};

    auto it = std::remove_if(filt.begin(),filt.end(),
    [&tags](auto p)
    {
        return !std::includes(p.second.begin(),p.second.end(),tags.begin(),tags.end());
    });
    filt.erase(it,filt.end());

    std::vector<std::string> entries;
    std::transform(filt.begin(),filt.end(),std::back_inserter(entries),
    [](auto p)
    {
        return p.first;
    }
    );
    std::sort(begin(entries),end(entries));
    std::copy(begin(entries),end(entries),std::ostream_iterator<std::string>(std::cout,"\n"));

}