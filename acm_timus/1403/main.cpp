#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <utility>

class order  {
    public:
    int time;
    int value;
    int index;
};

int N;
std::vector <order> orders;

bool cmp(const order &a, const order &b)  {
    if(a.value == b.value)  {
        return a.time < b.time;
    }
    return a.value > b.value;
}

std::vector <std::pair <int, int>> ans;

const int maxTime = 1e5 + 1;

std::set <int> timeHelper;

int main()  {
    scanf("%d", &N);
    for(int i = 0;i < N;i++)  {
        int time, value, index;
        scanf("%d%d", &time, &value);
        index = i + 1;
        orders.push_back({time, value, index});
    }
    std::sort(orders.begin(), orders.end(), cmp);
    for(int i = 1;i < maxTime;i++)
        timeHelper.insert(-i);
    for(const auto& x : orders)  {
        if(timeHelper.lower_bound(-x.time) != timeHelper.end())  {
            ans.push_back(std::make_pair(x.time, x.index));
            timeHelper.erase(timeHelper.lower_bound(-x.time));
        }
    }
    std::sort(ans.begin(), ans.end());
    printf("%d\n", ans.size());
    for(const auto &orderID : ans)  {
        printf("%d ", orderID.second);
    }
    printf("\n");
    return 0;
}