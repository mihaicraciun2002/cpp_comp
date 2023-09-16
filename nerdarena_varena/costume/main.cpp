#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5 + 1;

int N;
int v[maxn];
int arbint[4 * maxn];

void update(int node, int l, int r, int pos)  {
    if(l > r)  {
        return;
    }
    if(l > pos || r < pos)  {
        return;
    }
    if(l == r)  {
        arbint[node] = 1;
        return;
    }
    int mid = (l + r) / 2;
    update(node * 2, l, mid, pos);
    update(node * 2 + 1, mid + 1, r, pos);
    arbint[node] = arbint[node * 2] + arbint[node * 2 + 1];
}

int findMid(int node, int l, int r, int cnt)  {
    if(l > r)  {
        return -1;
    }
    if(l == r)  {
        return l;
    }
    int mid = (l + r) / 2;
    if(arbint[node * 2] < cnt)  {
        return findMid(node * 2 + 1, mid + 1, r, cnt - arbint[node * 2]);
    }else{
        return findMid(node * 2, l, mid, cnt);
    }
}

int main()  {
    freopen("costume.in", "r", stdin);
    freopen("costume.out", "w", stdout);
    scanf("%d", &N);
    int cnt = 0;
    for(int i = 1;i <= N;i++)  {
        scanf("%d", &v[i]);
        update(1, 1, N, v[i]);
        if(i % 2)
            cnt++;
        printf("%d ", findMid(1, 1, N, cnt));
    }
    return 0;
}