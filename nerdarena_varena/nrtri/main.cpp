#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e3 + 1;

int N;
int v[maxn];

const int maxval = 6e4 + 1;
int aib[maxval];

inline void add(int a)  {
    while(a < maxval)  {
        aib[a]++;
        a += (a & (-a));
    }
}

inline long long query(int a)  {
    long long sum = 0;
    while(a)  {
        sum += 1LL * aib[a];
        a -= (a & (-a));
    }
    return sum;
}

long long ans;

int main()  {
    freopen("nrtri.in", "r", stdin);
    freopen("nrtri.out", "w", stdout);
    scanf("%d", &N);
    for(int i = 1;i <= N;i++)  {
        scanf("%d", &v[i]);
    }
    sort(v + 1, v + N + 1);
    long long totsum = 0;
    for(int i = 1;i <= N;i++)  {
        long long tmp = 0;
        tmp = query(v[i]);
        ans += totsum - tmp;
        for(int j = 1;j < i;j++)
            add(v[i] + v[j]), totsum++;
    }
    cout << ans;
    return 0;
}