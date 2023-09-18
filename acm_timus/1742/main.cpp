#include <cstdio>
#include <utility>
#include <cstring>
#include <algorithm>

const int maxn = 1e5 + 1;

int N;
int nxt[maxn];

std::pair <int, int> d[maxn];
int viz[maxn];
bool isCycle[maxn];
int noDfs;
int whoStartedCycle;
int h[maxn];

void dfs(int node)  {
    if(viz[node])  {
        return;
    }
    if(nxt[node] == node)  {
        d[node] = std::make_pair(1, node);
        viz[node] = noDfs;
        return;
    }
    viz[node] = noDfs;
    if(viz[nxt[node]] == 0)  {
        h[nxt[node]] = h[node] + 1;
        dfs(nxt[node]);
        if(isCycle[nxt[node]] && nxt[node] != whoStartedCycle)  {
            isCycle[node] = 1;
            d[node] = std::make_pair(h[whoStartedCycle], node);
        }else{
            d[node] = std::make_pair(d[nxt[node]].first + 1, node);
        }
    }else if(viz[nxt[node]] == noDfs){
        whoStartedCycle = nxt[node];
        h[whoStartedCycle] = h[node] - h[whoStartedCycle] + 1;
        d[node] = std::make_pair(h[whoStartedCycle], node);
        isCycle[node] = 1;
    }else{
        d[node] = std::make_pair(d[nxt[node]].first + 1, node);
    }
}

bool vizSolve[maxn];

void dfsSolve(int node)  {
    if(vizSolve[node])
        return;
    vizSolve[node] = true;
    dfsSolve(nxt[node]);
}

inline int solveMin()  {
    int ans = 0;
    memset(vizSolve, 0, maxn * sizeof(bool));
    for(int i = N;i >= 1;i--)  {
        int index = d[i].second;
        if(vizSolve[index])
            continue;
        ans++;
        dfsSolve(index);
    }
    return ans;
}

inline int solveMax()  {
    int ans = 0;
    memset(vizSolve, 0, maxn * sizeof(bool));
    for(int i = 1;i <= N;i++)  {
        int index = d[i].second;
        if(vizSolve[index])
            continue;
        ans++;
        dfsSolve(index);
    }
    return ans;
}

#define EASY_IO 0

int main()  {
    #if EASY_IO
    freopen("1742.in", "r", stdin);
    #endif
    scanf("%d", &N);
    for(int i = 1;i <= N;i++)
        scanf("%d", &nxt[i]);
    for(int i = 1;i <= N;i++)
        if(!viz[i])
            noDfs++, h[i] = 1, dfs(i);
    std::sort(d + 1, d + N + 1);
    printf("%d %d\n", solveMin(), solveMax());
    return 0;
}