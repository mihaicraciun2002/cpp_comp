#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5 + 1;

int n;
int v[maxn];

struct cmp{
    bool operator ()(long long a, long long b)  {
        return a > b;
    }
};

priority_queue <long long, vector <long long>, cmp> pq;

int main()  {
    freopen("minmax.in", "r", stdin);
    freopen("minmax.out", "w", stdout);
    cin >> n;
    for(int i = 1;i <= n;i++)
        cin >> v[i];
    sort(v + 1, v + n + 1);
    int l, r;
    l = 1, r = n;
    long long sum = 0;
    for(int i = 1;i <= n;i++)  {
        if(l <= r)  {
            if(l != r)
                pq.push(1LL * v[r] - 1LL * v[l]);
            sum += 1LL * v[r] - 1LL * v[l];
            r--;
            l++;
        }else{
            sum -= pq.top();
            pq.pop();
        }
        cout << sum << "\n";
    }
    return 0;
}