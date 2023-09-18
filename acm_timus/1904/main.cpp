#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>

#define EASY_IO 1

const int maxn = 10 + 1;

int n;
int v[maxn];

std::vector <std::pair <int, int>> ans, aux;

int main()  {
    #if EASY_IO
    freopen("1904.in", "r", stdin);
    #endif
    scanf("%d", &n);
    for(int i = 1;i <= n;i++)
        scanf("%d", &v[i]);
    if(v[n] < -1)  {
        printf("0\n");
        return 0;
    }
    ans.push_back(std::make_pair(std::max(0, v[n] - 1), v[n] + 1));
    for(int i = n - 1;i >= 1;i--)  {
        int t = v[i];
        aux.clear();
        for(const auto &range : ans)  {
            int a, b;
            a = range.first, b = range.second;
            if(i == 1)  {
                aux.push_back(std::make_pair(-b + t, -a + t));
                aux.push_back(std::make_pair(a + t, b + t));
            }else{
                if(b - t >= 0)  {
                    aux.push_back(std::make_pair(-b + t, -a + t));
                }else if(-a + t >= 0)  {
                    aux.push_back(std::make_pair(0, -a + t));
                }
                if(a + t >= 0)  {
                    aux.push_back(std::make_pair(a + t, b + t));
                }else if(b + t >= 0)  {
                    aux.push_back(std::make_pair(0, b + t));
                }
            }
        }
        ans = aux;
    }
    aux.clear();
    std::sort(ans.begin(), ans.end());
    aux.push_back(ans[0]);
    for(int i = 1;i < ans.size();i++)  {
        int curra = ans[i].first, currb = ans[i].second;
        if(curra <= aux.back().second)  {
            aux.back().second = std::max(currb, aux.back().second);
        }else{
            aux.push_back(ans[i]);
        }
    }
    ans = aux;
    printf("%zu\n", ans.size());
    for(const auto &range : ans)  {
        printf("%d %d\n", range.first, range.second);
    }
    return 0;
}