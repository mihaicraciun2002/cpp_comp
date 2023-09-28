#define USE_MODE 1
#if USE_MODE
#include <chrono>
#include <iostream>
std::chrono::time_point<std::chrono::high_resolution_clock> started_time;
std::chrono::time_point<std::chrono::high_resolution_clock> finished_time;
inline void endTimeCHRONO()  {
    finished_time = std::chrono::high_resolution_clock::now(); std::cerr << "\nTime elapsed (s):\n";
    std::cerr << (double)std::chrono::duration_cast<std::chrono::milliseconds>(finished_time - started_time).count() / 1000.0 << "\n";
}
#endif
// INCLUDES (cstdio and iostream already included)

#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <cassert>
#include <algorithm>

// START CODE HERE

#define LL long long
#define quotient first
#define remainder second

int instances;

class bigInt  {
    private:
    std::vector <long long> digits;
    bool isReversed = false;
    int finishZero = 0;
    mutable long long sign = 1;
    const static long long base = 1e9;
    public:

    inline bool operator <=(const bigInt& oth) const {
        return (*this == oth) || (*this < oth);
    }

    inline bool operator >=(const bigInt& oth) const {
        return (*this == oth) || (*this > oth);
    }

    inline bool operator >(const bigInt& oth) const {
        return !(*this < oth);
    }

    inline bool operator ==(const bigInt& oth) const {
        return (sign == oth.sign && digits == oth.digits);
    }

    inline bool operator <(const bigInt& oth) const {
        if(digits.size() == 0 && oth.digits.size() == 0)  {
            return false;
        }
        if(sign * (int)digits.size() < oth.sign * (int)oth.digits.size())  {
            return true;
        }
        if(sign * (int)digits.size() > oth.sign * (int)oth.digits.size())  {
            return false;
        }

        int index = digits.size() - 1;
        while(index >= 0)  {
            if(digits[index] * sign < oth.digits[index] * oth.sign)  {
                return true;
            }
            if(digits[index] * sign > oth.digits[index] * oth.sign)  {
                return false;
            }
            index--;
        }
        return false;
    }

    private:
    // Special comparator made for dealing with division
    inline bool specialLess(const bigInt& oth) const  {
        assert(isReversed);
        int sizeThis = digits.size() - finishZero;
        if(sizeThis < oth.digits.size())
            return true;
        if(sizeThis > oth.digits.size())
            return false;
        if(oth.digits.size() == 0 && sizeThis == 0)  {
            return false;
        }
        int indexOth = oth.digits.size() - 1;
        int indexThis = finishZero;
        assert(sizeThis == oth.digits.size());
        while(indexOth >= 0)  {
            if(digits[indexThis] > oth.digits[indexOth])  {
                return false;
            }
            if(digits[indexThis] < oth.digits[indexOth])  {
                return true;
            }
            indexThis++;
            indexOth--;
        }
        return false;
    }

    inline void substract(const bigInt& oth)  {
        int sizeThis = (int)digits.size() - finishZero;
        int indexThis = (int)digits.size() - 1;
        int indexOth = 0;
        long long rest = 0;
        while(indexOth < oth.digits.size())  {
            long long toPush = (digits[indexThis] - oth.digits[indexOth] - rest);
            if(toPush < 0)
                rest = 1, toPush += base;
            else
                rest = 0;
            digits[indexThis] = toPush;
            indexThis--;
            indexOth++;
        }
        while(rest)  {
            long long toPush = (digits[indexThis] - rest);
            if(toPush < 0)
                rest = 1, toPush += base;
            else
                rest = 0;
            digits[indexThis] = toPush;
            indexThis--;
        }
        while(finishZero < digits.size() && digits[finishZero] == 0)
            finishZero++;
    }

    public:

    // Main division operator
    inline std::pair<bigInt, bigInt> operator /(const bigInt& oth) const  {
        // assert(oth.sign == 1 && sign == 1);
        bigInt ans;
        bigInt aux;
        aux.isReversed = true;
        bigInt othMul;

        int prev = digits.size() - 1;
        for(int index = digits.size() - 1;index >= 0;index--)  {
            aux.digits.push_back(digits[index]);
            if(prev - index + 1 >= oth.digits.size())  {
                // int digit = 0;
                // while(digit + 1 < 10 && !(aux.specialLess(othMul[digit + 1])))
                //     digit++;
                LL digit = 0;
                LL r = -1;
                LL pas = 1LL << 30;
                while(pas)  {
                    if((r + pas < base) && !(aux.specialLess(oth.mulDigit(r + pas))))
                        r += pas;
                    pas >>= 1;
                }
                digit = r;

                aux.substract(oth.mulDigit(digit));
                if(ans.digits.size() > 0 || digit > 0)
                    ans.digits.push_back(digit);
            }
        }
        bigInt remainder;
        for(int i = aux.digits.size() - 1;i >= aux.finishZero;i--)
            remainder.digits.push_back(aux.digits[i]);
        std::reverse(ans.digits.begin(), ans.digits.end());
        return std::make_pair(ans, remainder);
    }

    inline bigInt pow(const int& exp)  {
        bigInt ans = 1;
        bigInt aux = *this;
        int expCp = exp;
        while(expCp)  {
            if(expCp % 2)
                ans *= aux;
            aux *= aux;
            expCp /= 2;
        }
        return ans;
    }

    inline void operator *=(const LL& no)  {
        *this = *this * no;
    }

    inline void operator *=(const bigInt& oth)  {
        *this = *this * oth;
    }

    inline bigInt operator *(const LL& no) const  {
        return *this * bigInt(no);
    }

    private:

    inline bigInt mulDigit(const LL& no) const {
        bigInt ans;
        LL rest = 0;
        for(int i = 0;i < digits.size();i++)  {
            LL toPush = digits[i] * no + rest;
            rest = toPush / base;
            toPush %= base;
            ans.digits.push_back(toPush);
        }
        while(rest)  {
            LL toPush = rest;
            rest = toPush / base;
            toPush %= base;
            ans.digits.push_back(toPush);
        }
        return ans;
    }

    public:

    // Main multiplication operator
    inline bigInt operator *(const bigInt& oth) const  {
        if(oth == bigInt(0))  {
            return bigInt(0);
        }
        if(*this == bigInt(0))  {
            return bigInt(0);
        }
        bigInt ans;
        bigInt aux;
        int index = 0;

        bigInt helper;

        int desiredSize;
        int zeroed = 0;
        while(index < digits.size())  {
            LL digit = digits[index];
            desiredSize = index + 1;
            helper = oth.mulDigit(digit);
            for(int i = index;i < index + helper.digits.size();i++)  {
                if(aux.digits.size() <= i)  {
                    aux.digits.push_back(0);
                }
                aux.digits[i] = helper.digits[i - index];
            }
            if(digit != 0)
                ans += aux;
            if(aux.digits.size() < desiredSize)
                aux.digits.push_back(0);
            aux.digits[index] = 0;
            index++;
        }
        ans.sign = oth.sign * sign;
        return ans;
    }

    inline void operator -=(const bigInt& oth)  {
        if(oth.sign != sign)  {
            int csign = sign;
            int cosign = oth.sign;
            sign = 1;
            oth.sign = 1;
            *this += oth;
            sign = csign;
            oth.sign = cosign;
            return;
        }else{
            int csign = sign;
            int cosign = oth.sign;
            sign = 1;
            oth.sign = 1;
            if(*this < oth)  {
                *this = oth - *this;
                sign = -csign;
                oth.sign = cosign;
                if((*this).digits.size() == 0)
                    sign = 1;
                return;
            }
            sign = csign;
            oth.sign = cosign;
        }
        LL rest = 0;int index = 0;
        while(index < oth.digits.size())  {
            LL toPush = (digits[index] - oth.digits[index] - rest);
            if(toPush < 0)
                rest = 1, toPush += base;
            else
                rest = 0;
            digits[index] = toPush;
            index++;
        }
        while(rest && index < digits.size())  {
            LL toPush = digits[index] - rest;
            if(toPush < 0)
                rest = 1, toPush += base;
            else
                rest = 0;
            digits[index] = toPush;
            index++;
        }
        while(digits.size() && digits.back() == 0)
            digits.pop_back();
        if(digits.size() == 0)
            sign = 1;
    }

    inline bigInt operator -(const bigInt& oth) const {
        bigInt ans = *this;
        ans -= oth;
        return ans;
    }

    inline void operator +=(const LL& no)  {
        *this += bigInt(no);
    }

    inline void operator +=(const bigInt& oth)  {
        if(sign != oth.sign)  {
            int csign = sign;
            int cosign = oth.sign;
            sign = oth.sign = 1;
            if(*this >= oth)  {
                *this -= oth;
                sign = csign;
                if(digits.size() == 0)
                    sign = 1;
            }else{
                *this = oth - (*this);
                sign = cosign;
                if(digits.size() == 0)
                    sign = 1;
            }
            oth.sign = cosign;
            return;
        }
        LL rest = 0;
        int index = 0;
        while(index < digits.size() && index < oth.digits.size())  {
            LL toPush = (digits[index] + oth.digits[index] + rest);
            rest = toPush / base;
            toPush %= base;
            digits[index] = toPush;
            index++;
        }
        while(index < digits.size())  {
            LL toPush = (digits[index] + rest);
            rest = toPush / base;
            toPush %= base;
            digits[index] = toPush;
            index++;
        }
        while(index < oth.digits.size())  {
            LL toPush = (oth.digits[index] + rest);
            rest = toPush / base;
            toPush %= base;
            digits.push_back(toPush);
            index++;
        }
        while(rest)  {
            digits.push_back(rest % base);
            rest /= base;
        }
        if(digits.size() == 0)
            sign = 1;
    }

    inline bigInt operator +(const bigInt& oth) const {
        bigInt ans = *this;
        ans += oth;
        return ans;
    }

    inline bigInt operator +(const LL& no) const {
        return *this + bigInt(no);
    }

    inline void operator =(const LL& no)  {
        bigInt helper = bigInt(no);
        digits = helper.digits;
        sign = helper.sign;
    }

    inline void operator =(const bigInt& oth)  {
        digits = oth.digits;
        sign = oth.sign;
    }

    inline std::string show() const {
        std::string ans;
        if(sign == -1)
            ans.push_back('-');
        if(digits.size() == 0)  {
            ans.push_back('0');
            return ans;
        }

        for(int i = digits.size() - 1;i >= 0;i--)  {
            std::string helper = std::to_string(digits[i]);
            if(i < digits.size() - 1)
                for(int index = 0;index < 9 - helper.size();index++)
                    ans.push_back('0');
            ans.append(helper);
        }
        return ans;
    }

    bigInt(const LL& no)  {
        digits.clear();
        LL cno = no;
        if(cno < 0)
            sign = -1, cno = -cno;
        while(cno)  {
            digits.push_back(cno % base);
            cno /= base;
        }
        instances++;
    }
    bigInt(const bigInt& oth)  {
        digits = oth.digits;
        sign = oth.sign;
        instances++;
    }
    bigInt(){instances++;}
    inline int size()  {
        return (int)digits.size();
    }
};

inline bigInt operator +(const LL& no, const bigInt& op)  {
    return op + no;
}
inline bigInt operator *(const LL& no, const bigInt& op)  {
    return op * no;
}

template <typename T>
class myPair  {
    T first;
    T second;
};

myPair <int> bruh;



std::pair <bigInt, bigInt> euclid(const bigInt& a, const bigInt& b)  {
    if(b == bigInt(0))  {
        return std::make_pair(1, 0);
    }
    bigInt x, y;
    std::pair <bigInt, bigInt> r = (a / b);
    std::pair <bigInt, bigInt> rest = euclid(b, r.remainder);
    x = rest.second;
    y = rest.first; y -= (r.quotient * x);
    return std::make_pair(x, y);
}

// END CODE HERE

int main()  {
    #if USE_MODE
    started_time = std::chrono::high_resolution_clock::now(); freopen("aux.in", "r", stdin);  freopen("aux.out", "w", stdout);
    #endif

// START CODE HERE


    long long N;
    long long a[2001];
    std::cin >> N;
    for(int i = 1;i <= N;i++)  {
        std::cin >> a[i];
    }

    #if 0
    N = 2000;
    for(int i = 1;i <= 1999;i++)
        a[i] = 0;
    a[2000] = 1;
    #endif

    bigInt S;
    bigInt powN[2001];
    bigInt powN1[2001];

    powN[0] = 1;
    powN1[0] = 1;
    for(int i = 1;i <= N;i++)  {
        powN[i] = powN[i - 1] * N;
        powN1[i] = powN1[i - 1] * (N - 1);
    }

    for(int i = 1;i <= N;i++)  {
        S += a[i] * powN[i - 1] * powN1[N + 1 - i];
    }


    bigInt Sc = S;

    bigInt A, B;
    A = powN1[N];
    B = powN[N];

    auto P = euclid(B, A);
    auto& B1 = P.first;
    S = (S / A).remainder;
    S = A - S;
    S *= B1;
    S = (S / A).remainder;

    bigInt X;
    X = ((S * powN[N] + Sc) / powN1[N]).quotient;
    if(X == bigInt(0))  {
        X = powN[N];
    }
    std::cout << X.show() << "\n";


// END CODE HERE

    #if USE_MODE
    endTimeCHRONO();
    #endif
    return 0;
}
