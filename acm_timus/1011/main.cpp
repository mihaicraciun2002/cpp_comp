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
#include <cassert>

// START CODE HERE





// END CODE HERE

int main()  {
    #if USE_MODE
    started_time = std::chrono::high_resolution_clock::now(); freopen("aux.in", "r", stdin);  freopen("aux.out", "w", stdout);
    #endif

// START CODE HERE

    double aD, bD;
    std::cin >> aD >> bD;
    assert(aD <= bD);

    int a, b;
    a = (int)((aD + 1e-9) * 100.0);
    b = (int)((bD + 1e-9) * 100.0);

    int limit = (int)1e4;

    for(int y = 1;y <= limit * 2;y++)  {
        int ay = a * y;
        int by = b * y;

        int t = (ay / limit + 1) * limit;
        if(t < by)  {
            std::cout << y << "\n";
            return 0;
        }
    }


// END CODE HERE

    #if USE_MODE
    endTimeCHRONO();
    #endif
    return 0;
}
