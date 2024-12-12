#include <bits/stdc++.h>

inline void solve(){
    int n;
    std::cin >> n;
    std::vector <int> v(n);
    std::map <int, int> vf;
    for(int i = 0;i < n;i++){
        std::cin >> v[i];
        vf[v[i]]++;
    }
    int score = 0;
    for(const auto& x : vf){
        score += x.second / 2;
    }
    std::cout << score << "\n";
}

int main()  {
    int t;
    std::cin >> t;
    while(t--)  {
        solve();
    }
    return 0;
}