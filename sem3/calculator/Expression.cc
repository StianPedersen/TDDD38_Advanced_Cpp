#include "Expression.h"

#include <stdexcept>
#include <ostream>

/* Implement Expression here */
Expression::Expression(Node *root) : root{root} {};

Expression::Expression(Expression const &other) : root{other.root->clone()} {};

Expression::Expression(Expression &&other) : root{other.root}
{
    other.root = nullptr;
};

Expression::~Expression() { delete root; };

Expression &Expression::operator=(Expression const &rhs)
{
    Expression tmp{rhs};
    return *this = std::move(tmp);
}

Expression &Expression::operator=(Expression &&rhs)
{
    std::swap(root, rhs.root);
    return *this;
}

double Expression::evaluate() const
{
    return root->evaluate();
}

void Expression::print(std::ostream &os) const
{
    return root->print(os);
}

void Expression::print_tree(std::ostream &os) const
{
    return root->print_tree(os);
}

/* For part B */
void print(std::ostream &os)
{
    throw std::invalid_argument{"--print is unimplemented"};
}

/* For part C */
void Expression::expand()
{
    throw std::invalid_argument{"--expand is unimplemented"};
}
