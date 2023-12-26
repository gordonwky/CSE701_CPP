#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
using namespace std;

class bigint
{
public:
    bigint();         // default constructor
    bigint(int64_t);  // constructor with int64_t
    bigint(string &); // constructor with string

    bigint &operator-=(const bigint &);
    bigint &operator+=(const bigint &);
    bigint &operator*=(const bigint &);
    bigint &operator=(const bigint &);

    void change_sign(bool); // change sign function
    friend ostream &operator<<(ostream &, const bigint &);
    bool get_sign() const;              // getter function
    vector<uint8_t> get_vector() const; // getter function

private:
    // vector that store the number
    vector<uint8_t> big_int_vec;
    // store the sign
    bool sign;
};
// Overloaded binary operator << to easily print out a matrix to a stream.
ostream &operator<<(ostream &, const bigint &);

// Overloaded binary operator == to compare two bigint.
bool operator==(const bigint &, const bigint &);

// Overloaded binary operator != to compare two bigint.
bool operator!=(const bigint &, const bigint &);

bool operator>(const bigint &, const bigint &);

bool operator>=(const bigint &, const bigint &);

// Overloaded binary operator + to add two bigint.
bigint operator+(bigint, const bigint &);

// Overloaded unary operator - to take the negative of a bigint.
bigint operator-(const bigint);

// Overloaded binary operator - to subtract two bigint.
bigint operator-(bigint, const bigint &);

// Overloaded binary operator * to multiply two bigint.
bigint operator*(bigint, const bigint &);

// default constructor for zero

bigint::bigint()
{
    sign = true;
    big_int_vec.push_back(0);
};

// default constructor for 64 bit int
bigint::bigint(int64_t a)
{
    if (a == 0)
    {
        sign = true;
        big_int_vec.push_back(0);
    }
    if (a > 0)
    {
        sign = true;
    }
    if (a < 0)
    {
        sign = false;
    }
    a = abs(a);
    while (a != 0)
    {
        big_int_vec.push_back(static_cast<uint8_t>(a % 10));
        a /= 10;
    }
};

// constructor for string

bigint::bigint(string &a)
{
    sign = true;
    for (string::iterator i = a.end() - 1; i != a.begin() - 1; i--)
    {
        char num = *i;
        if (num == '0')
        {
            big_int_vec.push_back(0);
        }
        else if (num == '1')
        {
            big_int_vec.push_back(1);
        }
        else if (num == '2')
        {
            big_int_vec.push_back(2);
        }
        else if (num == '3')
        {
            big_int_vec.push_back(3);
        }
        else if (num == '4')
        {
            big_int_vec.push_back(4);
        }
        else if (num == '5')
        {
            big_int_vec.push_back(5);
        }
        else if (num == '6')
        {
            big_int_vec.push_back(6);
        }
        else if (num == '7')
        {
            big_int_vec.push_back(7);
        }
        else if (num == '8')
        {
            big_int_vec.push_back(8);
        }
        else if (num == '9')
        {
            big_int_vec.push_back(9);
        }
        else if (num == '-' and i == a.begin())
        {
            sign = false;
        }
        else if (num == '+' and i == a.begin())
        {
            sign = true;
        }
        else
        {
            throw(invalid_argument("Your string contains invalid characters"));
        }
    }

    while (true)
    {
        if (big_int_vec.back() == 0 and big_int_vec.size() != 1)
        {
            big_int_vec.pop_back();
        }
        else
        {
            break;
        }
    }
}

// two getter function
bool bigint::get_sign() const
{
    return sign;
}
vector<uint8_t> bigint::get_vector() const
{
    return big_int_vec;
}

// change sign function
void bigint::change_sign(bool new_sign)
{
    sign = new_sign;
}

// Compare operator ==
bool operator==(const bigint &lhs, const bigint &rhs)
{

    if (lhs.get_sign() != rhs.get_sign())
    {
        return false;
    }
    if (lhs.get_vector() != rhs.get_vector())
    {
        return false;
    }
    return true;
}
// Compare operator !=
bool operator!=(const bigint &lhs, const bigint &rhs)
{

    return !(lhs == rhs);
}

// Compare operator >
bool operator>(const bigint &lhs, const bigint &rhs)
{
    bool lhs_sign = lhs.get_sign();
    bool rhs_sign = rhs.get_sign();
    vector<uint8_t> lhs_vect = lhs.get_vector();
    vector<uint8_t> rhs_vect = rhs.get_vector();

    if (lhs_sign == true and rhs_sign == false)
    {
        // lhs is postive and rhs is negative
        return true;
    }

    if (lhs_sign == false and rhs_sign == true)
    {
        // lhs is negative and rhs is positive
        return false;
    }

    if (lhs_sign == true and rhs_sign == true)
    {
        if (lhs_vect.size() > rhs_vect.size())
        {
            return true;
        }
        else if (lhs_vect.size() == rhs_vect.size())
        {
            for (size_t i = 0; i < lhs_vect.size(); i++)
            {

                if (lhs_vect[i] > rhs_vect[i])
                {
                    return true;
                }
                if (lhs_vect[i] < rhs_vect[i])
                {
                    return false;
                }
            }
            return false;
        }
        else
        {
            return false;
        }
    }

    if (lhs_sign == false and rhs_sign == false)
    {
        if (lhs_vect.size() > rhs_vect.size())
        {
            return false;
        }
        else if (lhs_vect.size() == rhs_vect.size())
        {
            for (size_t i = 0; i < lhs_vect.size(); i++)
            {

                if (lhs_vect[i] > rhs_vect[i])
                {
                    return false;
                }
                if (lhs_vect[i] < rhs_vect[i])
                {
                    return true;
                }
            }
            return false;
        }
        else
        {
            return true;
        }
    }
    return false;
}

// Compare operator >=
bool operator>=(const bigint &lhs, const bigint &rhs)
{
    if (lhs == rhs)
        return true;
    else
    {
        return (lhs > rhs);
    }
}
// Compare operator <=
bool operator<=(const bigint &lhs, const bigint &rhs)
{
    return !(lhs > rhs);
}
// Compare operator <
bool operator<(const bigint &lhs, const bigint &rhs)
{
    return !(lhs >= rhs);
}
// print out operator << overload
ostream &operator<<(ostream &out, const bigint &bigint_a)
{
    if (bigint_a.sign == false)
        cout << "-";
    vector<uint8_t> vect = bigint_a.big_int_vec;
    for (vector<uint8_t>::iterator i = vect.end() - 1; i != vect.begin() - 1; i--)
        out << to_string(*i);
    return out;
}
// assignment operator =
bigint &bigint::operator=(const bigint &rhs)
{
    this->big_int_vec = rhs.big_int_vec;
    this->sign = rhs.sign;
    return *this;
}
// unary minus operator -
bigint operator-(bigint rhs)
{
    if (rhs.get_sign() == true)
    {
        rhs.change_sign(false);
    }
    else
    {
        rhs.change_sign(true);
    }
    return rhs;
}
// binary operator -=
bigint &bigint::operator-=(const bigint &other)
{
    if (this->sign == other.sign)
    {
        bigint temp;
        if (*this > other)
        {
            temp = other;
        }
        else if (*this == other)
        {
            // return 0
            *this = bigint();
            return *this;
        }
        else
        {
            temp = *this;
            *this = other;
            this->sign = !(this->sign);
        }

        size_t size_max = this->big_int_vec.size();
        uint8_t borrow = 0;
        for (size_t i = 0; i < size_max; i++)
        {
            uint8_t number;
            if (temp.big_int_vec.size() > i)
            {
                number = this->big_int_vec[i] + 10 - temp.big_int_vec[i] - borrow;
                this->big_int_vec[i] = (number) % 10;
            }
            else
            {
                number = this->big_int_vec[i] + 10 - borrow;
                this->big_int_vec[i] = (number) % 10;
            }
            if (number < 10)
            {
                borrow = 1;
            }
            else
            {
                borrow = 0;
            }
        }
        // erase the zeroes in front if exist;
        while (true)
        {
            if (this->big_int_vec.back() == 0)
            {
                this->big_int_vec.pop_back();
            }
            else
            {
                break;
            }
        }
        return *this;
    }
    else
    {
        *this += (-other);
        return *this;
    }
}

// binary operator +=
bigint &bigint::operator+=(const bigint &other)
{
    if (this->sign == other.sign)
    {
        uint8_t carry = 0;
        size_t max_size = std::max(other.big_int_vec.size(), this->big_int_vec.size());
        for (size_t i = 0; i < max_size; i++)
        {
            uint8_t number;
            if (this->big_int_vec.size() > i and other.big_int_vec.size() > i)
            {
                number = (carry + other.big_int_vec[i] + this->big_int_vec[i]);
                this->big_int_vec[i] = (carry + other.big_int_vec[i] + this->big_int_vec[i]) % 10;
            }
            else if (this->big_int_vec.size() <= i)
            {
                number = carry + other.big_int_vec[i];
                this->big_int_vec.push_back(number % 10);
            }
            else
            {
                number = carry + this->big_int_vec[i];
                this->big_int_vec[i] = number % 10;
            }
            if (number >= 10)
                carry = 1;
            else
                carry = 0;
        }
        if (carry == 1)
        {
            this->big_int_vec.push_back(1);
        }
        return *this;
    }
    else
    {
        if (other.sign == false)
        {
            *this -= (-other);
        }
        else
        {
            this->sign = true;
            *this -= other;
            this->sign = false;
        }
        return *this;
    }
}

// binary operator *=
bigint &bigint::operator*=(const bigint &other)
{
    bigint zero;

    for (size_t i = 0; i < other.big_int_vec.size(); i++)
    {
        bigint temp;
        temp.big_int_vec.pop_back();
        for (size_t j = 0; j < i; j++)
        {
            temp.big_int_vec.push_back(0);
        }
        uint8_t quotient = 0;
        uint8_t reminder = 0;
        for (size_t k = 0; k < this->big_int_vec.size(); k++)
        {
            uint8_t number = this->big_int_vec[k] * other.big_int_vec[i] + quotient;
            quotient = number / 10;
            reminder = number % 10;
            temp.big_int_vec.push_back(reminder);
        }
        if (quotient != 0)
        {
            temp.big_int_vec.push_back(quotient);
        }
        zero += temp;
    }
    if (this->sign == other.sign)
    {
        zero.sign = true;
    }
    else
    {
        zero.sign = false;
    }
    while (true)
    {
        if (zero.big_int_vec.back() == 0 and zero.big_int_vec.size() != 1)
        {
            zero.big_int_vec.pop_back();
        }
        else
        {
            break;
        }
    }
    *this = zero;
    return *this;
}
// Overloaded binary operator - to subtract two bigint.
bigint operator+(bigint lhs, const bigint &rhs)
{
    return lhs += rhs;
}

// Overloaded binary operator - to subtract two bigint.
bigint operator-(bigint lhs, const bigint &rhs)
{
    return lhs -= rhs;
}
// Overloaded binary operator - to multiply two bigint.
bigint operator*(bigint lhs, const bigint &rhs)
{
    return lhs *= rhs;
}