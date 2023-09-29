#include "bigInt.h"

// Multiplication and division class for bigInt

// Karatsuba for multiplication
void addVec(std::vector <long long> &ans, const std::vector <long long> &x, const int& zerosX)  {
}

std::vector <long long> karatsuba (const std::vector <long long>& x, const std::vector <long long>& y,
    const int& xL, const int& xR, const int& yL, const int& yR)  {
    std::vector <long long> ans;
    if(xR > xL)  {
        return std::vector <long long> ();
    }
    if(yR > yL)  {
        return std::vector <long long> ();
    }
    if(xR - xL + 1 == 1)  {
        long long remainder = 0LL;
        long long toPush = 0LL;
        int index = yL;
        return ans;
    }
    const int m = std::max(xR - xL + 1, yR - yL + 1);
    const int m2 = (m >> 1);
    const int xMiddle = std::min(xL + m2, xR);
    const int yMiddle = std::min(yL + m2, yR);
    std::vector <long long> z0, z1_1, z1_2, z2;
    z0 = karatsuba(x, y, xL, xMiddle, yL, yMiddle);
    z1_1 = karatsuba(x, y, xL, xMiddle, yMiddle + 1, yR);
    z1_2 = karatsuba(x, y, xMiddle + 1, xR, yL, yMiddle);
    z2 = karatsuba(x, y, xMiddle + 1, xR, yMiddle + 1, yR);
}

myfunc::bigInt myfunc::karatsubaHelper (const myfunc::bigInt& x, const myfunc::bigInt& y)  {

}

myfunc::bigInt myfunc::bigInt::operator * (const myfunc::bigInt& oth)  {
    return karatsubaHelper((*this), oth);
}
