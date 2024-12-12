#include <bits/stdc++.h>

const int maxn = 2e5 + 5;

bool ciur[maxn * 3];
std::map <int, bool> prim;

inline void build_ciur()  {
    ciur[1] = 1;
    for(int i = 2;i < maxn;i++){
        if(ciur[i]){
            continue;
        }
        prim[i] = true;
        for(long long j = 1LL * i * i;j < maxn;j += 1LL * i){
            ciur[j] = 1;
        }
    }
}

inline void solve(){
    int n;
    std::cin >> n;
    if(n < 5){
        std::cout << "-1\n";
        return;
    }
    for(int i = 1;i <= n;i += 2)  {
        if(i == 5){
            continue;
        }
        std::cout << i << " ";
    }
    std::cout << "5 4 ";
    for(int i = 2;i <= n;i += 2)  {
        if(i == 4){
            continue;
        }
        std::cout << i << " ";
    }
    std::cout << "\n";
}

int main()  {
    int t;
    std::cin >> t;
    build_ciur();
    while(t--)  {
        solve();
    }
    return 0;
}