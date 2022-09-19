#include "vector.h"
#include <cmath>
#include <iostream>

// implement all the functions declared in Vector.h here

bool Vector::operator==(Vector const &rhs)
{
    if (num_1 == rhs.num_1 && num_2 == rhs.num_2)
        return true;
    return false;
};

bool Vector::operator!=(Vector const &rhs)
{
    if (num_1 == rhs.num_1 && num_2 == rhs.num_2)
        return false;
    return true;
}

Vector &Vector::operator+=(Vector const &rhs)
{
    num_1 += rhs.num_1;
    num_2 += rhs.num_2;
    return *this;
}

Vector operator+(Vector const &lhs, Vector const &rhs)
{
    return Vector{lhs} += rhs;
};

Vector &Vector::operator*=(double const &rhs)
{
    num_1 *= rhs;
    num_2 *= rhs;
    return *this;
}

Vector operator*(Vector const &rhs, double d)
{
    return Vector{rhs} *= d;
}

Vector operator*(double d, Vector const &rhs)
{
    return Vector{rhs} *= d;
}

Vector Vector::operator-()
{
    Vector tmp{};
    tmp.num_1 = -num_1;
    tmp.num_2 = -num_2;
    return tmp;
}

Vector &Vector::operator-=(Vector const &rhs)
{
    num_1 -= rhs.num_1;
    num_2 -= rhs.num_2;
    return *this;
}

Vector operator-(Vector const &lhs, Vector const &rhs)
{
    return Vector{lhs} -= rhs;
}

Vector &Vector::operator/=(double const &rhs)
{
    num_1 /= rhs;
    num_2 /= rhs;
    return *this;
}

Vector operator/(Vector const &lhs, double d)
{
    return Vector{lhs} /= d;
}

double Vector::length() const
{
    return sqrt(pow(num_1, 2) + pow(num_2, 2));
}

std::ostream &operator<<(std::ostream &oss, Vector const &rhs)
{
    return oss << '(' << rhs.num_1 << ", " << rhs.num_2 << ')';
}

std::istream &operator>>(std::istream &is, Vector &rhs)
{
    Vector tmp{};
    is >> std::ws;
    if (is.peek() == '(')
    {
        is.ignore(1);
        is >> std::ws >> tmp.num_1 >> std::ws;
        if (is.peek() == ',')
        {
            is.ignore(1);
            is >> std::ws >> tmp.num_2 >> std::ws;
            if (is.peek() == ')')
            {
                is.ignore(1);
                rhs = tmp;
                std::cout << rhs.num_1 << " " << rhs.num_2 << std::endl;
                return is;
            }
        }
    }
    is.setstate(std::ios::failbit);
    return is;
}