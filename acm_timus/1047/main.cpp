#define CHRONO_IN 0
#if CHRONO_IN
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
#include <vector>

// START CODE HERE

int N;
double a0, an1;
std::vector <double> c({0.0});


// END CODE HERE

#define EASY_IO 0

int main()  {
    #if CHRONO_IN
    started_time = std::chrono::high_resolution_clock::now();
    #endif
    #if EASY_IO
    freopen("aux.in", "r", stdin);  freopen("aux.out", "w", stdout);
    #endif

// START CODE HERE

    std::cin >> N >> a0 >> an1;
    for(int i = 1;i <= N;i++)  {
        double x;
        std::cin >> x;
        c.push_back(x * 2.0);
    }

    double b1 = an1 - a0;
    for(int i = 1;i <= N;i++)  {
        b1 -= c[i] * (1.0 * N + 1.0 - 1.0 * i);
    }
    b1 /= 1.0 * (N + 1);
    printf("%.2lf\n", b1 + a0);

// END CODE HERE

    #if CHRONO_IN
    endTimeCHRONO();
    #endif
    return 0;
}