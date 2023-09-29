#include "bigInt.h"

// Multiplication and division class for bigInt

// Karatsuba for multiplication
void addVec(std::vector <long long> &ans, const std::vector <long long> &x, const long long& factor, const int& zerosX,
    const int& startPosX, const int& endPosX)  {
    int desiredSize = endPosX - startPosX + 1 + zerosX;
    while(ans.size() < desiredSize)
        ans.push_back(0);
    int startPosition = zerosX;
    int endPosition = zerosX + endPosX - startPosX;
    int index = startPosition;
    long long remainder = 0LL, toPush = 0LL;
    long long remainderX = 0LL, toPushX = 0LL;
    for(index = startPosition;index <= endPosition || remainderX;index++)  {
        if(!(index >= startPosition && index <= endPosition))  {
            toPushX = remainderX % myfunc::bigInt::base;
            remainderX /= myfunc::bigInt::base;
        }else{
            toPushX = (x[index - zerosX + startPosX] * factor) + remainderX;
            remainderX = toPushX / myfunc::bigInt::base;
            toPushX %= myfunc::bigInt::base;
        }
        toPush = ans[index] + toPushX + remainder;
        remainder = toPush / myfunc::bigInt::base;
        toPush %= myfunc::bigInt::base;
        ans[index] = toPush;
    }

    while(remainder)  {
        if(ans.size() == index)  {
            ans.push_back(remainder % myfunc::bigInt::base);
            remainder /= myfunc::bigInt::base;
        }else{
            toPush = ans[index] + remainder;
            remainder = toPush / myfunc::bigInt::base;
            toPush %= myfunc::bigInt::base;
            ans[index] = toPush;
        }
        index++;
    }
}

void karatsuba (std::vector <long long> &ans, const std::vector <long long>& x, const std::vector <long long>& y,
    const int& xL, const int& xR, const int& yL, const int& yR)  {

    if(xR < xL)  {
        return;
    }
    if(yR < yL)  {
        return;
    }
    if(xR - xL + 1 == 1)  {
        std::cerr << "Number: ";
        for(int i = (int)ans.size() - 1;i >= 0;i--)  {
            std::cerr << ans[i] << " ";
        }
        std::cerr << "\n";
        addVec(ans, y, x[xL], xL + yL, yL, yR);
        std::cerr << x[xL] << " " << y[yL] << "\n";
        std::cerr << xL << " " << xR << " " << yL << " " << yR << "\n";
        std::cerr << "Number after: ";
        for(int i = (int)ans.size() - 1;i >= 0;i--)  {
            std::cerr << ans[i] << " ";
        }
        std::cerr << "\n\n";
        return;
    }
    const int m = std::max(xR - xL + 1, yR - yL + 1);
    const int m2 = (m >> 1);
    const int xMiddle = std::min(xL + m2 - 1, xR);
    const int yMiddle = std::min(yL + m2 - 1, yR);
    karatsuba(ans, x, y, xL, xMiddle, yL, yMiddle);
    karatsuba(ans, x, y, xL, xMiddle, yMiddle + 1, yR);
    karatsuba(ans, x, y, xMiddle + 1, xR, yL, yMiddle);
    karatsuba(ans, x, y, xMiddle + 1, xR, yMiddle + 1, yR);
}

myfunc::bigInt myfunc::karatsubaHelper (const myfunc::bigInt& x, const myfunc::bigInt& y)  {
    if(x.size() == 0 || y.size() == 0)  {
        return myfunc::bigInt(0);
    }
    std::vector <long long> ans;
    karatsuba(ans, x.digits, y.digits, 0, x.size() - 1, 0, y.size() - 1);
    myfunc::bigInt ansBigInt;
    ansBigInt.digits = ans;
    ansBigInt.sign = x.sign * y.sign;
    return ansBigInt;
}

myfunc::bigInt myfunc::bigInt::operator * (const myfunc::bigInt& oth)  {
    return karatsubaHelper((*this), oth);
}
