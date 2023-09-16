#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6 + 2;

int n;
int x[maxn], y[maxn];

inline long long solve(int* v)  {
    long long mini = 0;
    int mid = n / 2 + n % 2;
    for(int i = 1;i <= n;i++)  {
        mini += abs(v[i] - v[mid]);
    }
    return mini;
}

int main()  {
    freopen("antitir.in", "r", stdin);
    freopen("antitir.out", "w", stdout);
    scanf("%d", &n);
    for(int i = 1;i <= n;i++)  {
        scanf("%d%d", &x[i], &y[i]);
    }
    sort(x + 1, x + n + 1);
    sort(y + 1, y + n + 1);
    printf("%lld", solve(x) + solve(y));
    return 0;
}