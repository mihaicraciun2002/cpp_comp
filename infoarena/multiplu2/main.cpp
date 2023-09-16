#include <bits/stdc++.h>

using namespace std;

const long long mod = 1e4;

long long N, K;
long long isSquare = 0;

// nr de divizori ai lui N
map <long long, int> t;
map <long long, int> d, sumd;
vector <long long> div1;

long long mul(long long a, long long n)  {
    long long ans = 1;
    a %= mod;
    while(n)  {
        if(n % 2LL)
            ans *= a, ans %= mod;
        a *= a;
        a %= mod;
        n /= 2LL;
    }
    return ((ans % mod) + mod) % mod;
}

int main()  {
    freopen("multiplu2.in", "r", stdin);
    freopen("multiplu2.out", "w", stdout);
    cin >> N >> K;
    long long sq = sqrt(N);
    if(sq * sq == N)  {
        isSquare = 1;
    }
    for(long long i = 1;i <= sq - isSquare;i++)  {
        if(N % i == 0)
            div1.push_back(i);
    }
    if(isSquare)  {
        div1.push_back(sq);
    }
    int sz = div1.size();
    for(int i = sz - 1 - isSquare;i >= 0;i--)  {
        div1.push_back(N / div1[i]);
    }
    t[N] = div1.size();
    d[1] = 1;
    sumd[1] = 1;
    t[1] = 1;
    for(int i = 1;i < div1.size();i++)  {
        long long x, y, auxs;
        x = div1[i];
        for(int j = i - 1;j >= 0;j--)  {
            y = div1[j];
            if(x % y == 0)  {
                t[x] = t[y] + 1;
                if(y % (x / y) != 0)
                    auxs = sumd[y] + d[x / y];
                else
                    auxs = sumd[y];
                auxs = (auxs % mod) + mod;
                auxs %= mod;
                d[x] = mul(t[x], K) - auxs;
                d[x] = (d[x] + mod) % mod;
                sumd[x] = d[x] + auxs;
                sumd[x] = (sumd[x] + mod) % mod;
            }
        }
    }
    cout << d[N];
    return 0;
}