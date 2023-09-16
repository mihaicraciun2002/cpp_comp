#include <bits/stdc++.h>

using namespace std;

const int maxv = 1e6 + 1;

int n, m;
int d[maxv];

int main()  {
    freopen("distincte2.in", "r", stdin);
    freopen("distincte2.out", "w", stdout);
    cin >> n >> m;
    for(int i = 1;i <= n;i++)  {
        int x;
        cin >> x;
        d[x] = 1;
    }
    for(int i = 1;i < maxv;i++)
        d[i] += d[i - 1];
    for(int i = 1;i <= m;i++)  {
        int l, r;
        cin >> l >> r;
        cout << d[r] - d[l - 1] << "\n";
    }
    return 0;
}