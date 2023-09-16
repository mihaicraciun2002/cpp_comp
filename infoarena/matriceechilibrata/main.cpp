#include <bits/stdc++.h>

using namespace std;

int N, M, X, Y;

int ans[1001][1001];

int main()  {
    freopen("matriceechilibrata.in", "r", stdin);
    freopen("matriceechilibrata.out", "w", stdout);
    cin >> N >> M >> X >> Y;
    if(N * X != M * Y)  {
        cout << "-1\n";
        return 0;
    }
    int l = 0, r = X - 1;
    for(int i = 1;i <= N;i++)  {
        int cnt = 0;
        for(int j = l;cnt < X;j++)  {
            ans[i][j % M] = 1, cnt++;
        }
        l += X;
        l = (l + M) % M;
        r += X;
        r = (r + M) % M;
    }
    for(int i = 1;i <= N;i++)  {
        for(int j = 0;j < M;j++)
            cout << ans[i][j];
        cout << "\n";
    }

    return 0;
}