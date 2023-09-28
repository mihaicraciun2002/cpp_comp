#include "bigInt.h"

class myfunc::div  {
    myfunc::bigInt quotient;
    myfunc::bigInt remainder;
};

// digit size and sign
const int& myfunc::bigInt::size () const {
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
void myfunc::bigInt::operator = (const bigInt& oth)  {
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
myfunc::bigInt::bigInt() {
    sign = 1;
    std::vector <long long> digits = std::vector <long long>();
}

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
    this -> sign = sign;
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
            isFirst = false;
        }
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
    return (this -> sign == sign && oth.size() == this -> size() &&
        oth.digits == this -> digits);
}

bool myfunc::bigInt::operator >= (const bigInt &oth) const  {
    return !((*this) < oth);
}

bool myfunc::bigInt::operator <= (const bigInt &oth) const  {
    return !((*this) > oth);
}


// Addition operator + opposite sign operator

myfunc::bigInt myfunc::operator - (const bigInt &oth)  {
    bigInt ans = oth;
    ans.setSign(-ans._sign());
    return ans;
}

void myfunc::bigInt::operator += (const bigInt &oth) {
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

void myfunc::bigInt::operator += (const long long &nr)  {
    (*this) += bigInt(nr);
}

myfunc::bigInt myfunc::bigInt::operator + (const bigInt &oth)  {
    myfunc::bigInt ans = (*this);
    ans += oth;
    return ans;
}

myfunc::bigInt myfunc::bigInt::operator + (const long long &nr)  {
    myfunc::bigInt ans = (*this);
    ans += bigInt(nr);
    return ans;
}
