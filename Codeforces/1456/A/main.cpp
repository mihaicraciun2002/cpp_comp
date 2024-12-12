#include <bits/stdc++.h>

inline void solve(){
    int n, p, k;
    std::cin >> n >> p >> k;
    std::string s;
    std::cin >> s;
    int x, y;
    std::cin >> x >> y;
    std::vector <int> dp(n, 0);
    for(int start = n - 1;start >= p - 1;start--){
        int nxt = start + k;
        if(nxt <= n - 1){
            dp[start] = dp[nxt];
        }
        if(s[start] == '0'){
            dp[start] += x;
        }
    }
    for(int start = n - 1;start >= p - 1;start--){
        dp[start] += y * (start - p + 1);
    }
    int ans = dp[n - 1];
    for(int start = n - 1;start >= p - 1;start--){
        ans = std::min(ans, dp[start]);
    }
    std::cout << ans << "\n";
}

int main(){
    int t;
    std::cin >> t;
    while(t--){
        solve();
    }
    return 0;
}