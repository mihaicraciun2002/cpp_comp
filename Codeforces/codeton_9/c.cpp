#include <bits/stdc++.h>

inline void solve(){
    int x;long long m;
    std::cin >> x >> m;
    int pow_t = 1;
    while(pow_t <= x){
        pow_t *= 2;
    }
    int nr = 0;
    pow_t = std::min((long long)pow_t, m);
    for(int y = 1;y <= pow_t;y++){
        int div = (x ^ y);
        if(div == 0){
            continue;
        }
        if(x % div == 0 || y % div == 0){
            nr++;
        }
    }
    std::cout << nr << "\n";
}

int main(){
    int t;
    std::cin >> t;
    while(t--){
        solve();
    }
    return 0;
}