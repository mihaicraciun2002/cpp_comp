#include <cstdio>
#include <cstdint>
#include <cinttypes>
#include <vector>

inline void solve()  {
    int n;
    scanf("%d", &n);
    std::vector <int> v(n + 1);
    for(int i = 1;i <= n;i++)
        scanf("%d", &v[i]);
}

#define EASY_IO 1

int main()  {
    #if EASY_IO
    freopen("io.in", "r", stdin);
    freopen("io.out", "w", stdout);
    #endif
    int16_t T;
    scanf("%" SCNd16, &T);
    while(T--)  {
        solve();
    }
    return 0;
}