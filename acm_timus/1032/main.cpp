#include <cstdio>
#include <vector>

const int maxn = 1e4 + 1;

int prv[maxn];

int N;
std::vector <int> v;

#define EASY_IO 0

int main()  {
    #if EASY_IO
    freopen("1032.in", "r", stdin);
    freopen("1032.out", "w", stdout);
    #endif
    scanf("%d", &N);
    int sum = 0, x;
    for(int i = 1;i <= N;i++)  {
        scanf("%d", &x);
        v.push_back(x);
        sum += x;
        sum %= N;
        if(sum == 0)  {
            printf("%d\n", i);
            for(int j = 0;j < i;j++)
                printf("%d\n", v[j]);
            return 0;
        }
        if(prv[sum])  {
            printf("%d\n", i - prv[sum]);
            for(int j = prv[sum];j < i;j++)  {
                printf("%d\n", v[j]);
            }
            return 0;
        }
        prv[sum] = i;
    }
    return 0;
}