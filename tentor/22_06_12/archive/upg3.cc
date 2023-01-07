#include <iostream>
#include <stdexcept>
#include <sstream>

class Variable_base
{
    public:
        virtual ~Variable_base() = default;
        virtual void print(std::ostream& os) const = 0;
        virtual Variable_base* add(Variable_base* rhs) const
        {
            throw std::logic_error("Not a type");
        }
    private:
};

class Number : public Variable_base
{
    public:
        Number(double const& d) : value{d}{}
        void print(std::ostream& os) const override;
        Variable_base* add(Variable_base* rhs) const override;
        
    private:
        double value;
};

class String : public Variable_base
{
    public:
        String(std::string const& s) : value{s}{};
        void print(std::ostream&os) const override;
        Variable_base* add(Variable_base* rhs) const override;
    private:
        std::string value;
};


// Functions
void Number::print(std::ostream& os) const 
{
    os<<value;
}

Variable_base* Number::add(Variable_base* rhs) const
{
    if(auto p = dynamic_cast<Number*>(rhs))
        return new Number((p->value + this->value));
    else
        throw std::logic_error("Not an number");
}

void String::print(std::ostream& os) const
{
    os<<value;
}

Variable_base* String::add(Variable_base* rhs) const
{
    if(auto p = dynamic_cast<Number*>(rhs))
    {
        std::ostringstream oss {};
        p->print(oss);
        return new String((value + oss.str()));
    }
    else if(auto p = dynamic_cast<String*>(rhs))
    {
        return new String(value+p->value);
    }
    else
    {
        throw std::logic_error("Not a number or a string");
    }
}

/* Expected output:

hello5.3
helloworld
Unknown operator
6.5

 */
int main()
{
    // Variable var1 { "hello" };
    // Variable var2 { 5.3 };
    // Variable var3 { "world" };
    // Variable var4 { 1.2 };
    
    // std::cout << var1 + var2 << std::endl;
    // std::cout << var1 + var3 << std::endl;

    // try
    // {
	// std::cout << var2 + var3 << std::endl;
    // } catch (std::exception& e)
    // {
	// std::cerr << e.what() << std::endl;
    // }
    
    // std::cout << var2 + var4 << std::endl;
    
}