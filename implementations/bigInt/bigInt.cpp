#include "bigInt.h"

class myfunc::div  {
    myfunc::bigInt quotient;
    myfunc::bigInt remainder;
};

// digit size and sign
const int myfunc::bigInt::size () const {
    return this -> digits.size();
}

const long long& myfunc::bigInt::_sign() const  {
    return this -> sign;
}
long long& myfunc::bigInt::_sign()  {
    return this -> sign;
}

void myfunc::bigInt::setSign(const long long& msign)  {
    this -> sign = msign;
}

// Equal sign
void myfunc::bigInt::operator = (const myfunc::bigInt& oth)  {
    this -> digits = oth.digits;
    this -> sign = oth.sign;
}

void myfunc::bigInt::operator = (const long long& nr)  {
    this -> digits.clear();
    long long nrCopy = nr;
    if(nr < 0)
        this -> sign = -1, nrCopy = -nrCopy;
    else
        this -> sign = 1;
    while(nrCopy)  {
        this -> digits.push_back(nrCopy % base),
        nrCopy /= base;
    }
}


// Constructors
myfunc::bigInt::bigInt() {}

myfunc::bigInt::bigInt(const long long& nr)  {
    this -> digits.clear();
    long long nrCopy = nr;
    if(nr < 0)
        this -> sign = -1, nrCopy = -nrCopy;
    else
        this -> sign = 1;
    while(nrCopy)  {
        this -> digits.push_back(nrCopy % base),
        nrCopy /= base;
    }
}

myfunc::bigInt::bigInt(const bigInt& oth)  {
    this -> digits = oth.digits;
    this -> sign = oth.sign;
}

// Digit access operator
long long& myfunc::bigInt::operator [] (const int& pos)  {
    return this -> digits[pos];
}

const long long& myfunc::bigInt::operator [] (const int& pos) const {
    return this -> digits[pos];
}

void myfunc::bigInt::push_back (const long long& digit)  {
    this -> digits.push_back(digit);
}

void myfunc::bigInt::pop_back()  {
    this -> digits.pop_back();
}

long long& myfunc::bigInt::back()  {
    return this -> digits.back();
}

const long long& myfunc::bigInt::back() const {
    return this -> digits.back();
}

long long& myfunc::bigInt::front()  {
    return this -> digits.front();
}

const long long& myfunc::bigInt::front() const {
    return this -> digits.front();
}

// Streams
std::string myfunc::bigInt::show() const {
    std::string ans;
    if(this -> sign == -1)
        ans.push_back('-');
    if((*this).size() == 0)  {
        ans.push_back('0');
        return ans;
    }
    bool isFirst = true;
    std::string helper;
    for(int index = (*this).size() - 1;index >= 0;index--)  {
        helper.clear();
        long long hlp = (*this)[index];
        int indexCount = 0;
        while(hlp)
            helper.push_back((char)(hlp % 10LL + '0')), hlp /= 10LL, indexCount++;
        if(!isFirst)  {
            while(indexCount < baseDigitCount)
                helper.push_back('0'), indexCount++;
        }
        isFirst = false;
        if(helper.size())
            for(int t = (int)helper.size() - 1;t >= 0;t--)
                ans.push_back(helper[t]);
    }
    return ans;
}

std::ostream& myfunc::operator << (std::ostream &output, const myfunc::bigInt& obj)  {
    output << obj.show();
    return output;
}

std::istream& myfunc::operator >> (std::istream &input, myfunc::bigInt& obj)  {
    long long ans;
    input >> ans;
    obj = bigInt(ans);
    return input;
}

// Comparators
bool myfunc::bigInt::operator > (const bigInt& oth) const {
    if(this -> sign > oth.sign)  {
        return true;
    }
    else if(this -> sign < oth.sign)  {
        return false;
    }
    bool result = true;
    if(this -> sign == -1)
        result = false;
    if(this -> size() > oth.size())  {
        return result;
    }else if(this -> size() < oth.size())  {
        return !result;
    }
    int index = this -> size() - 1;
    while(index >= 0)  {
        if((*this)[index] > oth[index])  {
            return result;
        }else if((*this)[index] < oth[index])  {
            return !result;
        }
    }
    return false;
}

bool myfunc::bigInt::operator < (const bigInt &oth) const {
    if(this -> sign > oth.sign)  {
        return false;
    }
    else if(this -> sign < oth.sign)  {
        return true;
    }
    bool result = false;
    if(this -> sign == -1)
        result = true;
    if(this -> size() > oth.size())  {
        return result;
    }else if(this -> size() < oth.size())  {
        return !result;
    }
    int index = this -> size() - 1;
    while(index >= 0)  {
        if((*this)[index] > oth[index])  {
            return result;
        }else if((*this)[index] < oth[index])  {
            return !result;
        }
    }
    return false;
}

bool myfunc::bigInt::operator == (const bigInt &oth) const  {
    return (this -> sign == oth.sign && oth.size() == this -> size() &&
        oth.digits == this -> digits);
}

bool myfunc::bigInt::operator != (const bigInt &oth) const  {
    return !((*this) == oth);
}

bool myfunc::bigInt::operator >= (const bigInt &oth) const  {
    return !((*this) < oth);
}

bool myfunc::bigInt::operator <= (const bigInt &oth) const  {
    return !((*this) > oth);
}

// Addition and subtraction helpers

void myfunc::bigInt::additionHelper(const myfunc::bigInt& oth)  {
    long long remainder = 0LL, toPush = 0LL;
    int index = 0;
    while(index < oth.size() && index < this -> size())  {
        toPush = (oth[index] + (*this)[index] + remainder);
        remainder = toPush % base;
        toPush /= base;
        (*this)[index] = toPush;
        index++;
    }
    while(index < oth.size())  {
        toPush = (oth[index] + remainder);
        remainder = toPush % base;
        toPush /= base;
        (*this).push_back(toPush);
        index++;
    }
    while(index < (*this).size())  {
        toPush = ((*this)[index] + remainder);
        remainder = toPush % base;
        toPush /= base;
        (*this)[index] = toPush;
        index++;
    }
    while(remainder)  {
        (*this).push_back(remainder % base);
        remainder /= base;
    }
}

void myfunc::bigInt::subtractionHelper(const myfunc::bigInt& oth)  {
    long long remainder = 0LL, toPush = 0LL;
    int index = 0;
    while(index < oth.size() && index < this -> size())  {
        toPush = (-oth[index] + (*this)[index] - remainder);
        if(toPush < 0)
            remainder = 1, toPush += base;
        else
            remainder = 0;
        (*this)[index] = toPush;
        index++;
    }
    while(index < (*this).size())  {
        toPush = ((*this)[index] - remainder);
        if(toPush < 0)
            remainder = 1, toPush += base;
        else
            remainder = 0;
        (*this)[index] = toPush;
        index++;
    }
    while((*this).size() && (*this).back() == 0)
        (*this).pop_back();
}

void myfunc::bigInt::inverseSubtractionHelper(const myfunc::bigInt& oth)  {
    long long remainder = 0LL, toPush = 0LL;
    int index = 0;
    while(index < oth.size() && index < this -> size())  {
        toPush = (oth[index] - (*this)[index] - remainder);
        if(toPush < 0)
            remainder = 1, toPush += base;
        else
            remainder = 0;
        (*this)[index] = toPush;
        index++;
    }
    while(index < oth.size())  {
        toPush = (oth[index] - remainder);
        if(toPush < 0)
            remainder = 1, toPush += base;
        else
            remainder = 0;
        (*this).push_back(toPush);
        index++;
    }
    while((*this).size() && (*this).back() == 0)
        (*this).pop_back();
}

// Abs comparators

bool myfunc::bigInt::absLess(const myfunc::bigInt& oth)  {
    if(this -> size() < oth.size())  {
        return true;
    }
    if(this -> size() > oth.size())  {
        return false;
    }
    int index = this -> size() - 1;
    while(index >= 0)  {
        if((*this)[index] > oth[index])  {
            return false;
        }else if((*this)[index] < oth[index])  {
            return true;
        }
        index--;
    }
    return false;
}

bool myfunc::bigInt::absEqual(const myfunc::bigInt& oth)  {
    return (this -> digits == oth.digits);
}

bool myfunc::bigInt::absGreater(const myfunc::bigInt& oth)  {
    if(this -> size() < oth.size())  {
        return false;
    }
    if(this -> size() > oth.size())  {
        return true;
    }
    int index = this -> size() - 1;
    while(index >= 0)  {
        if((*this)[index] > oth[index])  {
            return true;
        }else if((*this)[index] < oth[index])  {
            return false;
        }
        index--;
    }
    return false;
}

// Addition operator + opposite sign operator

myfunc::bigInt myfunc::operator - (const myfunc::bigInt& oth)  {
    myfunc::bigInt ans = oth;
    ans.setSign(-ans._sign());
    return ans;
}

void myfunc::bigInt::operator += (const myfunc::bigInt& oth) {
    if(oth.sign == this -> sign)  {
        this -> additionHelper(oth);
    }else{
        if(this -> absEqual(oth))  {
            (*this) = 0;
        }else if(this -> absGreater(oth))  {
            this -> subtractionHelper(oth);
        }else{
            this -> inverseSubtractionHelper(oth);
            this -> sign *= -1;
        }
    }
}

void myfunc::bigInt::operator += (const long long& nr)  {
    (*this) += myfunc::bigInt(nr);
}

myfunc::bigInt myfunc::bigInt::operator + (const myfunc::bigInt& oth)  {
    myfunc::bigInt ans = (*this);
    ans += oth;
    return ans;
}

myfunc::bigInt myfunc::bigInt::operator + (const long long& nr)  {
    myfunc::bigInt ans = (*this);
    ans += bigInt(nr);
    return ans;
}

myfunc::bigInt myfunc::operator + (const long long& nr, const bigInt& oth)  {
    return bigInt(nr) + oth;
}

// Subtraction operator

void myfunc::bigInt::operator -= (const myfunc::bigInt& oth)  {
    if(oth.sign != this -> sign)  {
        this -> additionHelper(oth);
    }else{
        if(this -> absEqual(oth))  {
            *this = 0;
        }else if(this -> absGreater(oth))  {
            this -> subtractionHelper(oth);
        }else{
            this -> inverseSubtractionHelper(oth);
            this -> sign *= -1;
        }
    }
}

void myfunc::bigInt::operator -= (const long long& nr)  {
    (*this) -= myfunc::bigInt(nr);
}
myfunc::bigInt myfunc::bigInt::operator - (const myfunc::bigInt& oth)  {
    myfunc::bigInt ans = (*this);
    ans -= oth;
    return ans;
}
myfunc::bigInt myfunc::bigInt::operator - (const long long& nr)  {
    myfunc::bigInt ans = (*this);
    ans -= nr;
    return ans;
}

myfunc::bigInt myfunc::operator - (const long long& nr, const bigInt& oth)  {
    return bigInt(nr) - oth;
}
