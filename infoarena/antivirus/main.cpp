#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e3 + 1;

int test;
int v[maxn];
long long d[maxn][maxn];
long long sum[maxn];


int findMin(int l, int r, int ln)  {
    long long ans = 1e9;
    if(ln == 0)  {
        return 0;
    }
    int l1 = l;
    int r1 = r;
    for(int ln2 = 0;ln2 <= ln;ln2++)  {
        l1 = l + ln2;
        r1 = r - (ln - ln2);
        ans = min(ans, sum[l1] - sum[l] + sum[r - 1] - sum[r1 - 1]);
    }
    return ans;
}

inline void solve()  {
    int n, k;
    cin >> n >> k;
    for(int i = 0;i <= n;i++)
        for(int j = 0;j <= n;j++)
            d[i][j] = 1e9;
    memset(sum, 0, maxn * sizeof(long long));
    vector <int> zeros;
    sum[0] = 0;
    for(int i = 1;i <= n;i++)  {
        cin >> v[i];
        if(v[i] == 0)
            zeros.push_back(i);
        sum[i] = sum[i - 1] + v[i];
    }
    int prev = zeros[0];
    for(int s1 = 1;s1 <= prev;s1++)
        d[prev][s1] = sum[prev] - sum[prev - s1];
    for(int ind = 1;ind < zeros.size();ind++)  {
        int i = zeros[ind];
        for(int s = ind + 1;s <= k - zeros.size() + ind + 1;s++)  {
            for(int t = max(1, s - i + prev);t < s;t++)  {
                d[i][s] = min(d[i][s], d[prev][t] + findMin(prev, i, s - t - 1));
            }
        }
        prev = i;
    }
    int lastZ = zeros[zeros.size() - 1];
    for(int s = zeros.size();s <= k;s++)  {
        if(lastZ + k - s > n)
            continue;
        d[lastZ][k] = min(d[lastZ][k], d[lastZ][s] + sum[lastZ + k - s] - sum[lastZ]);
    }
    cout << d[lastZ][k] << "\n";
}

int main()  {
    freopen("antivirus.in", "r", stdin);
    freopen("antivirus.out", "w", stdout);
    cin >> test;
    while(test--)  {
        solve();
    }
    return 0;
}