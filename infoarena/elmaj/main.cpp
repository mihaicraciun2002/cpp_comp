#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6 + 1;

int N;
int v[maxn];

int main()  {
    freopen("elmaj.in", "r", stdin);
    freopen("elmaj.out", "w", stdout);
    scanf("%d", &N);
    int elmaj = -1, cnt = 0;
    for(int i = 1;i <= N;i++)  {
        int x;
        scanf("%d", &x);
        v[i] = x;
        if(elmaj == x)
            cnt++;
        else cnt--;
        if(cnt <= 0)  {
            cnt = 1, elmaj = x;
        }
    }
    if(cnt <= 0)  {
        cout << "-1\n";
    }else  {
        int nrap = 0;
        for(int i = 1;i <= N;i++)
            if(v[i] == elmaj)
                nrap++;
        cout << elmaj << " " << nrap << "\n";
    }
    return 0;
}