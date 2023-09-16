#include <bits/stdc++.h>

using namespace std;

long long N;
long long P;

int main()  {
    freopen("suma.in", "r", stdin);
    freopen("suma.out", "w", stdout);
    cin >> N >> P;
    long long N1, N21, Nc;
    Nc = N;
    N1 = N + 1;
    N21 = 2LL * N + 1;
    long long sMare, sMic;
    if(Nc % 2 == 0)
        Nc /= 2LL;
    else N1 /= 2LL;
    sMic = Nc * N1;
    sMare = sMic;
    if(sMare % 3LL == 0)
        sMare /= 3LL;
    else
        N21 /= 3LL;
    sMic %= P;
    sMare %= P;
    sMare *= N21;
    sMare %= P;
    sMare -= sMic;
    sMare = (sMare + P) % P;
    cout << sMare;
    return 0;
}