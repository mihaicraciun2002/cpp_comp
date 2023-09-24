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
#include <unordered_map>

// START CODE HERE





// END CODE HERE

int main()  {
    #if USE_MODE
    started_time = std::chrono::high_resolution_clock::now(); freopen("aux.in", "r", stdin);  freopen("aux.out", "w", stdout);
    #endif

// START CODE HERE

    std::unordered_map <int, bool> vf;

    int N;
    std::cin >> N;
    for(int i = 1;i <= N;i++)  {
        int x;
        std::cin >> x;
        vf[x] = true;
    }
    std::cin >> N;
    for(int i = 1;i <= N;i++)  {
        int x;
        std::cin >> x;
        if(vf[(int)1e4 - x] == true)  {
            std::cout << "YES\n";
            return 0;
        }
    }
    std::cout << "NO\n";

// END CODE HERE

    #if USE_MODE
    endTimeCHRONO();
    #endif
    return 0;
}
