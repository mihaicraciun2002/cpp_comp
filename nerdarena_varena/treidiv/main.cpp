#include <bits/stdc++.h>

using namespace std;

const int maxval = 1e3 + 1;
bool vf[maxval];

inline static void ciur()  {
    vf[1] = 1;
    for(int i = 2;i * i < maxval;i++)  {
        if(!vf[i])
            for(int j = i * i;j < maxval;j += i)
                vf[j] = 1;
    }
}

namespace mine {
    inline int sqrt(int x)  {
        int r = -1;
        int pas = 1 << 10;
        while(pas)  {
            if((r + pas) * (r + pas) <= x)
                r += pas;
            pas >>= 1;
        }
        return r;
    }
}
int main()  {
    freopen("treidiv.in", "r", stdin);
    freopen("treidiv.out", "w", stdout);
    ciur();
    int N;
    scanf("%d\n", &N);
    int ans = 0;
    for(int i = 0;i < N;i++)  {
        int x;
        scanf("%d", &x);
        int ax = mine::sqrt(x);
        if(ax * ax == x && !vf[ax])
            ans++;
    }
    cout << ans << "\n";
    return 0;
}