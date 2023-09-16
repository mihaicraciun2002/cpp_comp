#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5 + 1;
const int maxv = 1e6 + 2;

int N;

#define pii pair <int, int>
#define l first
#define r second

pii v[maxn];
pii stv[maxn];
int sti = 0;

int arbint[4 * maxn];

void update(int node, int l, int r, int pos, int val)  {
    if(l > pos || r < pos)  {
        return;
    }
    if(l == r)  {
        arbint[node] = max(arbint[node], val);
        return;
    }
    int mid = (l + r) / 2;
    update(node * 2, l, mid, pos, val);
    update(node * 2 + 1, mid + 1, r, pos, val);
    arbint[node] = max(arbint[node], max(arbint[node * 2], arbint[node * 2 + 1]));
}

int query(int node, int l, int r, int l1, int r1)  {
    if(r1 < l || l1 > r)  {
        return 0;
    }
    if(l1 <= l && r <= r1)  {
        return arbint[node];
    }
    int mid = (l + r) / 2;
    return max(query(node * 2, l, mid, l1, r1), query(node * 2 + 1, mid + 1, r, l1, r1));
}

vector <int> rs;
int vals[maxv];

const int buffsz = 1 << 16;
char buf[buffsz];
int cnt = buffsz - 1;

inline char nextc()  {
    cnt++;
    if(cnt == buffsz)  {
        cnt = 0;
        fread(buf, 1, buffsz, stdin);
    }
    return buf[cnt];
}

inline int readInt()  {
    char ch;
    ch = nextc();
    int nr = 0;
    while(isdigit(ch))  {
        nr = nr * 10 + ch - '0';
        ch = nextc();
    }
    return nr;
}

int main()  {
    freopen("drept.in", "r", stdin);
    freopen("drept.out", "w", stdout);
    N = readInt();
    for(int i = 1;i <= N;i++)
        v[i].l = readInt(), v[i].r = readInt(), v[i].l++, v[i].r++, rs.push_back(v[i].r);
    sort(v + 1, v + N + 1);
    sort(rs.begin(), rs.end());
    int prevv = -1;
    int curval = 0;

    for(auto x : rs)  {
        if(x != prevv)  {
            curval++;
        }
        prevv = x;
        vals[x] = curval;
    }

    for(int i = 1;i <= N;i++)  {
        v[i].r = vals[v[i].r];
    }

    int maxi = 0;
    int prev = 0;

    for(int i = 1;i <= N;i++)  {
        if(prev != v[i].l)  {
            pii x;
            for(int j = 1;j <= sti;j++)  {
                x = stv[j];
                update(1, 1, curval, x.first, x.second);
            }
            sti = 0;
        }
        int qr = query(1, 1, curval, 1, v[i].r - 1);
        sti++;
        stv[sti] = make_pair(v[i].r, qr + 1);
        maxi = max(maxi, qr + 1);
        prev = v[i].l;
    }
    printf("%d", maxi);
    return 0;
}