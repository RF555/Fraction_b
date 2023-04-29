#include "doctest.h"
#include <stdexcept>
#include "sources/Fraction.hpp"

using namespace std;
using namespace ariel;

TEST_CASE("Constructors initiated correctly") {
    Fraction a;
    CHECK(a.numerator() == 0);
    CHECK(a.denominator() == 1);
    Fraction b(1, 3);
    CHECK(b.numerator() == 1);
    CHECK(b.denominator() == 3);
    float ff = 1.0 / 3;
    Fraction c(ff);
    CHECK(c == 1.0 / 3);
    CHECK(c == b);
    double dd = 1.0 / 6;
    Fraction d(dd);
    CHECK(d == 2.0 / 12);
    CHECK(d == c / 2);
}

TEST_CASE("Reduced form") {
    Fraction c(2, 4);
    CHECK(c.numerator() == 1);
    CHECK(c.denominator() == 2);
    Fraction d(3, 9);
    CHECK(d.numerator() == 1);
    CHECK(d.denominator() == 3);
//    cout << "d = " << d << " = " << double(d) << endl;

}

TEST_CASE("Error when dividing by 0") {
    CHECK_THROWS(Fraction(3, 0));
    Fraction a(2, 5);
    Fraction b;
    CHECK_THROWS(a / b);
    CHECK_THROWS(a / 0);
}

TEST_CASE("Copy constructor and = operation") {
    Fraction a(5, 9);
    Fraction b(a);
    CHECK(&a != &b);
    CHECK(a.numerator() == b.numerator());
    CHECK(a.denominator() == b.denominator());
    Fraction c = a;
    CHECK(&a != &c);
    CHECK(a.numerator() == c.numerator());
    CHECK(a.denominator() == c.denominator());
}

TEST_CASE("Arithmetic operations") {
    Fraction a;
    Fraction b(1, 5);
    Fraction c = a + b;
    CHECK(c == 0.2);
    Fraction d = b * c;
    CHECK(d == 0.04);
    Fraction e = b - d;
    CHECK(e == (0.2 - 0.04));
    c += b;
    CHECK(c == 0.4);
    e -= d;
    CHECK(e == (0.2 - 0.08));
    d *= b;
//    cout << "d=" << double(d) << endl;
    CHECK(d == 0.008);
    CHECK(a++ == 0);
    CHECK(a == 1);
    CHECK(++a == 2);
    Fraction f(20, 7);
    CHECK(f-- == 2.8571);
    CHECK(f == 1.8571);
    CHECK(--f == 0.8571);
    Fraction g = c / f;
    Fraction _g(0.4671);
//    cout << "g = " << g << " = " << double(g) << endl;
//    cout << "_g = " << _g << " = " << double(_g) << endl;
    CHECK(g == 0.4666);
    Fraction gg = -g;
    Fraction _gg(-0.4667);
//    cout << "gg = " << gg << " = " << double(gg) << endl;
//    cout << "_gg = " << _gg << " = " << double(_gg) << endl;
    CHECK(gg == -0.4666);
}

TEST_CASE("Boolean operations") {
    Fraction a;
    Fraction b(2, 5);
    Fraction bb(2, 5);
    Fraction c(3, 10);
    Fraction d(-5, 8);
    Fraction dd(10, -16);
    CHECK(!a);
    CHECK_FALSE(!b);
    CHECK(a != b);
    CHECK(c != d);
    CHECK(b == bb);
    CHECK(d == dd);
    CHECK(a >= a);
    CHECK(bb >= b);
    CHECK(c >= c);
    CHECK(dd >= d);
    CHECK(a <= a);
    CHECK(b <= bb);
    CHECK(c <= c);
    CHECK(d <= dd);
    CHECK(b > a);
    CHECK(d < a);
    CHECK(b > d);
//    cout << "a = " << a << " = " << double(a) << endl;
//    cout << "b = " << b << " = " << double(b) << endl;
//    cout << "c = " << c << " = " << double(c) << endl;
//    cout << "d = " << d << " = " << double(d) << endl;
}
