#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class Element
{
public:
    Element(string const &s) : name{s} {};
    virtual ~Element() = default;
    virtual void print(ostream &os) const = 0;

protected:
    string name;
};

class Label : public Element
{
public:
    Label(string const &n, string const &t) : Element(n), text(t) {}
    void print(ostream &os) const override;

private:
    string text;
};

class Collection : public Element
{
public:
    Collection(string const &n) : Element(n), items{}, column_width{0} {};
    virtual ~Collection() = default;
    void insert(int const i);

protected:
    virtual void print_item(ostream &os, int const &w) const;
    vector<int> items{};

private:
    int column_width;
};

template <int width>
class Grid : public Collection
{
public:
    Grid(string const &n) : Collection(n){};
    void print(std::ostream &os) const override;

private:
};

class List : public Grid<1>
{
public:
    List(string const &n) : Grid(n){};
    void print_item(ostream &os, int const &w) const override;
};

// Possible implementation for Grid::print
// Will support printing of a grid even if the number of items is not
// a multiple of the grid width.
template <int width>
void Grid<width>::print(std::ostream &os) const
{
    // Print header for the grid
    os << name << ":\n";
    for (size_t i{0}; i < items.size(); ++i)
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

void Label::print(ostream &os) const
{
    os << name << ": " << '"' << text << '"';
}

void Collection::print_item(ostream &os, int const &w) const
{
    os << setw(column_width) << w;
}

void Collection::insert(int const i)
{
    items.push_back(i);
    string i_s = to_string(i);
    string c_s = to_string(column_width);
    if (i_s.size() > column_width)
        column_width = i_s.size();
}

void List::print_item(ostream &os, int const &w) const
{
    os << "- [";
    Collection::print_item(os, w);
    os << "]";
}
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
                p->insert(n);
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