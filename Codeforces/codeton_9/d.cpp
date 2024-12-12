#include <bits/stdc++.h>

bool ver(const std::vector<int> &v, int n){
    for(int i = 1;i < n;i++){
        for(int j = i + 1;j <= n;j++){
            int aa = std::gcd(i, j);
            int bb = std::gcd(v[i], v[j]);
            if(v[aa] == bb){
                std::cerr << i << " " << j << "\n";
                return false;
            }
        }
    }
    return true;
}

int cnt(int nr){
    if(nr == 1){
        return 0;
    }
    int ans = 0;
    for(int i = 2;i * i <= nr;i++){
        while(nr % i == 0)
            nr /= i, ans++;
    }
    if(nr > 1){
        ans++;
    }
    return ans;
}

inline void solve(){
    int n, m;
    std::cin >> n >> m;
    std::vector <int> s(m);
    std::vector <int> ans(n + 1);
    for(int i = 0;i < m;i++){
        std::cin >> s[i];
    }
    std::sort(s.begin(), s.end());
    std::reverse(s.begin(), s.end());
    ans[1] = s[0];
    for(int i = 2;i <= n;i++){
        int aa = cnt(i);
        if(aa + 1 > m){
            std::cout << "-1\n";
            return;
        }
        ans[i] = s[aa];
    }
    for(int i = 1;i <= n;i++){
        std::cout << ans[i] << " ";
    }
    // std::cerr << ver(ans, 15);
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