#include <iostream>
#include <vector>
#include <initializer_list>


class Expression;
void pretty_print(std::ostream&os, Expression* e);

class Expression
{
    public:
        virtual ~Expression() = default;
        virtual bool evaluate()  = 0;
        virtual void print(std::ostream& os) const = 0;

};

class Literal : public Expression
{
    public:
        Literal(bool b) : value{b} {} 
        bool evaluate()  override;
        void print(std::ostream& os) const override;
    private:
        bool value; 
};

class Negation : public Expression // NB Minneshantering
{
    public:
        Negation(Expression* l) : expression{l} {}
        ~Negation()
        { 
            delete expression;
        }
        bool evaluate() override;
        void print(std::ostream& os) const override;
    private:
        Expression* expression;
};

class Compound : public Expression 
{
    public:
        Compound(std::initializer_list<Expression*>const& l) :
         expressions{l.begin(),l.end()}{
            
        }
        ~Compound(){ 
            for (Expression* expression : expressions)
                delete expression;
            }
        virtual std::string glyph() const = 0;
        void print(std::ostream& os) const;
    protected:
        std::vector<Expression*> expressions; // NB

};

class And : public Compound
{
    public:
        using Compound::Compound;
        std::string glyph() const;
        bool evaluate() override;
};

class Or : public Compound
{
    public:
    using Compound::Compound;
    std::string glyph() const;
    bool evaluate() override;
};


// Literal
bool Literal::evaluate() {
    return value;
}
void Literal::print(std::ostream& os) const{
    os<<std::boolalpha<<value;
}
 
// Negation
bool Negation::evaluate() {
    return !expression->evaluate();   
}

void Negation::print(std::ostream& os) const{
    os<<"!";
    pretty_print(os, expression);
}

// Compund
void Compound::print(std::ostream& os) const{
    
    for(int i{0} ; i < expressions.size();i++)
    {
        if(i != 0 && i != expressions.size())
            os<<glyph();
        pretty_print(os,expressions[i]);

    }

}

// And
std::string And::glyph() const
{
    return " && ";
}
bool And::evaluate(){
    for(auto e : expressions)
    {
        if(!e->evaluate())
        {
            return false;
        }
    }
    return true;
}

// Or
std::string Or::glyph() const
{
    return " || ";
}
bool Or::evaluate(){
    for(auto e : expressions)
    {
        if(e->evaluate())
        {
            return true;
        }
    }
    return false;
}

void pretty_print(std::ostream&os, Expression* e)
{

    if(auto p = dynamic_cast<Compound*>(e))
    {

        os<<"(";
        e->print(os);
        os<<")";
    }
    else
    {
        e->print(os);
    }
}




/* Expected output:


!true = false
!(true && false) = true
(true || false) && false && (false || !false) = false

 */
int main()
{

    // Think carefully about the types here. You might have to modify
    // the testcases slightly to make it work.

    Expression* expr1 { new Negation{new Literal { true }} };

    expr1->print(std::cout);
    std::cout << " = " << expr1->evaluate() << std::endl;
    
    Expression * expr2 {
	new Negation {
	    new And { new Literal { true },new Literal { false } }
	}
    };

    expr2->print(std::cout);
    std::cout << " = " << expr2->evaluate() << std::endl;
    
    Expression * expr3 {new
	And {
	    new Or {new Literal { true }, new Literal { false } },
	    new Literal { false },
	    new Or { new Literal { false }, new Negation { new Literal{false} } }
	}
    };

    expr3->print(std::cout);
    std::cout << " = " << expr3->evaluate() << std::endl;
    
}