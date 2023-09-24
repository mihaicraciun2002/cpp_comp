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

namespace ll  {
    inline long long abs(const long long& x)  {
        if(x >= 0)
            return x;
        return -x;
    }
}



// END CODE HERE

int main()  {
    #if USE_MODE
    started_time = std::chrono::high_resolution_clock::now(); freopen("aux.in", "r", stdin);  freopen("aux.out", "w", stdout);
    #endif

// START CODE HERE
    int N;
    std::cin >> N;
    long long v[N + 1];

    for(int i = 1;i <= N;i++)
        std::cin >> v[i];

    long long bestGradient = ll::abs(v[2] - v[1]);
    int bestLeft = 1, bestRight = 2;

    int prev = 1;

    for(int i = 3;i <= N;i++)  {
        const long long currentGradient = v[i] - v[i - 1];
        while(prev <= i - 2 && v[prev + 1] - v[prev] >= currentGradient)
            prev++;
        if(currentGradient > 0LL)  {
            if(currentGradient > bestGradient)  {
                bestGradient = currentGradient;
                bestLeft = i - 1, bestRight = i;
            }
        }else  {
            if(-currentGradient > bestGradient)  {
                bestGradient = -currentGradient;
                bestLeft = prev, bestRight = i;
            }
        }
    }

    std::cout << bestLeft << " " << bestRight << "\n";


// END CODE HERE

    #if USE_MODE
    endTimeCHRONO();
    #endif
    return 0;
}
