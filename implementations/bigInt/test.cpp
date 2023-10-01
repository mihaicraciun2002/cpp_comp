#include "bigInt.h"
#include <iostream>

int main()  {
    myfunc::bigInt a, b;
    a = 20080000004100LL, b = 30040000000007000LL;
    std::cerr << a << " * " << b << "\n";
    a *= a;
    b *= b;
    a *= a;
    b *= b;
    a *= a;
    b *= b;
    a *= a;
    b *= b;
    std::cerr << (a * b) << "\n";
    return 0;
}
