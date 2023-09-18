#include <bits/stdc++.h>

int N;
long long x1, y11, x2, y2;
long long ans;

int main()  {
    std::cin >> N >> x1 >> y11;
    long long frx, fry;
    frx = x1, fry = y11;
    for(int i = 1;i < N;i++)  {
        std::cin >> x2 >> y2;
        ans += (x1 * y2 - x2 * y11);
        x1 = x2, y11 = y2;
    }
    ans += (x2 * fry - frx * y2);
    if(ans < 0) {
        std::cout << "cw\n";
    }else std::cout << "ccw\n";
    return 0;
}