#include <bits/stdc++.h>

inline void solve(){
    int n;
    std::cin >> n;
    for(int i = 1;i <= n;i++){
        std::cout << 2 * i - 1 << " ";
    }
    std::cout << "\n";
}

int main(){
    int t;
    std::cin >> t;
    while(t--){
        solve();
    }
    return 0;
}