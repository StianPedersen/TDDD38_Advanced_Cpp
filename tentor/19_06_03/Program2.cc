#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <cassert>

using namespace std;

class Printable
{
public:
    Printable() = default;
    virtual ~Printable() = default;
    Printable(Printable const &);            // Copy constructor
    Printable(Printable &&);                 // Move constructor
    Printable &operator=(Printable const &); // Copy assignment
    Printable &operator=(Printable &&);      // Move assignment
    virtual void print(ostream &os) const = 0;
};

class Serializable
{
public:
    Serializable() = default;
    virtual ~Serializable() = default;
    virtual string serialize() const = 0;
    virtual bool deserialize(string const &str) = 0;
};

class Message : public Printable
{
public:
    Message(string const &s) : Printable(), msg{s} {}
    void print(ostream &os) const override;

private:
    string msg;
};

class Integer : public Printable, public Serializable
{
public:
    Integer(int const &i) : Printable(), Serializable(), data{i} {};
    void print(ostream &os) const override;
    string serialize() const override;
    bool deserialize(string const &str) override;

private:
    int data;
};

// Message
void Message::print(ostream &os) const
{
    os << msg << "\n";
}

// Integer
void Integer::print(ostream &os) const
{
    os << data << "\n";
}
string Integer::serialize() const
{
    return to_string(data);
}
bool Integer::deserialize(string const &str)
{
    data = stoi(str);

    return true;
}

vector<string> serialize(vector<Printable *> const &v)
{
    vector<string> result{};
    for (Printable *obj : v)
    {
        if (auto p = dynamic_cast<Serializable *>(obj) /* Check if obj is a Serializable */)
        {
            result.push_back(p->serialize() /* Call serialize on obj */);
        }
    }
    return result;
}

void print(ostream &os, vector<Printable *> const &v)
{
    for (Printable *obj : v)
    {
        /* Call print on obj with os as parameter */
        obj->print(os);
        // os << endl;
    }
}

int main()
{
    vector<Printable *> v = {
        new Message{"Hello there"},
        new Integer{0},
        new Message{"This is a message"},
        new Integer{100053},
        new Integer{-5}};

    {
        vector<string> result{serialize(v)};
        assert((result == vector<string>{"0", "100053", "-5"}));
    }

    {
        ostringstream oss{};
        print(oss, v);
        // cout << oss.str() << endl;
        assert(oss.str() == "Hello there\n0\nThis is a message\n100053\n-5\n");
    }

    {
        Integer i{0};
        assert(i.deserialize("15"));
        assert(i.serialize() == "15");
    }
    for (auto e : v)
    {
        delete e;
    }
}