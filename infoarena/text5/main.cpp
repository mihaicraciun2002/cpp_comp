#include <cstdio>
#include <iostream>
#include <stack>
#include <algorithm>

const int maxA = 99 + 1;
const int maxB = 999 + 1;
const int maxn = 1e6 + 1;

int N;
char s[maxn];



inline int decod(int nrCifre, int i)  {
    int nr = 0;
    while(nrCifre--)
        nr = nr * 10 + s[i++] - '0';
    return nr;
}

#define MORE_TESTS 0

inline void solve()  {
    scanf("%d%s", &N, s);
}

int main()  {
    freopen("text5.in", "r", stdin);
    freopen("text5.out", "w", stdout);
    #if MORE_TESTS
    int T;
    scanf("%d", &T);
    while(T--)  {
        solve();
    }
    #else
    solve();
    #endif
    return 0;
}