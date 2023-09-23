#define USE_MODE 0
#if USE_MODE
#include <chrono>
#include <iostream>
std::chrono::time_point<std::chrono::high_resolution_clock> started_time;
std::chrono::time_point<std::chrono::high_resolution_clock> finished_time;
inline void endTimeCHRONO()  {
    finished_time = std::chrono::high_resolution_clock::now(); std::cerr << "\nTime elapsed (s):\n";
    std::cerr << (double)std::chrono::duration_cast<std::chrono::milliseconds>(finished_time - started_time).count() / 1000.0 << "\n";
}
#endif
// INCLUDES (cstdio and iostream already included)

#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <queue>
#include <cstring>
#include <algorithm>

// START CODE HERE

const int maxn = 100 + 1;

#define cost second
#define neighbor first

int N, M;
std::vector <std::pair <int, int>> edges[maxn];
int d[maxn][maxn];
int prev[maxn][maxn];
int bestMiddleMan[maxn][maxn];

inline bool solve()  {
    scanf("%d", &N);
    if(N == -1)  {
        return false;
    }
    scanf("%d", &M);
    for(int i = 1;i <= N;i++)
        edges[i].clear();

    for(int i = 1;i <= N;i++)
        for(int j = 1;j <= N;j++)
            d[i][j] = 1e9;

    for(int i = 1;i <= M;i++)  {
        int x, y, l;
        scanf("%d%d%d", &x, &y, &l);
        edges[x].push_back(std::make_pair(y, l));
        edges[y].push_back(std::make_pair(x, l));
    }

    for(int i = 1;i <= N;i++)  {
        std::queue <int> Q;
        Q.push(i);
        d[i][i] = 0;
        while(!Q.empty())  {
            int node = Q.front();
            Q.pop();
            for(const auto& edge : edges[node])  {
                if(edge.neighbor < i)
                    continue;
                if(d[i][edge.neighbor] > d[i][node] + edge.cost)  {
                    prev[i][edge.neighbor] = node;
                    bestMiddleMan[i][edge.neighbor] = i;
                    d[i][edge.neighbor] = d[i][node] + edge.cost;
                    Q.push(edge.neighbor);
                }
            }
        }
    }


    bool foundBest = false;
    int best = 1e9;
    int bI, bA, bB;

    std::vector <int> sol;

    for(int i = N;i >= 1;i--)  {
        for(int a = i + 2;a <= N;a++)
            for(int b = a + 1;b <= N;b++)  {
                if(d[a][b] > d[i + 1][a] + d[i + 1][b])  {
                    d[a][b] = d[i + 1][a] + d[i + 1][b];
                    bestMiddleMan[a][b] = i + 1;
                }
            }

        for(int t = 0;t < edges[i].size();t++)  {
            for(int u = 0;u < edges[i].size();u++)  {
                if(t == u)
                    continue;
                int a = edges[i][t].neighbor;
                int b = edges[i][u].neighbor;
                int edgeACost = edges[i][t].cost;
                int edgeBCost = edges[i][u].cost;
                if(a >= b)
                    continue;
                if(i >= a)
                    continue;
                if(best > edgeACost + edgeBCost + d[a][b])  {
                    best = edgeACost + edgeBCost + d[a][b];
                    bI = i;
                    bA = a;
                    bB = b;
                    foundBest = true;
                    sol.clear();
                    sol.push_back(bI);
                    if(bestMiddleMan[a][b] == a)  {
                        int prvAux = b;
                        std::vector <int> auxSol;
                        while(prvAux != a)  {
                            auxSol.push_back(prvAux);
                            prvAux = prev[a][prvAux];
                        }
                        auxSol.push_back(a);
                        std::reverse(auxSol.begin(), auxSol.end());
                        for(const auto& x : auxSol)
                            sol.push_back(x);
                    }else{
                        int prvAux = a;
                        int middleGuy = bestMiddleMan[a][b];
                        while(prvAux != middleGuy)  {
                            sol.push_back(prvAux);
                            prvAux = prev[middleGuy][prvAux];
                        }
                        sol.push_back(middleGuy);
                        std::vector <int> auxSol;
                        prvAux = b;
                        while(prvAux != middleGuy)  {
                            auxSol.push_back(prvAux);
                            prvAux = prev[middleGuy][prvAux];
                        }
                        std::reverse(auxSol.begin(), auxSol.end());
                        for(const auto& x : auxSol)
                            sol.push_back(x);
                    }
                }
            }
        }
    }
    if(!foundBest)  {
        printf("No solution.\n");
        return true;
    }
    for(const auto& x : sol)  {
        printf("%d ", x);
    }
    printf("\n");
    return true;
}

// END CODE HERE

int main()  {
    #if USE_MODE
    started_time = std::chrono::high_resolution_clock::now(); freopen("aux.in", "r", stdin);  freopen("aux.out", "w", stdout);
    #endif

// START CODE HERE

    while(solve())  {}


// END CODE HERE

    #if USE_MODE
    endTimeCHRONO();
    #endif
    return 0;
}