#include <bits/stdc++.h>

using namespace std;

const int maxn = 3e4 + 1;
const int maxconf = (1 << 7);

int N;
int divizori[] = {2, 3, 7, 11, 19, 23, 37};
int v[maxn];
int d[maxconf];

int main()  {
    freopen("poly.in", "r", stdin);
    freopen("poly.out", "w", stdout);
    scanf("%d", &N);
    for(int i = 1;i <= N;i++)
        scanf("%d", &v[i]);
    int S = 0;
    for(int i = 1;i <= N;i++)  {
        int conf = 0;
        for(int div = 6;div >= 0;div--)  {
            conf <<= 1;
            if(v[i] % divizori[div] == 0)
                conf |= 1;
        }
        if(conf == 0)  {
            S += 1;
            d[0] = S;
            continue;
        }
        for(int cnfNeg = 0;cnfNeg < maxconf;cnfNeg++)  {
            if(!(cnfNeg & conf))
                d[conf] = max(d[conf], d[cnfNeg] + 1);
        }
        S = max(S, d[conf]);
    }
    cout << S;
    return 0;
}