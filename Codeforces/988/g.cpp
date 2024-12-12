#include <bits/stdc++.h>

const long long mod = 998244353LL;

const int maxn = 1e6 + 5;

// bool ciur[maxn * 3];
// std::map <int, bool> prim;

/*inline void build_ciur()  {
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
} */

inline std::vector <int> decomp(int val){
    std::vector <int> ans;
    for(int i = 2;i * i <= val;i++){
        if(val % i)
            continue;
        while(val % i == 0)
            val /= i;
        ans.push_back(i);
    }
    if(val > 1){
        ans.push_back(val);
    }
    return ans;
}

inline void solve(){
    int n;
    scanf("%d", &n);

    std::vector <int> v(n + 1);
    std::unordered_map <int, long long> ddiv;
    std::unordered_map <int, int> viz;
    std::vector <long long> totans(n + 1);

    for(int i = 1;i <= n;i++){
        scanf("%d", &v[i]);
        auto dec = decomp(v[i]);
        int r = 1 << (dec.size());
        for(int j = 1;j < r;j++){
            std::vector <int> dd;
            int dda = 1;
            std::vector <int> oth;
            long long aaaa = 0;
            for(int div_i = 0;div_i < dec.size();div_i++){
                if((j & (1 << div_i))){
                    dd.push_back(dec[div_i]);
                    dda *= dec[div_i];
                }else{
                    oth.push_back(dec[div_i]);
                }
            }
            for(const auto t : oth){
                aaaa += ddiv[dda * t];
                aaaa %= mod;
            }
            totans[i] += ddiv[dda] - aaaa;
            if(i == 4){
              //  std::cerr << "bruh" << dda << ' ' << aaaa << ' ' << ddiv[dda] << "\n";
            }
            totans[i] = (totans[i] + mod) % mod;
        }

        if(i == 1)
            totans[i] = 1;

        for(int j = 1;j < r;j++){
            std::vector <int> dd;
            int dda = 1;

            long long aaaa = 0;
            for(int div_i = 0;div_i < dec.size();div_i++){
                if((j & (1 << div_i))){
                    dd.push_back(dec[div_i]);
                    dda *= dec[div_i];
                }
            }
            ddiv[dda] += totans[i];
            ddiv[dda] %= mod;
        }
    }

    std::cout << totans[n] << "\n";
}

int main()  {
    int t = 1;
    while(t--)  {
        solve();
    }
    return 0;
}