# Bigint class for arbitary-precision integer

Here is a brief introduction to the bigint class which is designed for an arbitary-precision signed integer. It serves as an extension as c++ signed integer. User could input an arbitary long string that represents a integer and it will be converted into the bigint class for further use. Users could also provide a 64-bit signed integer and it would convert it into bigint class as well. The bigint could deal with several operation between the bigint class but not with other c++ originally available integer type.

## Compilation 
You could compile the file with the latest gcc / clang.

## Constructor

We provides three different kinds of contructors.

1. default constructor 
- create an integer 0 with a default positve sign. 

2. constructor with int64_t (64 bit signed integer as input) 
- convert the integer into bigint class with arbitary-precision

3. constructor with string 
- take an arbitary long string of digits and convert into bigint class
- exception detection if strings contain invalid characters like "&*#"

## Operation Overloading

We overload the following operation for usage.

1. Addition (+ and +=)
2. Subtraction (- and -=)
3. Multiplication (* and *=)
4. Negation (unary -)
5. Comparison (==, !=, <, >, <=, and >=)
6. Assignment (=)
7. Insertion (<<, to print the integer to a stream such as std::cout or a file)

## Internal storage 

We store our digits in a vector of 8-bit unsigned integer and a boolean value for sign of number. True for positive sign (including zero) and false for negative sign.

## Functions in class 

The following operators are defined as member function in class

1. bigint &operator-=(const bigint &)
2. bigint &operator+=(const bigint &)
3. bigint &operator*=(const bigint &)
4. bigint &operator=(const bigint &)

The other member function includes:
5. void change_sign(bool) 
- set function for sign

6. bool get_sign() const;
- getter function for sign
7. vector<uint8_t> get_vector() const
- getter function for vector


## Non member function 

9. friend ostream &operator<<(ostream &, const bigint &);
- friend function to print out the integer

10. bool operator==(const bigint &, const bigint &);
- function to check two integers equal

11. bool operator!=(const bigint &, const bigint &);
- function to check two integers not equal

12. bool operator>(const bigint &, const bigint &);
- function to check lhs larger than rhs or not


13. bool operator>=(const bigint &, const bigint &);
- function to check lhs larger than rhs or not


12. bool operator<(const bigint &, const bigint &);
- function to check lhs smaller than rhs or not

12. bool operator<=(const bigint &, const bigint &);
- function to check lhs smaller than rhs or not

14. bigint operator+(bigint, const bigint &);
- function to check lhs larger than rhs or not

15. bigint operator-(const bigint);
- function to check lhs larger than rhs or not

16. bigint operator-(bigint, const bigint &);
- function to check lhs larger than rhs or not

17. bigint operator*(const bigint &, const bigint &);
- function to check lhs larger than rhs or not

## Algorithms for the mathematical operation

### Addition
We separate two case in addition.
Case 1: signs of two number equal. 
Case 2: signs of two number differ.

Case 1 follows simple math from addition. uint_8 carry is needed to handle the carry in addition such as 15 + 16 = 31, the 5+6 =11 will give an extra +11 for 1 + 1 in 10-digit.

Case 2 will be handled by substraction in case 1. 

### Substraction

We separate two case in substraction.
Case 1: signs of two number equal. 
Case 2: signs of two number differ.

Case 1 follows simple math. uint_8 borrow is needed to handle the borrow in addition such as 30 - 16 = 14, the 0 - 6 in one-digit becomes 0 - 6 + 10 = 4 , and borrow will be 1 for 10-digit, i.e. 3 - 1 - 1. Extra minus one due to borrow.

Case 2 is handled by addition in case 1

### Multiplication

We handle the digits multiplication as math tells. We define remainder and quotient. For example, for 8 * 7 = 56, the 6 will keep as reminder and stay at its original digit, and 5 will be the quotient as carry for next digit. Another thing in  multiplication is that we need to deal with multiple digits. For example in 13 * 19, we will do it in the way of (13)*(10+9). We first handle 13 * 9 by digit-by-digit multiplication, then we will plus 13 * 10. For the part of sign , we handles at last using the simple math rule.

## Example
The below shows the demo and the expected output. 

```cpp
#include "bigint.hpp"
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdint>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    // default constructor
    bigint A;
    cout << "A : " << A << "\n"; // print 0

    // constructor with int64
    int64_t pos_num = 62;
    int64_t neg_num = -3721973298;
    bigint B(pos_num);
    bigint C(neg_num);
    cout << "B : " << B << "\n"; // print 372973298
    cout << "C : " << C << "\n"; // print -3721973298

    // constuctor with arbitary long string
    string a = "21120432749928429374310981";
    string b = "+9048112032749928429374310981";
    string c = "-4832947927403183108310392";
    string d = "4390593509305+-=3%4234333";

    bigint D(a);
    bigint E(b);
    bigint F(c);
    cout << "D : " << D << "\n"; // print 21120432749928429374310981
    cout << "E : " << E << "\n"; // print 9048112032749928429374310981
    cout << "F : " << F << "\n"; // print -4832947927403183108310392

    // error handling
    try
    {
        bigint G(d);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n'; // print error message
    }

    // some simple number that can verify
    bigint X(49);
    bigint Y(32);
    bigint Z(-89);
    cout << "X : " << X << "\n"; // print 49
    cout << "Y : " << Y << "\n"; // print 32
    cout << "Z : " << Z << "\n"; // print -89

    // Addition with + , - , * with
    cout << "Result from big int : X + Y = " << (X + Y) << " ; Result from C++ original: " << (49 + 32) << "\n";

    cout << "Result from big int : Y - X = " << (Y - X) << " ; Result from C++ original: " << (32 - 49) << "\n";

    cout << "Result from big int : X * Y = " << (X * Z) << " ; Result from C++ original: " << (49 * -89) << "\n";

    // comparison operator
    cout << boolalpha;
    cout << "Result from big int : X > Y = " << (X > Y) << " ; Result from C++ original: " << (49 > 32) << "\n";
    cout << "Result from big int : X >= Y = " << (X >= Y) << " ; Result from C++ original: " << (49 >= 32) << "\n";
    cout << "Result from big int : Z < X = " << (Z < X) << " ; Result from C++ original: " << (-89 < 49) << "\n";
    cout << "Result from big int : Z <= X = " << (Z <= X) << " ; Result from C++ original: " << (-89 <= 49) << "\n";
    cout << "Result from big int : X == X = " << (X == X) << " ; Result from C++ original: " << (49 == 49) << "\n";
    cout << "Result from big int : X != Y = " << (X != Y) << " ; Result from C++ original: " << (49 != 32) << "\n";

    // unary minus operator
    cout << "Result from big int : -X = " << -X << "\n";

    // assignment = operator

    A = X;
    cout << "New A = " << A << " and X = " << X << "\n";
    // += , -= , *=

    cout << "Result from big int X += Y " << (X += Y) << " ; Result from C++ original: " << (49 + 32) << "\n";
    cout << "Result from big int Y -= Z " << (Y -= Z) << " ; Result from C++ original: " << (32 - -89) << "\n";
    cout << "Result from big int Z *= X " << (Z *= X) << " ; Result from C++ original: " << (-89 * (49 + 32)) << "\n";

    return 0;

}

```
A : 0
B : 62
C : -3721973298
D : 21120432749928429374310981
E : 9048112032749928429374310981
F : -4832947927403183108310392
Your string contains invalid characters
X : 49
Y : 32
Z : -89
Result from big int : X + Y = 81 ; Result from C++ original: 81
Result from big int : Y - X = -17 ; Result from C++ original: -17
Result from big int : X * Y = -4361 ; Result from C++ original: -4361
Result from big int : X > Y = true ; Result from C++ original: true
Result from big int : X >= Y = true ; Result from C++ original: true
Result from big int : Z < X = true ; Result from C++ original: true
Result from big int : Z <= X = true ; Result from C++ original: true
Result from big int : X == X = true ; Result from C++ original: true
Result from big int : X != Y = true ; Result from C++ original: true
Result from big int : -X = -49
New A = 49 and X = 49
Result from big int X += Y 81 ; Result from C++ original: 81
Result from big int Y -= Z 121 ; Result from C++ original: 121
Result from big int Z *= X -7209 ; Result from C++ original: -7209