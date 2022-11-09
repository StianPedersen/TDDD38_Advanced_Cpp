#include <vector>
#include <string>
#include <iostream>
using namespace std;
class Book
{
public:
    Book(string const &s) : title{s} {}
    virtual ~Book() = default;
    virtual bool for_children() const = 0;

    string const title;
};

class Non_Fiction : public Book
{
public:
    Non_Fiction(string const &s) : Book(s) {}
    bool for_children() const override;
};

class Fiction : public Book
{
public:
    Fiction(string const &s, bool b = false) : Book(s), is_children_book{b} {}
    bool for_children() const override;

private:
    bool is_children_book;
};

class Crime_Fiction : public Book
{
public:
    Crime_Fiction(string const &s, bool b = false) : Book(s + " (best seller)"), is_children_book{b} {}
    bool for_children() const override;

private:
    bool is_children_book;
};

class Reader
{
public:
    Reader(string const &s) : name{s} {}
    virtual ~Reader() = default;
    virtual bool likes(Book *b) const;
    void read(Book *b) const;

private:
    string name;
};

class Academic : public Reader
{
public:
    Academic(string const &s) : Reader(s) {}
    bool likes(Book *b) const override;
};

class Child : public Reader
{
public:
    Child(string const &s) : Reader(s) {}
    bool likes(Book *b) const;
};

class Detective : public Reader
{
public:
    Detective(string const &s) : Reader(s) {}
    bool likes(Book *b) const override;
};

// Non_fiction
bool Non_Fiction::for_children() const
{
    return false;
};

// Fiction
bool Fiction::for_children() const
{
    return is_children_book;
}

// Crime_Fiction
bool Crime_Fiction::for_children() const
{
    return is_children_book;
}

// Reader
bool Reader::likes(Book *b) const
{
    return true;
};
void Reader::read(Book *b) const
{
    if (likes(b))
        cout << name << " recomends reading " << b->title;
    else
        cout << name << " does not recomends reading " << b->title;
    cout << "\n";
}

// Academic
bool Academic::likes(Book *b) const
{
    auto p = dynamic_cast<Non_Fiction *>(b);
    if (p)
        return true;
    else
        return false;
}

// Child
bool Child::likes(Book *b) const
{
    if (b->for_children())
        return true;
    else
        return false;
}

// Detective
bool Detective::likes(Book *b) const
{
    if (typeid(*b) == typeid(Fiction))
        return true;
    else
        return false;
}
/* if implemented correctly this program
   should give the following output:

Rhea Deer recommends reading "The Lord of the Rings".
Rhea Deer recommends reading "Winnie the Pooh".
Rhea Deer recommends reading "The Da Vinci Code (best seller)".
Rhea Deer recommends reading "Nancy Drew: The Secret of the Old Clock (best seller)".
Rhea Deer recommends reading "Course Literature".
Professor McProfessorsen does not recommend reading "The Lord of the Rings".
Professor McProfessorsen does not recommend reading "Winnie the Pooh".
Professor McProfessorsen does not recommend reading "The Da Vinci Code (best seller)".
Professor McProfessorsen does not recommend reading "Nancy Drew: The Secret of the Old Clock (best seller)".
Professor McProfessorsen recommends reading "Course Literature".
Christopher Robin does not recommend reading "The Lord of the Rings".
Christopher Robin recommends reading "Winnie the Pooh".
Christopher Robin does not recommend reading "The Da Vinci Code (best seller)".
Christopher Robin recommends reading "Nancy Drew: The Secret of the Old Clock (best seller)".
Christopher Robin does not recommend reading "Course Literature".
Sherlock Holmes recommends reading "The Lord of the Rings".
Sherlock Holmes recommends reading "Winnie the Pooh".
Sherlock Holmes does not recommend reading "The Da Vinci Code (best seller)".
Sherlock Holmes does not recommend reading "Nancy Drew: The Secret of the Old Clock (best seller)".
Sherlock Holmes does not recommend reading "Course Literature".
*/
int main()
{
    vector<Reader *> readers{
        new Reader{"Rhea Deer"},
        new Academic{"Professor McProfessorsen"},
        new Child{"Christopher Robin"},
        new Detective{"Sherlock Holmes"}};

    vector<Book *> books{
        new Fiction{"The Lord of the Rings"}, //
        new Fiction{"Winnie the Pooh", true}, //
        new Crime_Fiction{"The Da Vinci Code"},
        new Crime_Fiction{"Nancy Drew: The Secret of the Old Clock", true},
        new Non_Fiction{"Course Literature"}};

    for (auto reader : readers)
    {
        for (auto book : books)
        {
            // reader.read(book);
            // or
            reader->read(book);
        }
    }
}