#include "bigInt.h"
#include <iostream>

int main()  {
    myfunc::bigInt a = myfunc::bigInt(2);// = myfunc::bigInt(0);
    std::cout << "bruh: " << a.digits[0] << "\n";
    // std::cout << a << "\n";
    return 0;
}
