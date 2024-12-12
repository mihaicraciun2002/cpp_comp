#include <bits/stdc++.h>

inline int query(int l, int r){
    std::cout << "? " << l << " " << r << "\n";
    std::cout.flush();
    int ans;
    std::cin >> ans;
    return ans;
}

inline void out_imp(){
    std::cout << "! IMPOSSIBLE\n";
    std::cout.flush();
}

inline void out(const std::vector<int>& v){
    std::cout << "! ";
    for(int i = 1;i < v.size();i++){
        std::cout << v[i];
    }
    std::cout << "\n";
    std::cout.flush();
}

inline void solve(){
    int n;
    std::cin >> n;
    std::vector<int> v(n + 1, -1);
    int end = 1;
    for(int i = 1;i < n;)  {
        int no = query(i, i + 1);
        if(no == 1)  {
            v[i] = 0;
            v[i + 1] = 1;
            if(end + 1 < i){
                int qq = query(end, i + 1);
                int length = i - end;
                int pas = 1 << 25;
                int r = end;
                while(pas){
                    if(r + pas >= i){
                        pas >>= 1;
                        continue;
                    }
                    if(query(end, r + pas) == qq){
                        r += pas;
                    }
                    pas >>= 1;
                }
                for(int j = end;j <= r;j++)
                    v[j] = 1;
                for(int j = r + 1;j < i;j++)
                    v[j] = 0;
            }
            end = i + 1;
            i = i + 2;
        }else{
            i = i + 1;
        }
    }
    for(int i = 1;i <= n;i++){
        if(v[i] == -1){
            out_imp();
            return;
        }
    }
    out(v);
}

int main()  {
    int t;
    std::cin >> t;
    while(t--)  {
        solve();
    }
    return 0;
}