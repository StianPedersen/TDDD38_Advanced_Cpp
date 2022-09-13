#include <iostream>
#include <string>
int sum(double const *numbers,
        unsigned long long size)
{
    double result{};
    for (unsigned i{}; i < size; ++i) // converts i to unsigned long longi int
    {
        result += static_cast<int>(numbers[i]); // Converts to int then to double
    }
    return result;
}

int main()
{
    std::string message{};
    message = "Enter a number: ";

    double numbers[3];
    for (int i{0}; i < 3; ++i)
    {
        std::cout << message;
        if (!(std::cin >> numbers[i]))
        {
            return true;
        }
    }
    // Converts numbers to a pointer to const doubles and 3 to unsigned long long int
    std::cout << sum(numbers, 3) + 1.0 << std::endl;
}