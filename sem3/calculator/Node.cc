#include "Node.h"
#include <iomanip>
// Number
double Number::evaluate() const
{
  return value;
};

void Number::print(std::ostream &os) const
{
  os << evaluate();
};

void Number::print_tree(std::ostream &os, int depth) const
{
  os << std::setw(depth) << "";
  print(os);
  os << std::endl;
};

Node *Number::clone()
{
  return new Number{value};
};

// Operator

void Operator::print_tree(std::ostream &os, int depth) const
{
  left->print_tree(os, depth + 3);
  os << std::setw(depth) << ""
     << " / "
     << "\n";
  // os << std::setw(depth) << this->get_operator() << "\n";
  if (typeid(*this) == typeid(Multiplication))
  {
    os << std::setw(depth) << ""
       << "*"
       << "\n";
  }
  else if (typeid(*this) == typeid(Subtraction))
  {
    os << std::setw(depth) << ""
       << "-"
       << "\n";
  }
  else if (typeid(*this) == typeid(Addition))
  {
    os << std::setw(depth) << ""
       << "+"
       << "\n";
  }
  else if (typeid(*this) == typeid(Division))
  {
    os << std::setw(depth) << ""
       << "/"
       << "\n";
  }
  else
  {
    os << std::setw(depth) << ""
       << "ERROR"
       << "\n";
  }

  os << std::setw(depth) << ""
     << " \\ "
     << "\n";
  right->print_tree(os, depth + 3);
};

// Addition
double Addition::evaluate() const
{
  return left->evaluate() + right->evaluate();
};

void Addition::print(std::ostream &os) const
{
  left->print(os);
  os << "+";
  right->print(os);
};

Node *Addition::clone()
{
  return new Addition{left->clone(), right->clone()};
};

// Substraction
double Subtraction::evaluate() const
{
  return left->evaluate() - right->evaluate();
};

void Subtraction::print(std::ostream &os) const
{
  left->print(os);
  os << "-";
  right->print(os);
};

Node *Subtraction::clone()
{
  return new Subtraction{left->clone(), right->clone()};
};

// Multiplication
double Multiplication::evaluate() const
{
  return left->evaluate() * right->evaluate();
};

void Multiplication::print(std::ostream &os) const
{
  left->print(os);
  os << "*";
  right->print(os);
};

Node *Multiplication::clone()
{
  return new Multiplication{left->clone(), right->clone()};
};

// Division
double Division::evaluate() const
{
  return left->evaluate() / right->evaluate();
};

void Division::print(std::ostream &os) const
{
  left->print(os);
  os << "/";
  right->print(os);
};

Node *Division::clone()
{
  return new Division{left->clone(), right->clone()};
};
