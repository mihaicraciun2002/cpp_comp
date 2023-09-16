#include <bits/stdc++.h>

using namespace std;

int L, B, P, Q;

long long ansP, ansQ;

void conf(int n, int b, int p, int q, bool st, vector <int> f)  {
    vector <int> hm;
    if(n == 0)  {
        int nr0 = 0, ans = 0;
        for(auto t : f)  {
            if(t == 0)
                nr0++;
            else  {
                ans = max(ans, nr0);
                nr0 = 0;
            }
        }
        ans = max(ans, nr0);
        if(ans <= p)  {
            ansP++;
        }
        if(ans >= Q)  {
            ansQ++;
        }
        return;
    }
    if(st == 1)  {
        for(int i = 1;i < b;i++)
            hm.push_back(i);
    }else
        for(int i = 0;i < b;i++)
            hm.push_back(i);
    for(auto x : hm)  {
        f.push_back(x);
        conf(n - 1, b, p, q, 0, f);
        f.pop_back();
    }
}

int main()  {
    freopen("zero.in", "r", stdin);
    FILE *in2 = fopen("zero.out", "r");
    cin >> L >> B >> P >> Q;
    vector <int> emp;
    conf(L, B, P, Q, 1, emp);
    long long ans1P, ans1Q;
    fscanf(in2, "%lld%lld", &ans1P, &ans1Q);
    cerr << L << " " << B << " " << P << " " << Q << "\n";
    cerr << "Corect: " << ansP << " " << ansQ << "\n";
    cerr << "Output: " << ans1P << " " << ans1Q << "\n";
    cerr << (ans1P == ansP && ans1Q == ansQ);
    return 0;
}