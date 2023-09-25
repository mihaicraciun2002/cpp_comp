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

// START CODE HERE

#define neighbor first
#define cost second

const int INF = 1e9;
const int maxn = 100 + 1;
const int maxk = 100 - 1 + 1;
std::vector <std::pair <int, int>> edges[maxn];
int dad[maxn];
int kidCount[maxn];
int subTreeSize[maxn];
int totalCost[maxn];
int d[maxn][maxk][maxn];
bool computed[maxn][maxk][maxn];

int N, Q, K;
int sumEdges;

void DFS(const int& node)  {
    subTreeSize[node]++;
    for(const auto& edge : edges[node])  {
        int neighbor = edge.neighbor;
        if(dad[neighbor])
            continue;
        dad[neighbor] = node;
        kidCount[node]++;
        DFS(neighbor);
        subTreeSize[node] += subTreeSize[neighbor];
        totalCost[node] += edge.cost;
        totalCost[node] += totalCost[neighbor];
    }
}

void DFSDP(const int& node)  {
    int kidIndex = 0;
    int maxSubtreeSize = 1;
    for(int i = 0;i <= kidCount[node];i++)
        computed[node][0][i] = true;
    for(const auto& edge: edges[node])  {
        int child = edge.neighbor;
        if(dad[child] != node)
            continue;
        DFSDP(child);
        kidIndex++;
        maxSubtreeSize += subTreeSize[child];
        for(int k = 1;k <= K;k++)  {
            d[node][k][kidIndex] = INF;
            bool isComputed = false;

            for(int t = 0;t <= k;t++)  {
                if(computed[node][k - t][kidIndex - 1] && computed[child][t][kidCount[child]])  {
                    d[node][k][kidIndex] = std::min(d[node][k][kidIndex],
                        d[node][k - t][kidIndex - 1] + d[child][t][kidCount[child]]),
                        isComputed = true;
                }
            }
            computed[node][k][kidIndex] = isComputed;
            // If we completely cut off child
            int maxDim = subTreeSize[child];

            if(k >= maxDim && (computed[node][k - maxDim][kidIndex - 1] || (kidIndex == 1 && k == maxDim)))  {
                d[node][k][kidIndex] = std::min(d[node][k][kidIndex],
                    d[node][k - maxDim][kidIndex - 1] + d[child][maxDim - 1][kidCount[child]] + edge.cost);
                computed[node][k][kidIndex] = true;
            }
        }
    }
}

// END CODE HERE

int main()  {
    #if USE_MODE
    started_time = std::chrono::high_resolution_clock::now(); freopen("aux.in", "r", stdin);  freopen("aux.out", "w", stdout);
    #endif

// START CODE HERE

    std::cin >> N >> Q;
    K = N - 1 - Q;
    for(int i = 1;i < N;i++)  {
        int x, y, c;
        std::cin >> x >> y >> c;
        sumEdges += c;
        edges[x].push_back(std::make_pair(y, c));
        edges[y].push_back(std::make_pair(x, c));
    }

    dad[1] = 1;
    DFS(1);
    DFSDP(1);


    std::cout << sumEdges - d[1][K][kidCount[1]] << "\n";


// END CODE HERE

    #if USE_MODE
    endTimeCHRONO();
    #endif
    return 0;
}
