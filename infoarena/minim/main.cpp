#include <bits/stdc++.h>

using namespace std;

#define pii pair <int, int>

int n;
#define x first
#define i second
vector <pii> v;


inline void perform()  {
    int l = 0, r = 0, ans = INT_MAX;
    int s = 1, in = 0;
    for(int i = 0;i < v.size();i++)  {
        if(v[i].x <= s + v[i].x)  {
            s = v[i].x;
            in = i;
        }else s += v[i].x;
        if(s < ans)  {
            ans = s;
            l = in;
            r = i;
        }else if(s == ans)  {
            if(r - l > i - in)  {
                r = i;
                l = in;
            }
        }
    }
    cout << ans << " " << v[l].i + 1 << " " << v[r].i + 1 << "\n";
    vector <pii> aux;
    for(int i = 0;i < v.size();i++)  {
        if(i >= l && i <= r)
            continue;
        aux.push_back(v[i]);
    }
    v = aux;
}

int main()  {
    freopen("minim.in", "r", stdin);
    freopen("minim.out", "w", stdout);
    cin >> n;
    for(int i = 0;i < n;i++)  {
        int x;
        cin >> x;
        v.push_back(make_pair(x, i));
    }
    while(v.size())  {
        perform();
    }
    return 0;
}