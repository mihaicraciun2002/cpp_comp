/**
d[l][p] - lungime l, cel mult p zerouri consecutive

d[l][p] = suma de
x caractere nenule + y caractere nule (y > 0, y <= p) + 1 caracter nenul + restul
x caractere nenule + y caractere nule

(B - 1) ^ x * (B - 1) * d[l - x - y - 1][p]

PLUS
(B - 1) ^ l daca totul e nenul

x caractere nenule + y caractere nule:
(B - 1) ^ x  (include pe (B - 1) ^ l pt x = l)

 */

#include <bits/stdc++.h>

using namespace std;

typedef struct longInt  {
    public:
    vector <char> digits;
    longInt(int x)  {
        while(x)  {
            digits.push_back(x % 10);
            x /= 10;
        }
    }
    longInt(long long x)  {
        while(x)  {
            digits.push_back(x % 10);
            x /= 10;
        }
    }
    longInt() = default;
    void operator =(const longInt &oth)  {
        digits = oth.digits;
    }
    void operator =(int oth)  {
        digits.clear();
        while(oth)  {
            digits.push_back(oth % 10);
            oth /= 10;
        }
    }
    void operator =(long long oth)  {
        digits.clear();
        while(oth)  {
            digits.push_back(oth % 10);
            oth /= 10;
        }
    }
    longInt operator +(const longInt &oth)  {
        int l = 0, r = 0, rest = 0;
        longInt ans = longInt(0);
        while(l < digits.size() && r < oth.digits.size())  {
            ans.digits.push_back((digits[l] + oth.digits[r] + rest) % 10);
            rest = (digits[l] + oth.digits[r] + rest) / 10;
            l++, r++;
        }
        while(l < digits.size())
            ans.digits.push_back((digits[l] + rest) % 10),
            rest = (rest + digits[l]) / 10, l++;
        while(r < oth.digits.size())
            ans.digits.push_back((oth.digits[r] + rest) % 10),
            rest = (rest + oth.digits[r]) / 10, r++;
        if(rest)
            ans.digits.push_back(rest);
        return ans;
    }
    longInt operator +(const long long oth)  {
        return *this + *(new longInt(oth));
    }
    longInt operator +(const int oth)  {
        return *this + *(new longInt(oth));
    }
    void operator +=(const longInt &oth)  {
        digits = (*this + oth).digits;
    }
    void operator +=(const long long oth)  {
        digits = (*this + oth).digits;
    }
    void operator +=(const int oth)  {
        digits = (*this + oth).digits;
    }
    longInt operator *(const longInt &oth)  {
        longInt ans = longInt(0);
        //oth * 
        //this
        for(int l = 0;l < digits.size();l++)  {
            longInt partial = longInt(0);
            for(int kk = 1;kk <= l;kk++)
                partial.digits.push_back(0);
            int rest = 0;
            for(int r = 0;r < oth.digits.size();r++)  {
                partial.digits.push_back((oth.digits[r] * digits[l] + rest) % 10);
                rest = (oth.digits[r] * digits[l] + rest) / 10;
            }
            if(rest)  {
                partial.digits.push_back(rest);
            }
            ans += partial;
        }
        return ans;
    }
    longInt operator *(const long long oth)  {
        return(*this * *(new longInt(oth)));
    }
    longInt operator *(const int oth)  {
        return (*this * *(new longInt(oth)));
    }
    void operator *=(const longInt &oth)  {
        digits = (*this * oth).digits;
    }
    void operator *=(const long long oth)  {
        digits = (*this * oth).digits;
    }
    void operator *=(const int oth)  {
        digits = (*this * oth).digits;
    }
    longInt operator -(const longInt &oth)  {
        longInt ans;
        int rest = 0;
        for(int r = 0;r < oth.digits.size();r++)  {
            int tb = digits[r] - oth.digits[r] - rest;
            if(tb < 0)  {
                rest = 1;
                ans.digits.push_back(tb + 10);
            }
            else  {
                rest = 0;
                ans.digits.push_back(tb);
            }
        }
        for(int r = oth.digits.size();r < digits.size();r++)  {
            int tb = digits[r] - rest;
            if(tb < 0)  {
                rest = 1;
                ans.digits.push_back(tb + 10);
            }
            else ans.digits.push_back(tb);
        }
        while(ans.digits.size() && ans.digits[ans.digits.size() - 1] == 0)
            ans.digits.pop_back();
        return ans;
    }
    string show()  {
        string ans;
        if(!digits.size())  {
            ans.push_back('0');
            return ans;
        }
        for(int i = digits.size() - 1;i >= 0;i--)
            ans.push_back(digits[i] + '0');
        return ans;
    }
}longInt;

int L, B, P, Q;
longInt d[21][21];
longInt putB1[21], putB[21];

int main()  {
    freopen("zero.in", "r", stdin);
    freopen("zero.out", "w", stdout);
    cin >> L >> B >> P >> Q;
    putB1[0] = 1;
    putB[0] = 1;
    for(int p = 1;p <= L;p++)
        putB1[p] = putB1[p - 1] * (B - 1),
        putB[p] = putB[p - 1] * (B);
    for(int l = 1;l <= L - 1;l++)  {
        for(int p = 0;p <= l;p++)  {
            for(int x = l - p;x <= l;x++)  {
                d[l][p] += putB1[x];
            }
            for(int x = 0;x <= l;x++)  {
                for(int y = 1;y <= p;y++)  {
                    if(l > x + y + 1)  {
                        d[l][p] += putB1[x + 1] * d[l - x - y - 1][p];
                    }
                    else if(l == x + y + 1)  {
                        d[l][p] += putB1[x + 1];
                    }
                }
            }

        }
        for(int p = l + 1;p <= L - 1;p++)
            d[l][p] = putB[l];
    }
    cout << ((d[L - 1][P] * (B - 1)).show()) << "\n";
    cout << (((d[L - 1][L - 1] - d[L - 1][Q - 1]) * (B - 1)).show());
    return 0;
}