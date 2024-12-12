#include <bits/stdc++.h>

struct cmp{
    bool operator()(const std::pair<int, int>a, const std::pair<int, int>b) const {
        return a.second > b.second;
    }
};

inline void solve(){
    int n, m, L;
    std::cin >> n >> m >> L;
    std::vector <std::pair <int, int>> hurdles;
    int start_hurdle = 1;
    for(int i = 1;i <= n;i++){
        int l, r;
        std::cin >> l >> r;
        hurdles.push_back(std::make_pair(l, r));
    }
    int curr_pow = 1;
    std::vector <std::pair <int, int>> powerups;
    int powerup_idx = 0;
    for(int i = 1;i <= m;i++){
        int pos, v;
        std::cin >> pos >> v;
        powerups.push_back(std::make_pair(pos, v));
    }
    std::multiset <std::pair <int, int>, cmp> ms;
    int ans = 0;
    for(int i = 0;i < n;i++)  {
        int start = hurdles[i].first;
        int length = hurdles[i].second - hurdles[i].first + 1;
        while(powerup_idx < powerups.size() && powerups[powerup_idx].first < start){
            ms.insert(powerups[powerup_idx]);
            powerup_idx++;
        }
        if(curr_pow > length){
            continue;
        }
        while(curr_pow <= length && !ms.empty()){
            auto ms_top = ms.begin();
            curr_pow += (*ms_top).second;
            ans++;
            ms.erase(ms_top);
        }
        if(curr_pow <= length){
            std::cout << "-1\n";
            return;
        }
    }
    std::cout << ans << "\n";
}

int main()  {
    int t;
    std::cin >> t;
    while(t--)  {
        solve();
    }
    return 0;
}