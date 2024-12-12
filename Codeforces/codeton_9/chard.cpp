#include <bits/stdc++.h>

#define DEBUG 1

long long mod;

void br(long long& val){
    val = (val % mod);
    val = val + mod;
    val = val % mod;
}

void invmod(long long W, long long X, long long&a, long long&b){
    if(X == 0){
        a = 1;
        b = 0;
        return;
    }
    long long a1, b1;
    invmod(X, W % X, a1, b1);
    a = b1;
    b = (a1 - (W / X) * b1);
    br(a);
    br(b);
}


long long invmod(long long W, long long X, long long div){
    long long a, b;
    mod = X;
    br(div);
    // std::cerr << W << " " << X << " " << div << "\n";
    invmod(W, X, a, b);
    long long act_div;
    act_div = W * a + X * b;
    br(act_div);
    long long fact, c;
    long long gcc = std::gcd(X, act_div);
    gcc = std::gcd(gcc, div);
    invmod(act_div / gcc, X / gcc, fact, c);

    fact = (fact * div / gcc);
    br(fact);

    // std::cerr <<( (W * a + X * b) % mod + mod) % mod << " " << a << "\n";
    a *= fact;
    br(a);
    b *= fact;
    br(b);

    // std::cerr <<( (W * a + X * b) % mod + mod) % mod << "\n";

    long long aaa = W * a + X * b;
    br(aaa);
    if(aaa != div){
        return -1;
    }
    long long minna = X / std::gcd(X, W);
    a %= minna;
    a += minna;
    a %= minna;
    return a;
}

inline void solve(){
    int x;long long m;
    std::cin >> x >> m;
    int pow_t = 1;
    while(pow_t <= x){
        pow_t *= 2;
    }
    long long nr = 0;
    int cpow_t = pow_t;
    pow_t = std::min((long long)pow_t, m);
    for(int y = 1;y <= pow_t;y++){
        int div = (x ^ y);

        if(div % x == 0 || div % y == 0){
            nr++;
        }
        // Now compute for y >= cpow_t

        long long a = invmod(cpow_t, x, (-div));

        if(a != -1){
            std::cerr << "a" << y << " " << a << "\n";
            // if(y == 1)
            // std::cerr << a << " " << y << "\n";
            long long lim = m - y;
            long long rr = 1;
            if(a == 0){
                rr = 0;
            }
            if(y == cpow_t){
                rr = 0;
            }
            if(lim >= 0){
                lim /= 1LL * cpow_t;
                lim -= a;
                if(lim >= 0){
                    lim /= 1LL * x / std::gcd(x, cpow_t);
                    nr += lim + rr;
                }
            }
        }
    }
    std::cout << nr << "\n";
}

int main(){
    if(DEBUG){
        freopen("chard.in", "r", stdin);
        freopen("chard.out", "w", stdout);
    }
    int t;
    std::cin >> t;
    while(t--){
        solve();
    }
    return 0;
}