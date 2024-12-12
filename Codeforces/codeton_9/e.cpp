#include <bits/stdc++.h>


const int maxn = 1e6;

long long kk[maxn];

const long long mod = 998244353;

inline void solve(){
    int n;
    std::cin >> n;
    if(n == 2){
        std::cout << "1\n";
        return;
    }
    int moves = n - 2;
    long long ans = 1;
    long long sum = 1;

    kk[0] = 1;
    for(int b = 1;b <= moves - 2;b++){
        kk[b] = 1 + (n - b) * sum;
        sum += kk[b];
        kk[b] = sum;
        kk[b] %= mod;
        sum %= mod;
    }

    for(int t = 1;t <= moves;t++){
        ans += 1;

        if(1 + t <= moves)
            ans += (1 + t) * (kk[moves - 1 - t]);
        ans %= mod;
        continue;

        for(int s = 1;s + t <= moves;s++){
            ans += (1 + t) * kk[moves - s - t];
            ans %= mod;
        }
    } 
    std::cout << ans << "\n";
    return;
}


int main(){
    int t;
    std::cin >> t;

    while(t--){
        solve();
    }
    return 0;
}