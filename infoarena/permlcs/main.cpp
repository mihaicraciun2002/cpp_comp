#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e3 + 1;
const int maxm = 11;

int N, M;
int poz[maxn][maxm];
int v[maxn];
int d[maxn];

int main()  {
    freopen("permlcs.in", "r", stdin);
    freopen("permlcs.out", "w", stdout);
    cin >> N >> M;
    for(int i = 1;i <= N;i++)  {
        cin >> v[i];
        poz[v[i]][1] = i;
    }
    for(int i = 2;i <= M;i++)  {
        for(int j = 1;j <= N;j++)  {
            int x;
            cin >> x;
            poz[x][i] = j;
        }
    }
    for(int i = 1;i <= N;i++)  {
        d[v[i]] = 1;
        for(int j = 1;j < i;j++)  {
            bool OK = 1;
            for(int t = 2;t <= M && OK;t++)  {
                if(poz[v[j]][t] > poz[v[i]][t])
                    OK = 0;
            }
            if(OK == 1)
                d[v[i]] = max(d[v[i]], 1 + d[v[j]]);
        }
    }
    int ans = 0;
    for(int i = 1;i <= N;i++)
        ans = max(ans, d[i]);
    cout << ans;
    return 0;
}