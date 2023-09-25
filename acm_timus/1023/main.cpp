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
#include <cmath>
#include <algorithm>

// START CODE HERE





// END CODE HERE

int main()  {
    #if USE_MODE
    started_time = std::chrono::high_resolution_clock::now(); freopen("aux.in", "r", stdin);  freopen("aux.out", "w", stdout);
    #endif

// START CODE HERE

    int K;
    std::cin >> K;
    int p = 3;
    int sq = (int)sqrt(K);
    while(p <= sq || (p <= K && p <= 9))  {
        if(K % p == 0)
            break;
        p++;
    }

    if(K % p != 0)  {
        p = K;
    }

    if(K % 2 == 0 && K >= 6)  {
        p = std::min(p, K / 2);
    }

    std::cout << p - 1 << "\n";

// END CODE HERE

    #if USE_MODE
    endTimeCHRONO();
    #endif
    return 0;
}
