
#include <iostream>
/*
  Implement the classes:
  - Node
  - Number
  - Operator
  - Addition
  - Subtraction
  - Multiplication
  - Division

  Node should have the following (pure virtual) members:
  - double evaluate()
    + Calculate the expression stored in 'this'

  - void print(std::ostream& os)
    + print the expression represented in 'this'

  - void print_tree(std::ostream& os, int depth)
    + print a textual representation of the expression tree

  - Node* clone()
    + return a a new instance of the expression stored in 'this'
 */

class Node
{
public:
  Node() = default;
  virtual ~Node() = default;

  virtual double evaluate() const = 0;
  virtual void print(std::ostream &os) const = 0;
  virtual void print_tree(std::ostream &os, int depth = 0) const = 0;
  virtual Node *clone() = 0;
};

class Number : public Node
{
public:
  Number() = default;
  Number(double d) : value{d} {};

  double evaluate() const override;
  void print(std::ostream &os) const override;
  void print_tree(std::ostream &os, int depth = 0) const override;
  Node *clone() override;

private:
  double value;
};

class Operator : public Node
{
public:
  Operator() = default;
  Operator(Node *lhs, Node *rhs) : left{lhs}, right{rhs} {};
  Operator(Operator const &) = delete;
  Operator(Operator &&) = delete;
  ~Operator() = default;
  Operator &operator=(Operator const &) = delete;
  Operator &operator=(Operator &&) = delete;

  void print_tree(std::ostream &os, int depth = 0) const override;

protected:
  Node *left;
  Node *right;
};

class Addition : public Operator
{
public:
  using Operator::Operator;
  double evaluate() const override;
  void print(std::ostream &os) const override;
  Node *clone() override;
};

class Subtraction : public Addition
{
public:
  using Addition::Addition;
  double evaluate() const override;
  void print(std::ostream &os) const override;
  Node *clone() override;
};

class Multiplication : public Operator
{
public:
  using Operator::Operator;

  double evaluate() const override;
  void print(std::ostream &os) const override;
  Node *clone() override;
};

class Division : public Multiplication
{
public:
  using Multiplication::Multiplication;

  double evaluate() const override;
  void print(std::ostream &os) const override;
  Node *clone() override;
};