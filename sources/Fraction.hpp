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

        Fraction(const Fraction &_frac);

        Fraction(Fraction &&_frac) noexcept;

        Fraction(const int &n);

        Fraction(const double &dec);

        Fraction(const float &flt);

        ~Fraction();

        int getNumerator();

        int getDenominator();

        Fraction &operator=(const Fraction &_frac);

        // Arithmetic operations:
        friend Fraction operator+(const Fraction &_frac1, const Fraction &_frac2);

        friend Fraction operator-(const Fraction &_frac1, const Fraction &_frac2);

        friend Fraction operator*(const Fraction &_frac1, const Fraction &_frac2);

        friend Fraction operator/(const Fraction &_frac1, const Fraction &_frac2);


        Fraction &operator+=(const Fraction &_frac);

        Fraction &operator-=(const Fraction &_frac);

        Fraction &operator*=(const Fraction &_frac);

        Fraction &operator++();

        Fraction operator++(int);

        Fraction &operator--();

        Fraction operator--(int);

        Fraction operator-() const;

        // Boolean operations:
        bool operator!() const;

        friend bool operator!=(const Fraction &_frac1, const Fraction &_frac2);

        friend bool operator==(const Fraction &_frac1, const Fraction &_frac2);

        friend bool operator>=(const Fraction &_frac1, const Fraction &_frac2);

        friend bool operator<=(const Fraction &_frac1, const Fraction &_frac2);

        friend bool operator<(const Fraction &_frac1, const Fraction &_frac2);

        friend bool operator>(const Fraction &_frac1, const Fraction &_frac2);

        // Conversions:
        explicit operator double() const;

        explicit operator float() const;

        // I/O operations:
        friend std::ostream &operator<<(ostream &output, const Fraction &_frac);

        friend std::istream &operator>>(istream &input, Fraction &_frac);

        Fraction &operator=(Fraction &&_frac) noexcept;

    private:
        /**
         * Reduce the fraction to it's minimal form.
         */
        void reducedForm();

        static istream &checkNextChar(istream &input, char expectedChar);

    };

    /**
 * Check for overflow when adding 2 integers.
 * @param _n1
 * @param _n2
 * @return Sum of _n1 and _n2.
 * @throw overflow_error
 */
    int addOvf(int _n1, int _n2);

    /**
     * Check for overflow when multiplying 2 integers.
     * @param _n1
     * @param _n2
     * @return Multiplication of _n1 and _n2.
     * @throw overflow_error
     */
    int mulOvf(int _n1, int _n2);

}
#endif