#include <vector>
#include <utility>
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include "myComplex.h"

#define KARATSUBA 0
#define FFT 1

inline int multiplicationCount = 0;

namespace myfunc  {

    class bigInt;
    class div;

    inline std::unordered_map<int, complex <long double>> wRoots;
    inline bool hasComputedRoots = false;
    inline int maxDigits = (1 << 13);

    class bigInt  {
        private:
        std::vector <long long> digits;
        long long sign = 1;

        // Methods that only do additions and subtractions for
        // non-negative integers (subtraction requires the first number
        // to be greater as well)
        void additionHelper(const bigInt& oth);
        void subtractionHelper(const bigInt& oth);
        // Used to treat the case when this is smaller than oth (in absolute value)
        void inverseSubtractionHelper(const bigInt& oth);
        // Compares absolute values of integers
        bool absLess(const bigInt& oth);
        bool absEqual(const bigInt& oth);
        bool absGreater(const bigInt& oth);

        public:
        static const long long base = 1e4;
        static const int baseDigitCount = 4;
        static const int MUL_TYPE = KARATSUBA;
        // constructors
        bigInt();
        bigInt(const long long& nr);
        bigInt(const bigInt &oth);

        // digit size and sign
        const int size() const;
        const long long& _sign() const;
        long long& _sign();
        void setSign(const long long& msign);

        // Equal sign
        void operator = (const bigInt& oth);
        void operator = (const long long& nr);

        // Digit access operator
        long long& operator [] (const int& pos);
        const long long& operator [] (const int& pos) const;
        void push_back(const long long& digit);
        void pop_back();
        long long& back();
        const long long& back() const;
        long long& front();
        const long long& front() const;

        // Streams
        std::string show() const;

        // Comparators
        bool operator > (const bigInt& oth) const;
        bool operator < (const bigInt& oth) const;
        bool operator >= (const bigInt& oth) const;
        bool operator <= (const bigInt& oth) const;
        bool operator == (const bigInt& oth) const;
        bool operator != (const bigInt& oth) const;

        // Addition operation
        void operator += (const bigInt& oth);
        void operator += (const long long& nr);
        bigInt operator + (const bigInt& oth);
        bigInt operator + (const long long& nr);

        // Subtraction operation
        void operator -= (const bigInt& oth);
        void operator -= (const long long& nr);
        bigInt operator - (const bigInt& oth);
        bigInt operator - (const long long& nr);

        // Multiplication operation
        void operator *= (const bigInt &oth);
        void operator *= (const long long &nr);
        bigInt operator * (const bigInt& oth);
        bigInt operator * (const long long& nr);
        friend bigInt karatsubaHelper(const bigInt& x, const bigInt& y);
        friend bigInt fftHelper(const bigInt& x, const bigInt& y);
        bigInt pow (const int& exp);

        // Division operation
        void operator /= (const bigInt &oth);
        void operator /= (const long long &nr);
        bigInt operator / (const bigInt& oth);
        bigInt operator / (const long long& nr);

        // Remainder operation
        void operator %= (const bigInt &oth);
        void operator %= (const long long &oth);
        bigInt operator % (const bigInt& oth);
        bigInt operator % (const long long& nr);

        // Combines Divison and remainder for faster times
        div division (const bigInt& oth);
    };

    bigInt karatsubaHelper(const bigInt& x, const bigInt& y);

    bigInt operator - (const bigInt& oth);
    std::ostream &operator << (std::ostream &output, const bigInt& obj);
    std::istream &operator >> (std::istream &input, bigInt& obj);
    bigInt operator + (const long long& no, const bigInt& oth);
    bigInt operator - (const long long& no, const bigInt& oth);
    bigInt operator * (const long long& no, const bigInt& oth);

}
