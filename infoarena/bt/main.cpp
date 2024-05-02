#include <iostream>
#include <cstdio>
#include <tuple>

const int maxN = 500 + 5;
const long long mod = 1e9 + 7;
const int _modInt = 1e9 + 7;

int modIfy(long long t)  {
    return (t % mod + mod) % mod;
}

std::pair <int, int> invMod(int a, int b)  {
    if(a == 0)
        return std::make_pair(0, 1);
    int x, y;
    std::tie(x, y) = invMod(b % a, a);
    return std::make_pair(modIfy(1LL * y - 1LL * (b / a) * x), x);
}

class modInt  {
    private:
    int nr;
    int inv;
    public:
    modInt()  {nr = 0; inv = -1;}
    modInt(const int& nr)  {
        this -> nr = nr;
        this -> inv = -1;
    }
    void operator = (const int& nr)  {
        this -> nr = nr;
        this -> inv = -1;
    }
    void operator = (const modInt& oth)  {
        this -> nr = oth.nr;
        this -> inv = oth.inv;
    }
    modInt operator * (const modInt& oth)  {
        return modInt(modIfy(1LL * (oth.nr) * this -> nr));
    }
    void operator *= (const modInt& oth)  {
        *this = ((*this) * oth);
    }
    modInt operator + (const modInt& oth)  {
        return modInt((oth.nr + this -> nr) % _modInt);
    }
    void operator += (const modInt& oth)  {
        *this = ((*this) + oth);
    }
    int get()  {
        return this -> nr;
    }
    modInt invMod()  {
        if(this -> inv == -1)
            this -> inv = (::invMod(this -> nr, mod).first);
        return modInt(this -> inv);
    }
};

int N;
int v[maxN * 2];
modInt d[maxN * 2][maxN * 2];
bool computed[maxN * 2][maxN * 2];
modInt fact[maxN];

modInt choose(int lg, int lg1)  {
    return fact[lg] * fact[lg1].invMod() * fact[lg - lg1].invMod();
}

modInt& calc(int i, int j)  {
    if(computed[i][j])
        return d[i][j];
    if(computed[i - N][j - N])
        return d[i - N][j - N];
}

int main()  {
    freopen("bt.in", "r", stdin);
    freopen("bt.out", "w", stdout);
    std::cin >> N;
    for(int i = 1;i <= N;i++)
        std::cin >> v[i];
    for(int i = N + 1;i <= 2 * N;i++)
        v[i] = v[i - N];
    v[0] = v[N];
    for(int i = 1;i <= N;i++)  {
        if(v[i] == v[i - 1])  {
            std::cout << "0\n";
            return 0;
        }
    }
    for(int i = 1;i < 2 * N;i++)  {
        d[i][i] = (v[i - 1] != v[i + 1]);
        computed[i][i] = true;
        d[i][i - 1] = 1;
        computed[i][i - 1] = true;
    }

    fact[0] = 1;
    for(int i = 1;i <= N;i++)
        fact[i] = fact[i - 1] * i;

    for(int lung = 2;lung < N;lung++)  {
        for(int i = 1;i <= N;i++)  {
            int j = i + lung - 1;
            computed[i][j] = true;
            if(v[i - 1] == v[j + 1] && (i - 1) % N != (j + 1) % N)
                continue;

            for(int k = i;k <= j;k++)  {
                if(v[k] == v[i - 1] || v[k] == v[j + 1])
                    continue;
                int lg1 = k - i;
                int lg = j - i;
                d[i][j] += calc(i, k - 1) * calc(k + 1, j) * choose(lg, lg1);
            }
        }
    }
    modInt ans = 0;
    for(int i = 1;i <= N;i++)  {
        ans += d[i][i + N - 2];
    }
    std::cout << ans.get() << "\n";
    return 0;
}
