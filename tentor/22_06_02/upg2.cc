#include <iostream>
#include <stdexcept>
#include <sstream>

class Variable_Base
{
public:
    virtual ~Variable_Base() = default;
    virtual void print(std::ostream &os) = 0;
    virtual Variable_Base *add(Variable_Base *rhs) = 0;

private:
};

class Number : public Variable_Base
{
public:
    Number(double d) : value{d} {};
    void print(std::ostream &os) override
    {
        os << value;
    }
    Variable_Base *add(Variable_Base *rhs) override
    {
        if (auto p = dynamic_cast<Number *>(rhs))
        {
            return new Number{value + p->value};
        }
        else
        {
            throw std::invalid_argument("what");
        }
    }

private:
    double value{};
};

class String : public Variable_Base
{
public:
    String(std::string s) : value{s} {};
    void print(std::ostream &os) override
    {
        os << value;
    }

    Variable_Base *add(Variable_Base *rhs) override
    {
        if (auto p = dynamic_cast<Number *>(rhs))
        {
            std::ostringstream os_new;
            os_new << value;
            p->print(os_new);
            return new String{os_new.str()};
        }
        else if (auto p = dynamic_cast<String *>(rhs))
        {
            return new String{value + p->value};
        }
        else
        {
            throw std::invalid_argument("es ist invalid");
        }
    }

private:
    std::string value;
};

/* Expected output:

hello5.3
helloworld
Unknown operator
6.5

 */
int main()
{
    // Variable var1{"hello"};
    // Variable var2{5.3};
    // Variable var3{"world"};
    // Variable var4{1.2};

    // std::cout << var1 + var2 << std::endl;
    // std::cout << var1 + var3 << std::endl;

    // try
    // {
    //     std::cout << var2 + var3 << std::endl;
    // }
    // catch (std::exception &e)
    // {
    //     std::cerr << e.what() << std::endl;
    // }

    // std::cout << var2 + var4 << std::endl;
}