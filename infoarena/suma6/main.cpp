#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5 + 1;
const int maxsqrtn = 317;
const int maxq = 2e5 + 1;
const int maxval = 1e6 + 1;

int N, S, Q;
int blockSize;
int v[maxn];

class Query  {
    public:
    int L;
    int R;
    int index;
};

Query queries[maxq];

bool queryCmp(Query a, Query b)  {
    if(a.L / blockSize != b.L / blockSize)
        return a.L < b.L;
    return a.R < b.R;
}

int vf[maxval];
long long ans[maxq];

long long currans = 0;

int main()  {
    freopen("suma6.in", "r", stdin);
    freopen("suma6.out", "w", stdout);
    cin >> N >> S;
    for(int i = 1;i <= N;i++)  {
        cin >> v[i];
    }
    blockSize = sqrt(N);
    cin >> Q;
    for(int i = 1;i <= Q;i++)  {
        cin >> queries[i].L >> queries[i].R;
        queries[i].index = i;
    }
    sort(queries + 1, queries + Q + 1, queryCmp);
    int currL = queries[1].L, currR = queries[1].R;
    for(int i = currL;i <= currR;i++)  {
        if(S >= v[i])
            currans += vf[S - v[i]];
        vf[v[i]]++;
    }
    ans[queries[1].index] = currans;
    for(int i = 2;i <= Q;i++)  {
        while(currL < queries[i].L)  {
            vf[v[currL]]--;
            if(S >= v[currL])
                currans -= vf[S - v[currL]];
            currL++;
        }
        while(currL > queries[i].L)  {
            currL--;
            if(S >= v[currL])
                currans += vf[S - v[currL]];
            vf[v[currL]]++;
        }
        while(currR < queries[i].R)  {
            currR++;
            if(S >= v[currR])
                currans += vf[S - v[currR]];
            vf[v[currR]]++;
        }
        while(currR > queries[i].R)  {
            vf[v[currR]]--;
            if(S >= v[currR])
                currans -= vf[S - v[currR]];
            currR--;
        }
        ans[queries[i].index] = currans;
    }
    for(int i = 1;i <= Q;i++)
        cout << ans[i] << "\n";
    return 0;
}