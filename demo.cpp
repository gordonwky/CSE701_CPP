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
    // A += B;
    // cout << A;
}
