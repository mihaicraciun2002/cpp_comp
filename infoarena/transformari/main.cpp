#include <bits/stdc++.h>

using namespace std;

int N;

const int maxval = 1e9;

int cmmdc(int a, int b)  {
    if(a > b)
        swap(a, b);
    if(a == 1)
        return b - a;
    if(b == 1)
        return 0;
    if(a == 0)
        return maxval;
    return b / a + cmmdc(a, b % a);
}

int main()  {
    freopen("transformari.in", "r", stdin);
    freopen("transformari.out", "w", stdout);
    cin >> N;
    int ans = maxval;
    for(int i = 1;i < N;i++)  {
        ans = min(ans, cmmdc(i, N));
    }
    cout << ans;
    return 0;
}