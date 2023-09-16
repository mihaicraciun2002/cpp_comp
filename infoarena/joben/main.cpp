#include <string>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

std::string a, b;
std::vector <char> vfa, vfb;

inline void solve()  {
    std::cin >> a >> b;
    vfa.clear();
    vfb.clear();
    vfa.resize(26);
    vfb.resize(26);
    for(const auto &x : a)
        vfa[x - 'a']++;
    for(const auto &x : b)
        vfb[x - 'a']++;
    std::sort(vfa.begin(), vfa.end());
    std::sort(vfb.begin(), vfb.end());
    for(int i = 0;i < 26;i++)  {
        if(vfa[i] != vfb[i])  {
            std::cout << "NU\n";
            return;
        }
    }
    std::cout << "DA\n";
}

int main()  {
    freopen("joben.in", "r", stdin);
    freopen("joben.out", "w", stdout);
    int T;
    std::cin >> T;
    while(T--)
        solve();
    return 0;
}