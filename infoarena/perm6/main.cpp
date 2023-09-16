#include <bits/stdc++.h>

using namespace std;

class longInt  {
    private:
    vector <int> digits;
    public:
    longInt()  {}
    longInt(int num)  {
        while(num)
            digits.push_back(num % 10), num /= 10;
    }
    void operator +=(const longInt& oth)  {
        int rest = 0;
        int cnt = 0;
        while(cnt < digits.size() && cnt < oth.digits.size())  {
            digits[cnt] = (digits[cnt] + oth.digits[cnt] + rest);
            rest = digits[cnt] / 10;
            digits[cnt] %= 10;
            cnt++;
        }
        while(cnt < digits.size() && rest)  {
            digits[cnt] = (digits[cnt] + rest);
            rest = digits[cnt] / 10;
            digits[cnt] %= 10;
            cnt++;
        }
        while(cnt < oth.digits.size())  {
            if(cnt == digits.size())
                digits.push_back(0);
            digits[cnt] = (digits[cnt] + oth.digits[cnt] + rest);
            rest = digits[cnt] / 10;
            digits[cnt] %= 10;
            cnt++;
        }
        if(rest)  {
            if(cnt == digits.size())
                digits.push_back(0);
            digits[cnt] = rest;
            cnt++;
        }
    }
    void operator =(int num)  {
        while(num)
            digits.push_back(num % 10), num /= 10;
    }
    string show()  {
        string ans;
        if(digits.size() == 0)
            ans.push_back('0');
        for(auto x : digits)
            ans.push_back(x + '0');
        reverse(ans.begin(), ans.end());
        return ans;
    }
};

const int maxn = 45 + 1;
const int maxk = 45 * 44  / 2 + 1;

longInt d[maxn][maxk];

int N, K;

int main()  {
    freopen("perm6.in", "r", stdin);
    freopen("perm6.out", "w", stdout);
    cin >> N >> K;
    for(int n = 0;n <= N;n++)  {
        int kMax = n * (n - 1) / 2;
        d[n][0] = 1;
        d[n][kMax] = 1;
        for(int k = 1;k < kMax;k++)  {
            for(int j = 0;j <= min(n - 1, k);j++)
                d[n][k] += d[n - 1][k - j];
        }
    }
    cout << d[N][K].show();
    return 0;
}