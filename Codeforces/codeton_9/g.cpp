#include <bits/stdc++.h>

void dfs(const std::vector <int>(&v)[], std::vector <int>& depth, std::vector <bool> &viz, const int& node){
    viz[node] = true;

    depth[node] = 1;

    for(const auto& vec : v[node]){
        if(viz[vec]){
            continue;
        }
        dfs(v, depth, viz, vec);
        depth[node] = std::max(depth[node], depth[vec] + 1);
    }
}


inline void solve(){
    int n, m;
    std::cin >> n >> m;
    std::vector <int> v[n + 1];
    std::vector <int> depth(n + 1, -1);
    for(int i = 1;i <= n;i++){
        int a, b;
        std::cin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);
    }
    std::vector <bool> viz(n + 1, 0);
    dfs(v, depth, viz, 1);

}

int main(){
    int t;
    t = 1;
    while(t--){
        solve();
    }
    return 0;
}