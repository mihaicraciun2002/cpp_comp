#include <bits/stdc++.h>

inline std::map <int, bool> find_div(const int& nr)  {
    std::map <int, bool> vv;
    
    for(int i = 1;i * i <= nr;i++)  {
        if(nr % i == 0)  {
            vv[i] = true;
            vv[nr / i] = true;
        }
    }

    return vv;
}

inline void solve(){
    int k;
    std::cin >> k;
    std::vector <int> a(k);
    std::map <int, int> vf;
    
    for(int i = 0;i < k;i++){
        std::cin >> a[i];
        vf[a[i]] ++;
    }
    const auto& tt = find_div(k - 2);
    for(const auto& x : tt)  {
        int val = x.first;
        int op = (k - 2) / val;
        int eq = (val == op);
        if(vf[val] - eq > 0 && vf[op] - eq > 0)  {
            std::cout << val << " " << op << "\n";
            return;
        }
    }
}

int main()  {
    int t;
    std::cin >> t;
    while(t--)  {
        solve();
    }
    return 0;
}