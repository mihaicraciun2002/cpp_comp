#define CHRONO_IN 0
#if CHRONO_IN
#include <chrono>
#endif
// INCLUDES
//######################################//
#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
#include <cctype>
#include <iostream>

//######################################//
// START CODE HERE
//######################################//

//######################################//
// END CODE HERE
//######################################//
#define EASY_IO 0


int main()  {
    #if CHRONO_IN
    auto started_time = std::chrono::high_resolution_clock::now();
    #endif
    #if EASY_IO
    freopen("aux.in", "r", stdin);
    freopen("aux.out", "w", stdout);
    #endif
//######################################//
// START CODE HERE
//######################################//


//######################################//
// END CODE HERE
//######################################//
    #if CHRONO_IN
    auto finished_time = std::chrono::high_resolution_clock::now();
    std::cerr << "Time elapsed (s):\n";
    std::cerr << (double)std::chrono::duration_cast<std::chrono::milliseconds>(finished_time - started_time).count() / 1000.0 << "\n";
    #endif
    return 0;
}
