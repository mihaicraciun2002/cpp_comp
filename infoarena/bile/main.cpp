#include <bits/stdc++.h>

using namespace std;

const int maxn = 250 + 1;

#define pii pair <int, int>
#define l first
#define r second

pii dada[maxn][maxn];
int bigus[maxn][maxn];
int ansMax = 0;

pii findDada(pii start)  {
    int l = start.l;
    int r = start.r;
    while(start != dada[start.l][start.r])  {
        start = dada[start.l][start.r];
    }
    pii start2 = make_pair(l, r);
    while(start2 != start)  {
        pii aux = dada[start2.l][start2.r];
        dada[start2.l][start2.r] = start;
        start2 = aux;
    }
    return start;
}

int bigus1(pii someone)  {
    return bigus[someone.l][someone.r];
}

void union1(pii one, pii two)  {
    one = findDada(one);
    two = findDada(two);
    if(one == two){return;}
    if(bigus1(one) < bigus1(two))  {
        dada[one.l][one.r] = two;
        bigus[two.l][two.r] += bigus[one.l][one.r];
        ansMax = max(ansMax, bigus[two.l][two.r]);
    }else{
        dada[two.l][two.r] = one;
        bigus[one.l][one.r] += bigus[two.l][two.r];
        ansMax = max(ansMax, bigus[one.l][one.r]);
    }
}

const int dl[] = {0, 1, 0, -1};
const int dr[] = {1, 0, -1, 0};

int main()  {
    freopen("bile.in", "r", stdin);
    freopen("bile.out", "w", stdout);
    int n;
    cin >> n;
    vector <pii> v(n * n);
    vector <int> ans(n * n);
    for(int i = 0;i < n * n;i++)
        cin >> v[i].l >> v[i].r;
    for(int i = n * n - 1;i >= 0;i--)  {
        bigus[v[i].l][v[i].r] = 1;
        dada[v[i].l][v[i].r] = v[i];
        ans[i] = ansMax;
        ansMax = max(ansMax, 1);
        for(int j = 0;j < 4;j++)  {
            int ll = v[i].l + dl[j];
            int rr = v[i].r + dr[j];
            if(ll >= 1 && ll <= n && rr >= 1 && rr <= n)  {
                if(bigus[ll][rr])  {
                    union1(make_pair(ll, rr), v[i]);
                }
            }
        }
    }
    for(int i = 0;i < ans.size();i++)
        cout << ans[i] << "\n";
    return 0;
}