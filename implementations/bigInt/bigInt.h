#include <vector>
#include <utility>
#include <iostream>
#include <string>


namespace myfunc  {

    class bigInt;
    class div;

    class bigInt  {
        public:
        const long long base = 1e9;
        const int baseDigitCount = 9;
        std::vector <long long> digits;
        long long sign = 1;


        public:
        // constructors
        bigInt();
        bigInt(const long long& nr);
        bigInt(const bigInt &oth);

        // digit size and sign
        const int& size() const;
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

        // Streams
        std::string show() const;

        // Comparators
        bool operator > (const bigInt& oth) const;
        bool operator < (const bigInt& oth) const;
        bool operator >= (const bigInt& oth) const;
        bool operator <= (const bigInt& oth) const;
        bool operator == (const bigInt& oth) const;

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

    bigInt operator - (const bigInt& oth);
    std::ostream &operator << (std::ostream &output, const bigInt& obj);


}
