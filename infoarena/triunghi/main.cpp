#include <bits/stdc++.h>

using namespace std;

int N, S;
const int maxS = 1e6;

int tot[20];

bool viz[maxS + 5];
#define pii pair <int, int>

int g[20][20][20];
pii ansP[maxS + 5];

int gans[20];
int ans[20][20];

int main()  {
    freopen("triunghi.in", "r", stdin);
    freopen("triunghi.out", "w", stdout);
    scanf("%d%d", &N, &S);
    for(int i = 1;i <= N;i++)
        g[N][i][i] += 1, tot[i] = 1;
    for(int l = N - 1;l >= 1;l--)  {
        for(int pos = 1;pos <= l;pos++)
            for(int i = 1;i <= N;i++)
                g[l][pos][i] = g[l + 1][pos][i] + g[l + 1][pos + 1][i],
                tot[i] += g[l][pos][i];
    }
    for(int i = 1;i <= N;i++)
        S -= tot[i];
    int N2 = N / 2 + N % 2;
    viz[0] = 1;
    for(int i = 1;i <= N2;i++)  {
        for(int g = 0;g <= S;g++)  {
            if(g - tot[i] >= 0 && viz[g - tot[i]])
                viz[g] = 1, ansP[g] = make_pair(i, 1);
        }
    }
    if(!viz[S])  {
        cout << "imposibil\n";
        return 0;
    }
    while(S)  {
        gans[ansP[S].first] += ansP[S].second;
        S -= ansP[S].second * tot[ansP[S].first];
    }
    for(int i = 1;i <= N;i++)
        ans[N][i] = gans[i] + 1;
    for(int l = N - 1;l >= 1;l--)
        for(int i = 1;i <= l;i++)
            ans[l][i] = ans[l + 1][i] + ans[l + 1][i + 1];
    for(int l = 1;l <= N;l++)  {
        for(int i = 1;i <= l;i++)
            printf("%d ", ans[l][i]);
        printf("\n");
    }
    return 0;
}