#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Book{
    public:
        Book(string const& t) : title{t}{}

        Book(Book const&b) = delete; // copy constructor
        Book& operator=(Book const& b) = delete // Copy assignment operator.

        virtual ~Book() = default;
        virtual bool for_children() const = 0;

        string title;
};

class Non_fiction : public Book{
    public:
        Non_fiction(string const& t) : Book(t){}
        bool for_children() const override;
    private:
};

class Crime_Fiction : public Book{
    public:
        Crime_Fiction(string const& t, bool b = false) : 
                            Book(t+" (best seller)"), b{b} {}
        bool for_children() const override;
    private:
        bool b;
};


class Fiction : public Book{
    public:
        Fiction(string const& t, bool b = false) : Book(t), b{b} {}
        bool for_children() const override;
    private:
        bool b;
};

class Reader
{
    public:
        Reader(string const& n) : name{n}{}
        virtual bool likes(Book* b) const;
        virtual void read(Book* b) const;
    private:
        string name;
};

class Academic : public Reader
{
    public:
        Academic(string const& n) : Reader(n){}
        bool likes(Book* b) const override;
};

class Child : public Reader{
    public:
        Child(string const& n) : Reader(n){}
        bool likes(Book* b) const override;
};

class Detective : public Reader
{
    public:
        Detective(string const& n) : Reader(n){}
        bool likes(Book* b) const override;

};


bool Non_fiction::for_children() const {
    return false;
}
bool Fiction::for_children() const {
    return b;
}
bool Crime_Fiction::for_children() const {
    return b;
}

// Reader
bool Reader::likes(Book* b) const
{
    return true;
}
void Reader::read(Book* b) const
{
    if(likes(b))
        cout<<name<<" recommends reading "<<b->title<<endl;
    else
        cout<<name<<" does not recommend reading "<<b->title<<endl;
}
// Academic
bool Academic::likes(Book* b) const
{
    if(auto p = dynamic_cast<Non_fiction*>(b))
        return true;
    else
        return false;
}
// Child
bool Child::likes(Book* b) const
{
    if(b->for_children())
        return true;
    else
        return false;
}   

// Detective
bool Detective::likes(Book* b) const
{
    if(typeid(*b) == typeid(Fiction))
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
  vector< Reader *> readers {
    new Reader{"Rhea Deer"},
    new Academic{"Professor McProfessorsen"},
    new Child{"Christopher Robin"},
    new Detective{"Sherlock Holmes"}
  };

  vector<Book *> books {
    new Fiction{"The Lord of the Rings"},
    new Fiction{"Winnie the Pooh", true},
    new Crime_Fiction{"The Da Vinci Code"},
    new Crime_Fiction{"Nancy Drew: The Secret of the Old Clock", true},
    new Non_fiction{"Course Literature"}
  };

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