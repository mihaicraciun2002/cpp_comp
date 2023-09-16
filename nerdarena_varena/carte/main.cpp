#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e4 + 1;

int n;
int pos[maxn];

int main()  {
    freopen("carte.in", "r", stdin);
    freopen("carte.out", "w", stdout);
    cin >> n;
    for(int i = 1;i <= n;i++)  {
        int x;
        cin >> x;
        pos[x] = i;
    }
    int curr = 1, amm = 1;
    int maxx = 1, poss = 1;
    for(int i = 2;i <= n;i++)  {
        if(pos[i] < pos[i - 1])  {
            curr++;
            amm = 0;
        }
        amm++;
        if(maxx < amm)  {
            maxx = amm;
            poss = curr;
        }
    }
    cout << curr << " " << poss << " " << maxx;
    return 0;
}