#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <iterator>
#include <sstream>
#include <iomanip>

using namespace std;

/* Expected output:

Highscore      | Fastest       
Team D  : 37   | Team C
Team C  : 12   | Team B
Team B  : 5    | Team A

*/

string team_to_string(pair<string, int> const& team)
{
    ostringstream oss{};
    oss << left << setw(8) << team.first
        << ": " << setw(4) << team.second;
    return oss.str();
}

int main()
{
    vector<pair<string, int>> const results {
        {"Team C", 12},
        {"Team B", 5},
        {"Team A", 0},
        {"Team D", 37},
    };
    vector<pair<string, int>> highscore(3);

    // write your code here
}