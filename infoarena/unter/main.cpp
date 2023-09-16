#include <bits/stdc++.h>

using namespace std;

inline void solve()  {
    int n, d;
    scanf("%d%d", &n, &d);
    int po10 = 1;
    for(int i = 1;i <= d;i++)
        po10 *= 10;
    long long first;
    int a, b;
    scanf("%d.%d", &a, &b);
    first = 1LL * (a * po10 + b);
    bool ok = 1;
    for(int i = 2;i <= n;i++)  {
        scanf("%d.%d", &a, &b);
        long long nn = 1LL * (a * po10 + b);
        if((first + 1) * (i - 1) + 5 * po10 <= nn * i or
            first * (i - 1) + 1 * po10 >= nn * i + 1)
                ok = 0;
/*         if(nn == 500)  {
            cerr << first << " " << nn * i << "\n";
            cerr << (first + 1) * (i - 1) + 5 * po10 << " " <<
                first * (i - 1) + 1 * po10 << "\n";
        } */
        first = nn;
    }
    if(ok == 1)
        cout << "DA\n";
    else
        cout << "NU\n";
}

int main()  {
    freopen("unter.in", "r", stdin);
    freopen("unter.out", "w", stdout);
    int t;
    scanf("%d", &t);
    while(t--){solve();}
    return 0;
}