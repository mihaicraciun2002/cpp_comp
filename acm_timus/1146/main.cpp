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

// START CODE HERE

const int maxn = 100 + 1;

int sum[maxn][maxn];
int v[maxn][maxn];
int dp[maxn][maxn][maxn];

int N;

inline int sumCol(const int& col, const int& end, const int& start)  {
    return sum[end][col] - sum[start][col] - (sum[end][col - 1] - sum[start][col - 1]);
}

// END CODE HERE

int main()  {
    #if USE_MODE
    started_time = std::chrono::high_resolution_clock::now(); freopen("aux.in", "r", stdin);  freopen("aux.out", "w", stdout);
    #endif

// START CODE HERE

    std::cin >> N;
    for(int i = 1;i <= N;i++)
        for(int j = 1;j <= N;j++)
            std::cin >> v[i][j];

    for(int i = 1;i <= N;i++)
        for(int j = 1;j <= N;j++)
            sum[i][j] = sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1] + v[i][j];

    int ans = -1e9;

    for(int h = 1;h <= N;h++)  {
        for(int i = h;i <= N;i++)  {
            for(int j = 1;j <= N;j++)  {
                dp[i][j][h] = std::max(0, dp[i][j - 1][h]) + sumCol(j, i, i - h);
                ans = std::max(ans, dp[i][j][h]);
            }
        }
    }

    std::cout << ans << "\n";


// END CODE HERE

    #if USE_MODE
    endTimeCHRONO();
    #endif
    return 0;
}
