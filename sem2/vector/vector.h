#pragma once
#include <ostream>

class Vector
{
public:
    Vector() : num_1{}, num_2{} {};
    Vector(double const &one, double const &two) : num_1{one}, num_2{two} {}

    bool operator==(Vector const &rhs);
    bool operator!=(Vector const &rhs);

    Vector &operator+=(Vector const &rhs); // compund assignment??
    Vector &operator*=(double const &rhs); // compund assignment??
    Vector &operator-=(Vector const &rhs); // compund assignment??
    Vector &operator/=(double const &rhs);

    Vector operator-();

    // Streams
    friend std::ostream &operator<<(std::ostream &os, Vector const &rhs);
    friend std::istream &operator>>(std::istream &is, Vector &rhs);

    // Functions
    double length() const;

private:
    double num_1;
    double num_2;
};

Vector operator+(Vector const &lhs, Vector const &rhs);
Vector operator-(Vector const &lhs, Vector const &rhs);

Vector operator*(Vector const &rhs, double d);
Vector operator*(double d, Vector const &rhs);

Vector operator/(Vector const &rhs, double d);
