#include <iostream>
#include <fstream>
#include <iomanip>

int main()
{
    std::ifstream f("text.txt");
    if (!f.is_open())
        std::cerr << "File not open";
    std::string s{};
    int longest_count{0};
    std::string longest_word;

    int shortest_count{100};
    std::string shortest_word;

    int mean_count{0};
    int numerator{0};

    while (f >> s)
    {
        if (s.length() < shortest_count)
        {
            shortest_count = s.length();
            shortest_word = s;
        }

        if (s.length() > longest_count)
        {
            longest_count = s.length();
            longest_word = s;
        }
        numerator += s.length();
        mean_count++;
    }
    std::cout << "There are " << mean_count << "word in the file.\n";
    std::cout << "The shortest word was " << '"' << shortest_word << '"' << " with " << shortest_count << " characters(s).\n";
    std::cout << "The longest word was " << '"' << longest_word << '"' << " with " << longest_word.length() << " character(s).\n";
    std::cout << "The avarage length was " << std::setprecision(2) << std::fixed << (double)numerator / mean_count << " characer(s).\n";
}