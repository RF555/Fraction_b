#include <cmath>
#include <numeric>
#include <iomanip>
#include "Fraction.hpp"


namespace ariel {
    int max_int = std::numeric_limits<int>::max();
    int min_int = std::numeric_limits<int>::min();

    Fraction::Fraction() : _numerator(0), _denominator(1) {}

    Fraction::Fraction(int numerator, int denominator = 1) : _numerator(numerator), _denominator(denominator) {
        if (denominator == 0) {
            throw invalid_argument("INVALID ERROR: Denominator can not be 0!\n");
        }
        this->reducedForm();
    }

    Fraction::Fraction(const int &n) : _numerator(n), _denominator(1) {}

    Fraction::Fraction(const Fraction &_other)
            : _numerator(_other._numerator), _denominator(_other._denominator) {
        this->reducedForm();
    }

    Fraction::Fraction(const double &d) : _numerator(floor(d * 1000)), _denominator(1000) {
        this->reducedForm();
    }

    Fraction::Fraction(const float &f) : _numerator(floor(f * 1000)), _denominator(1000) {
        this->reducedForm();
    }

    Fraction::~Fraction() = default;

    int Fraction::getNumerator() { return this->_numerator; }

    int Fraction::getDenominator() { return this->_denominator; }

    Fraction &Fraction::operator=(const Fraction &q) {
        if (this != &q) {
            this->_numerator = q._numerator;
            this->_denominator = q._denominator;
        }
        return *this;
    }

    Fraction operator+(const Fraction &a, const Fraction &b) {
        return {addOvf(mulOvf(a._numerator, b._denominator), mulOvf(b._numerator, a._denominator)),
                mulOvf(a._denominator, b._denominator)};
    }

    Fraction operator-(const Fraction &a, const Fraction &b) {
        return {addOvf(mulOvf(a._numerator, b._denominator), mulOvf(-1 * b._numerator, a._denominator)),
                mulOvf(a._denominator, b._denominator)};
    }

    Fraction operator*(const Fraction &a, const Fraction &b) {
        return {mulOvf(a._numerator, b._numerator),
                mulOvf(a._denominator, b._denominator)};
    }

    Fraction operator/(const Fraction &a, const Fraction &b) {
        if (b._numerator == 0) {
            throw overflow_error("ARITHMETIC ERROR: Can not divide by 0!");
        }
        return {mulOvf(a._numerator, b._denominator), mulOvf(a._denominator, b._numerator)};
    }


    Fraction &Fraction::operator+=(const Fraction &q) {
        this->_numerator = addOvf(mulOvf(this->_numerator, q._denominator), mulOvf(q._numerator, this->_denominator));
        this->_denominator = mulOvf(q._denominator, q._denominator);
        this->reducedForm();
        return *this;
    }

    Fraction &Fraction::operator-=(const Fraction &q) {
        this->_numerator = addOvf(mulOvf(this->_numerator, q._denominator),
                                  mulOvf(-1 * q._numerator, this->_denominator));
        this->_denominator = mulOvf(this->_denominator, q._denominator);
        this->reducedForm();
        return *this;
    }

    Fraction &Fraction::operator*=(const Fraction &q) {
        this->_numerator = mulOvf(this->_numerator, q._numerator);
        this->_denominator = mulOvf(this->_denominator, q._denominator);
        this->reducedForm();
        return *this;
    }

    Fraction &Fraction::operator++() {
        this->_numerator = addOvf(this->_denominator, this->_denominator);
        this->reducedForm();
        return *this;
    }

    Fraction Fraction::operator++(int) {
        Fraction copy = *this;
        this->_numerator = addOvf(this->_numerator, this->_denominator);
        this->reducedForm();
        return copy;
    }

    Fraction &Fraction::operator--() {
        this->_numerator = addOvf(this->_numerator, -1 * this->_denominator);
        this->reducedForm();
        return *this;
    }

    Fraction Fraction::operator--(int) {
        Fraction copy = *this;
        this->_numerator = addOvf(this->_numerator, -1 * this->_denominator);
        this->reducedForm();
        return copy;
    }

    Fraction Fraction::operator-() const {
        return {-1 * this->_numerator, this->_denominator};
    }

    bool Fraction::operator!() const {
        return this->_numerator == 0;
    }

    bool operator==(const Fraction &a, const Fraction &b) {
        return (double(a) == double(b) || abs(double(a) - double(b)) < 0.001);
    }

    bool operator!=(const Fraction &a, const Fraction &b) {
        return !(a == b);
    }

    bool operator>=(const Fraction &a, const Fraction &b) {
        return double(a) >= double(b);
    }

    bool operator<=(const Fraction &a, const Fraction &b) {
        return double(a) <= double(b);
    }

    bool operator>(const Fraction &a, const Fraction &b) {
        return double(a) > double(b);
    }

    bool operator<(const Fraction &a, const Fraction &b) {
        return double(a) < double(b);
    }

    std::ostream &operator<<(ostream &output, const Fraction &q) {
        return output << q._numerator << '/' << q._denominator;
    }

    istream &Fraction::checkNextChar(istream &input, char expectedChar) {
        char actualChar;
        input >> actualChar;
        if (!input) { return input; }
        if (actualChar != expectedChar) {
            input.setstate(ios::failbit);
        }
        return input;
    }

    std::istream &operator>>(istream &input, Fraction &q) {
        int new_num = 0, new_den = 0;
        // remember place for rewinding
        ios::pos_type startPosition = input.tellg();

        if ((!(input >> new_num)) || (!(input >> new_den))) {
            if (new_den == 0) {
                throw runtime_error("RUNTIME ERROR: Denominator can not be 0!\n");
            }
            q.reducedForm();
            // rewind on error
            auto errorState = input.rdstate(); // remember error state
            input.clear(); // clear error so seekg will work
            input.seekg(startPosition); // rewind
            input.clear(errorState); // set back the error flag
        } else {
            if (new_den == 0) {
                throw runtime_error("RUNTIME ERROR: Denominator can not be 0!\n");
            }
            q._numerator = new_num;
            q._denominator = new_den;
            q.reducedForm();
        }
        return input;
    }

    void Fraction::reducedForm() {
        int num = this->_numerator;
        int den = this->_denominator;
        int d = gcd(num, den);
        this->_numerator = this->_numerator / d;
        this->_denominator = this->_denominator / d;
        if (this->_denominator < 0) {
            this->_denominator *= -1;
            this->_numerator *= -1;
        }
    }

    Fraction::operator double() const {
        return round(this->_numerator * 100000.0 / this->_denominator) / 100000;
    }

    Fraction::operator float() const {
        return round(this->_numerator * 100000.0 / this->_denominator) / 100000;
    }

    int addOvf(int a, int b) {
        if ((a >= 0) && (b >= 0) && (a > max_int - b)) {
            throw overflow_error("OVERFLOW ERROR!\n");
        } else {
            return a + b;
        }
    }

    int mulOvf(int a, int b) {
        int c = a * b;
        if ((a != 0) && (c / a != b)) {
            throw overflow_error("OVERFLOW ERROR!\n");
        } else {
            return a * b;
        }
    }


}
