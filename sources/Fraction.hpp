#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <iostream>
#include <string>

using namespace std;
namespace ariel {
    class Fraction {
        int _numerator, _denominator;

    public:
        Fraction();

        /**
         * @throw invalid_argument when denominator is 0.
         */
        Fraction(int numerator, int denominator);

        Fraction(const Fraction &_other);

        Fraction(const int &n);

        Fraction(const double &d);

        Fraction(const float &f);

        ~Fraction();

        int getNumerator();

        int getDenominator();

        Fraction &operator=(const Fraction &q);

        // Arithmetic operations:
        friend Fraction operator+(const Fraction &a, const Fraction &b);

        friend Fraction operator-(const Fraction &a, const Fraction &b);

        friend Fraction operator*(const Fraction &a, const Fraction &b);

        friend Fraction operator/(const Fraction &a, const Fraction &b);


        Fraction &operator+=(const Fraction &q);

        Fraction &operator-=(const Fraction &q);

        Fraction &operator*=(const Fraction &q);

        Fraction &operator++();

        Fraction operator++(int);

        Fraction &operator--();

        Fraction operator--(int);

        Fraction operator-() const;

        // Boolean operations:
        bool operator!() const;

        friend bool operator!=(const Fraction &a, const Fraction &b);

        friend bool operator==(const Fraction &a, const Fraction &b);

        friend bool operator>=(const Fraction &a, const Fraction &b);

        friend bool operator<=(const Fraction &a, const Fraction &b);

        friend bool operator<(const Fraction &a, const Fraction &b);

        friend bool operator>(const Fraction &a, const Fraction &b);

        // Conversions:
        explicit operator double() const;

        explicit operator float() const;

        // I/O operations:
        friend std::ostream &operator<<(ostream &output, const Fraction &q);

        friend std::istream &operator>>(istream &input, Fraction &q);

    private:
        /**
         * Reduce the fraction to it's minimal form.
         */
        void reducedForm();

        static istream &checkNextChar(istream &input, char expectedChar);

    };

    /**
 * Check for overflow when adding 2 integers.
 * @param a
 * @param b
 * @return Sum of a and b.
 * @throw overflow_error
 */
    int addOvf(int a, int b);

    /**
     * Check for overflow when multiplying 2 integers.
     * @param a
     * @param b
     * @return Multiplication of a and b.
     * @throw overflow_error
     */
    int mulOvf(int a, int b);

}
#endif