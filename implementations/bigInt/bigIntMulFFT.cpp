#include "bigInt.h"

myfunc::complex<long double> giveAns(const long long& elem)  {
    return myfunc::complex<long double>(elem, 0);
}

myfunc::complex<long double> giveAns(const myfunc::complex<long double>& elem)  {
    return elem;
}

myfunc::complex<long double> wGet(int m)  {
    const long double PI = std::acos(-1);
    return std::cos(2.0 * PI / m) + std::sin(2.0 * PI / m) * myfunc::complex<long double>(0, 1);
}

template <typename T>
std::vector <myfunc::complex<long double>> fft(const std::vector <T>& A, const int& m, const int& start, const int& stepSize, const int& sign, const int& pointless)  {
    if(start >= pointless)  {
        return std::vector <myfunc::complex<long double>> ();
    }
    if(m == 1)  {
        return std::vector <myfunc::complex<long double>> (1, giveAns(A[start]));
    }
    myfunc::complex<long double> w1 = myfunc::wRoots[sign * m];

    int m2 = m / 2;
    auto F_even = fft(A, m2, start, (stepSize << 1), sign, pointless);
    auto F_odd = fft(A, m2, start + stepSize, (stepSize << 1), sign, pointless);
    std::vector <myfunc::complex<long double>> F(m, 0.0);
    myfunc::complex<long double> x(1.0, 0.0);

    for(int i = 0; i < m2;i++)  {
        multiplicationCount++;
        myfunc::complex<long double> evenGuy, oddGuy;
        if(i >= F_even.size())
            evenGuy = 0.0;
        else
            evenGuy = F_even[i];
        if(i >= F_odd.size())
            oddGuy = 0.0;
        else
            oddGuy = F_odd[i];
        if(i >= F_odd.size() && i >= F_even.size())
            return F;
        F[i] = evenGuy + x * oddGuy;
        F[i + m2] = evenGuy - x * oddGuy;
        x *= w1;
    }
    return F;
}

void toNextPow(int& m)  {
    int pow2 = 1;
    int originalM = m;
    while(m)  {
        m >>= 1;
        pow2 <<= 1;
    }
    m = pow2;
    if(originalM * 2 == pow2)
        m = originalM;
}

myfunc::bigInt myfunc::fftHelper(const myfunc::bigInt& x, const myfunc::bigInt& y)  {
    if(!myfunc::hasComputedRoots)  {
        for(int pow = 1;pow <= myfunc::maxDigits;pow *= 2)  {
            myfunc::wRoots[pow] = wGet(pow);
            myfunc::wRoots[-pow] = wGet(-pow);
        }
        myfunc::hasComputedRoots = true;
    }
    if(x.size() == 0 || y.size() == 0)  {
        return myfunc::bigInt(0);
    }
    std::vector <long long> aX, aY;
    aX = x.digits;
    aY = y.digits;
    int m = x.size() + y.size();
    toNextPow(m);
    int pointlessX = aX.size();
    while(aX.size() < m)
        aX.push_back(0);
    int pointlessY = aY.size();
    while(aY.size() < m)
        aY.push_back(0);
    const long double PI = std::acos(-1);
    myfunc::complex<long double> w = myfunc::wRoots[m];
    myfunc::complex<long double> wInv = myfunc::wRoots[-m];
    std::cerr << m << "\n";
    auto F_X = fft(aX, m, 0, 1, 1, pointlessX);
    auto F_Y = fft(aY, m, 0, 1, 1, pointlessY);

    std::vector <myfunc::complex<long double>> F(m);
    for(int i = 0;i < m;i++)
        F[i] = F_X[i] * F_Y[i];

    auto FInv = fft(F, m, 0, 1, -1, m);

    myfunc::bigInt C;
    std::vector <long long> P(m);
    for(int i = 0;i < m;i++)  {
        P[i] = (long long)round((1.0 / m * FInv[i].real));
    }

    while(P.size() && P.back() == 0)
        P.pop_back();


    long long remainder = 0LL, toPush = 0LL;
    for(int i = 0;i < P.size();i++)  {
        toPush = remainder + P[i];
        remainder = toPush / myfunc::bigInt::base;
        toPush %= myfunc::bigInt::base;
        C.push_back(toPush);
    }

    while(remainder)  {
        C.push_back(remainder % myfunc::bigInt::base);
        remainder /= myfunc::bigInt::base;
    }

    C.sign = x.sign * y.sign;

    return C;
}
