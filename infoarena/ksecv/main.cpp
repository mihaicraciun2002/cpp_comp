#include <cstdio>
#include <algorithm>
#include <stack>
#include <utility>

const int maxn = 1e5 + 1;

int N, K;
int v[maxn];

int prv = 0, curr = 1;

int dp[maxn][2];

int main()  {
    std::freopen("ksecv.in", "r", stdin);
    std::freopen("ksecv.out", "w", stdout);
    std::scanf("%d%d", &N, &K);
    for(int i = 1;i <= N;i++)
        std::scanf("%d", &v[i]);
    for(int i = 1;i <= N;i++)
        dp[i][0] = std::max(dp[i - 1][0], v[i]);
    for(int k = 2;k <= K;k++)  {
        prv = k % 2;
        curr = 1 - prv;
        std::stack < std::pair <int, int> > stack;
        for(int i = k;i <= N;i++)  {
            int ans = dp[i - 1][prv];
            while(!stack.empty() && v[i] >= v[stack.top().first])  {
                ans = std::min(ans, stack.top().second);
                stack.pop();
            }
            dp[i][curr] = ans + v[i];
            if(!stack.empty())  {
                dp[i][curr] = std::min(dp[i][curr], dp[stack.top().first][curr]);
            }
            stack.push(std::make_pair(i, ans));
        }
    }
    std::printf("%d\n", dp[N][(K + 1) % 2]);
    return 0;
}