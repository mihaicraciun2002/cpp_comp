#include <iostream>
#include <cmath>

long a, m, n;
double d, o, w;

int main()  {
    std::cin >> n >> m;
    a = 0;
    w = 0;
    o = 0;

    while(1)  {
        a++;
        d = 1.0 * m / (a * 2 - 1);
        if(w + d >= 1.0 * n)
            break;
        w = w + d;
        o = o + m;
    }
    d = n - w;
    o = o + d * (a * 2 - 1);
    std::cout << (long)(ceil(o)) << "\n";
    return 0;
}