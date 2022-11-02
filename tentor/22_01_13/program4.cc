#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
// Element
class Element
{
public:
    Element(std::string const &n) : name{n} {};
    virtual ~Element() = default;
    virtual void print(std::ostream &os) = 0;

protected:
    std::string const name;
};

// Label
class Label : public Element
{
public:
    Label(std::string const &n, std::string const &t) : Element(n), text{t} {}
    void print(std::ostream &os) override;

private:
    std::string const text;
};

// Collection
class Collection : public Element
{
public:
    Collection(std::string const &n) : Element(n), column_width{0}, items{} {};

    void insert(int &i);

protected:
    virtual void print_item(std::ostream &os, int const &i);

    int column_width{0};
    std::vector<int> items;
};

// Grid
template <int width>
class Grid : public Collection
{
public:
    Grid<width>(std::string const &n) : Collection(n){};
    void print(std::ostream &os) override;

private:
};

class List : public Grid<1>
{
public:
    List(std::string const &n) : Grid(n){};
    void print_item(std::ostream &os, int const &i) override;

private:
};

// Label functions
void Label::print(std::ostream &os)
{
    os << Element::name << ": " << '"' << text << '"';
};

// Collection functions
void Collection::print_item(std::ostream &os, int const &i)
{
    os << std::setw(column_width) << i;
};
void Collection::insert(int &i)
{
    if (std::to_string(i).size() > column_width)
        column_width = std::to_string(i).size();

    items.push_back(i);
};

// Grid functions
template <int width>
void Grid<width>::print(std::ostream &os)
{
    // Print header for the grid
    os << name << ":\n";
    for (unsigned int i{0}; i < items.size(); ++i)
    {
        // print each item
        print_item(os, items[i]);

        // If we have filled one row (or if this is the last item),
        // print a newline character
        if ((i + 1) % width == 0 || i + 1 == items.size())
        {
            os << '\n';
        }
        else
        {
            os << ' ';
        }
    }
}

// List functions
void List::print_item(std::ostream &os, int const &i)
{
    os << "[";
    Collection::print_item(os, i);
    os << "]";
};

/* Expected output:

My Text: "This is a text"

My Grid (3):
  1  12 123
456   4  45
 78 789   7

My List:
 - [  1]
 - [ 12]
 - [123]
 - [456]
 - [  4]
 - [ 45]
 - [ 78]
 - [789]
 - [  7]

My Grid (2):
  1  12
123 456
  4  45
 78 789
  7

*/

int main()
{
    std::vector<Element *> elements = {
        new Label{"My Label", "This is a text"},
        new Grid<3>{"My Grid (3)"},
        new List{"My List"},
        new Grid<2>{"My Grid (2)"}};
    std::vector<int> data{1, 12, 123, 456, 4, 45, 78, 789, 7};

    // Populate each collection with 'data'
    for (int n : data)
    {
        for (auto e : elements)
        {
            // If e is of type 'Collection':
            // call insert(n) on it
            if (auto p = dynamic_cast<Collection *>(e))
            {
                p->insert(n);
            };
        }
    }

    // Print each element
    for (auto e : elements)
    {
        // call print(std::cout) on e
        e->print(std::cout);
        std::cout << std::endl;
    }
}