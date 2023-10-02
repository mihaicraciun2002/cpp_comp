#include "bigInt.h"
#include <iostream>
#include <chrono>

int main()  {
    #if 0
    myfunc::bigInt a, b;
    a = 20080000004100LL, b = 30040000000007000LL;
    std::cerr << a * b << "\n";

    #else
std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    myfunc::bigInt n = 2000;
    myfunc::bigInt a[2001];
    for(int i = 1;i < 2000;i++)
        a[i] = 0;
    a[2000] = 1;
    myfunc::bigInt powN[2001], powN1[2001];
    powN[0] = 1;
    powN1[0] = 1;
    for(int i = 1;i <= 2000;i++)  {
        powN[i] = powN[i - 1] * n;
    }
    freopen("test.out", "w", stdout);
    std::cout << powN[1000] << "\n";
    std::cerr << multiplicationCount << "\n";
std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
std::cerr << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
    return 0;
    #endif
}
