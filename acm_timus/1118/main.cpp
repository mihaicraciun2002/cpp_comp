#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6 + 1;
long long s[maxn];
bool prim[maxn];
int firstPrime[maxn];

int main()  {
    prim[1] = 1;
    for(int i = 2;i * i < maxn;i++)
        if(!prim[i])  {
            for(int j = i * i;j < maxn;j += i)  {
                if(!prim[j])
                    firstPrime[j] = i;
                prim[j] = 1;
            }
        }
    s[1] = 1;
    for(int i = 2;i < maxn;i++)  {
        if(s[i])
            continue;
        if(!prim[i])  {
            s[i] = 1 + i;
            continue;
        }
        int powSz = 0, cp = i;
        int p = firstPrime[i];
        long long myPow = 1;
        while(cp && cp % p == 0)
            cp /= p, powSz++, myPow *= p;
        s[i] = s[i / p] + myPow * s[i / myPow];
    }
    int L, R;
    #if 1
    cin >> L >> R;
    #else
    L = 24, R = 28;
    #endif
    double mini = 1.0 * s[L] / L;
    int miniIndex = L;
    for(int i = L;i <= R;i++)
        if(mini > 1.0 * s[i] / i)  {
            mini = 1.0 * s[i] / i;
            miniIndex = i;
        }
    cout << miniIndex << "\n";
    return 0;
}