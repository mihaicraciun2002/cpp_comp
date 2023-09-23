#define CHRONO_IN 0
#if CHRONO_IN
#include <chrono>
#endif
// INCLUDES
//######################################//
#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
#include <cctype>
#include <iostream>

//######################################//
// START CODE HERE
//######################################//

const int maxn = 7500 + 1;
std::priority_queue <int> pq;
int N;
int v[maxn], lastSeen[maxn];
std::vector <int> edges[maxn];

inline int nextInt(FILE *in)  {
    char ch = fgetc(in);
    if(ch == EOF)
        return -1;
    while(!isdigit(ch))
        ch = fgetc(in);
    int ans = 0;
    while(ch != EOF && isdigit(ch))  {
        ans = ans * 10 + ch - '0';
        ch = fgetc(in);
    }
    return ans;
}

//######################################//
// END CODE HERE
//######################################//
#define EASY_IO 0
int main()  {
    #if CHRONO_IN
    auto started_time = std::chrono::high_resolution_clock::now();
    #endif
    #if EASY_IO
    freopen("aux.in", "r", stdin);
    freopen("aux.out", "w", stdout);
    #endif
//######################################//
// START CODE HERE
//######################################//
    while(1)  {
        int nextToRead = nextInt(stdin);
        if(nextToRead < 0)  {
            break;
        }
        v[++N] = nextToRead;
        lastSeen[v[N]] = N;
    }
    N++;

    for(int i = 1;i <= N;i++)  {
        if(lastSeen[i] == 0)  {
            pq.push(-i);
        }
    }

    for(int i = 1;i < N;i++)  {
        int node = -pq.top();
        pq.pop();
        edges[v[i]].push_back(node);
        edges[node].push_back(v[i]);
        if(i == lastSeen[v[i]])  {
            pq.push(-v[i]);
        }
    }

    for(int i = 1;i <= N;i++)  {
        std::sort(edges[i].begin(), edges[i].end());
        printf("%d: ", i);
        for(const auto& node: edges[i])
            printf("%d ", node);
        printf("\n");
    }

//######################################//
// END CODE HERE
//######################################//
    #if CHRONO_IN
    auto finished_time = std::chrono::high_resolution_clock::now();
    std::cerr << "Time elapsed (s):\n";
    std::cerr << (double)std::chrono::duration_cast<std::chrono::milliseconds>(finished_time - started_time).count() / 1000.0 << "\n";
    #endif
    return 0;
}