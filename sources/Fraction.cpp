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

    Fraction::Fraction(const int &n) :
            _numerator(n),
            _denominator(1) {}

    Fraction::Fraction(const Fraction &_frac)
            : _numerator(_frac._numerator),
              _denominator(_frac._denominator) {
        this->reducedForm();
    }

    Fraction::Fraction(Fraction &&_frac) :
            _numerator(_frac._numerator),
            _denominator(_frac._denominator) {
        this->reducedForm();
    }

    Fraction::Fraction(const double &dec) :
            _numerator(floor(dec * 1000)),
            _denominator(1000) {
        this->reducedForm();
    }

    Fraction::Fraction(const float &flt) :
            _numerator(floor(flt * 1000)),
            _denominator(1000) {
        this->reducedForm();
    }

    Fraction::~Fraction() =
    default;

    int Fraction::getNumerator() { return this->_numerator; }

    int Fraction::getDenominator() { return this->_denominator; }

    Fraction &Fraction::operator=(const Fraction &_frac) {
        if (this != &_frac) {
            this->_numerator = _frac._numerator;
            this->_denominator = _frac._denominator;
        }
        return *this;
    }

    Fraction operator+(const Fraction &_frac1, const Fraction &_frac2) {
        return {addOvf(mulOvf(_frac1._numerator, _frac2._denominator), mulOvf(_frac2._numerator, _frac1._denominator)),
                mulOvf(_frac1._denominator, _frac2._denominator)};
    }

    Fraction operator-(const Fraction &_frac1, const Fraction &_frac2) {
        return {addOvf(mulOvf(_frac1._numerator, _frac2._denominator),
                       mulOvf(mulOvf(-1, _frac2._numerator), _frac1._denominator)),
                mulOvf(_frac1._denominator, _frac2._denominator)};
    }

    Fraction operator*(const Fraction &_frac1, const Fraction &_frac2) {
        return {mulOvf(_frac1._numerator, _frac2._numerator),
                mulOvf(_frac1._denominator, _frac2._denominator)};
    }

    Fraction operator/(const Fraction &_frac1, const Fraction &_frac2) {
        if (_frac2._numerator == 0) {
            throw overflow_error("ARITHMETIC ERROR: Can not divide by 0!");
        }
        return {mulOvf(_frac1._numerator, _frac2._denominator), mulOvf(_frac1._denominator, _frac2._numerator)};
    }


    Fraction &Fraction::operator+=(const Fraction &_frac) {
        this->_numerator = addOvf(mulOvf(this->_numerator, _frac._denominator),
                                  mulOvf(_frac._numerator, this->_denominator));
        this->_denominator = mulOvf(this->_denominator, _frac._denominator);
        this->reducedForm();
        return *this;
    }

    Fraction &Fraction::operator-=(const Fraction &_frac) {
        this->_numerator = addOvf(mulOvf(this->_numerator, _frac._denominator),
                                  mulOvf(mulOvf(-1, _frac._numerator), this->_denominator));
        this->_denominator = mulOvf(this->_denominator, _frac._denominator);
        this->reducedForm();
        return *this;
    }

    Fraction &Fraction::operator*=(const Fraction &_frac) {
        this->_numerator = mulOvf(this->_numerator, _frac._numerator);
        this->_denominator = mulOvf(this->_denominator, _frac._denominator);
        this->reducedForm();
        return *this;
    }

    Fraction &Fraction::operator++() {
        this->_numerator = addOvf(this->_numerator, this->_denominator);
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
        this->_numerator = addOvf(this->_numerator, mulOvf(-1, this->_denominator));
        this->reducedForm();
        return *this;
    }

    Fraction Fraction::operator--(int) {
        Fraction copy = *this;
        this->_numerator = addOvf(this->_numerator, mulOvf(-1, this->_denominator));
        this->reducedForm();
        return copy;
    }

    Fraction Fraction::operator-() const {
        return {mulOvf(-1, this->_numerator), this->_denominator};
    }

    bool Fraction::operator!() const {
        return this->_numerator == 0;
    }

    bool operator==(const Fraction &_frac1, const Fraction &_frac2) {
        return (double(_frac1) == double(_frac2) || abs(double(_frac1) - double(_frac2)) < 0.001);
    }

    bool operator!=(const Fraction &_frac1, const Fraction &_frac2) {
        return !(_frac1 == _frac2);
    }

    bool operator>=(const Fraction &_frac1, const Fraction &_frac2) {
        return double(_frac1) >= double(_frac2);
    }

    bool operator<=(const Fraction &_frac1, const Fraction &_frac2) {
        return double(_frac1) <= double(_frac2);
    }

    bool operator>(const Fraction &_frac1, const Fraction &_frac2) {
        return double(_frac1) > double(_frac2);
    }

    bool operator<(const Fraction &_frac1, const Fraction &_frac2) {
        return double(_frac1) < double(_frac2);
    }

    std::ostream &operator<<(ostream &output, const Fraction &_frac) {
        return output << _frac._numerator << '/' << _frac._denominator;
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

    std::istream &operator>>(istream &input, Fraction &_frac) {
        int new_num = 0, new_den = 0;
        // remember place for rewinding
        ios::pos_type startPosition = input.tellg();

        if ((!(input >> new_num)) || (!(input >> new_den))) {
            if (new_den == 0) {
                throw runtime_error("RUNTIME ERROR: Denominator can not be 0!\n");
            }
            _frac.reducedForm();
            // rewind on error
            auto errorState = input.rdstate(); // remember error state
            input.clear(); // clear error so seekg will work
            input.seekg(startPosition); // rewind
            input.clear(errorState); // set back the error flag
        } else {
            if (new_den == 0) {
                throw runtime_error("RUNTIME ERROR: Denominator can not be 0!\n");
            }
            _frac._numerator = new_num;
            _frac._denominator = new_den;
            _frac.reducedForm();
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

    Fraction &Fraction::operator=(Fraction &&_frac)

    noexcept {
    this->
    _numerator = _frac._numerator;
    this->
    _denominator = _frac._denominator;
    return *this;
}

int addOvf(int _n1, int _n2) {
    if (((_n1 >= 0) && (_n2 >= 0) && (_n1 > max_int - _n2)) ||
        ((_n1 < 0) && (_n2 < 0) && (_n1 < min_int - _n2))) {
        throw overflow_error("OVERFLOW ERROR!\n");
    } else {
        return _n1 + _n2;
    }
}

int mulOvf(int _n1, int _n2) {
    if (((_n1 == -1) && (_n2 == min_int)) || ((_n1 == min_int) && (_n2 == -1))) {
        throw overflow_error("OVERFLOW ERROR!\n");
    } else {
        int c = _n1 * _n2;
        if (((_n1 != 0) && (c / _n1 != _n2))) {
            throw overflow_error("OVERFLOW ERROR!\n");
        } else {
            return _n1 * _n2;
        }
    }
}


}
