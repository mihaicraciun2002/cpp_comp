#include "bigInt.h"

std::complex <double> giveAns(const long long& elem)  {
    return std::complex <double> {elem, 0};
}

std::complex <double> giveAns(const std::complex <double>& elem)  {
    return elem;
}

std::complex <double> wGet(int m)  {
    const double PI = std::acos(-1);
    return std::cos(2.0 * PI / m) + std::complex <double> {0, 1} * std::sin(2.0 * PI / m);
}

template <typename T>
std::vector <std::complex <double>> fft(std::vector <T>& A, int m, std::complex <double> w, int sign)  {
    if(m == 1)  {
        return std::vector <std::complex <double>> (1, giveAns(A[0]));
    }
    std::complex <double> w1 = wGet(m * sign);
    std::vector <T> A_even(m / 2), A_odd(m / 2);
    for(int i = 0;i <= m - 2;i += 2)
        A_even[i / 2] = A[i], A_odd[i / 2] = A[i + 1];
    auto F_even = fft(A_even, m / 2, w * w, sign);
    auto F_odd = fft(A_odd, m / 2, w * w, sign);
    std::vector <std::complex <double>> F(m);
    std::complex <double> x(1.0, 0.0);
    for(int i = 0; i < m / 2;i++)  {
        F[i] = F_even[i] + x * F_odd[i];
        F[i + m / 2] = F_even[i] - x * F_odd[i];
        x *= w;
    }
    return F;
}

void toNextPow(int& m)  {
    int pow2 = 1;
    int originalM = m;
    while(m)  {
        m /= 2;
        pow2 *= 2;
    }
    m = pow2;
    if(originalM * 2 == pow2)
        m = originalM;
}

myfunc::bigInt myfunc::fftHelper(const myfunc::bigInt& x, const myfunc::bigInt& y)  {
    if(x.size() == 0 || y.size() == 0)  {
        return myfunc::bigInt(0);
    }
    std::vector <long long> aX, aY;
    aX = x.digits;
    aY = y.digits;
    int m = x.size() + y.size();
    toNextPow(m);
    while(aX.size() < m)
        aX.push_back(0);
    while(aY.size() < m)
        aY.push_back(0);
    const double PI = std::acos(-1);
    std::complex <double> w = wGet(m);
    std::complex <double> wInv = wGet(-m);
    auto F_X = fft(aX, m, w, 1);
    auto F_Y = fft(aY, m, w, 1);

    std::vector <std::complex <double>> F(m);
    for(int i = 0;i < m;i++)
        F[i] = F_X[i] * F_Y[i];
    auto FInv = fft(F, m, wInv, -1);
    myfunc::bigInt C;
    std::vector <long long> P(m);
    for(int i = 0;i < m;i++)  {
        P[i] = (long long)round((1.0 / (double)m * FInv[i]).real());
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
