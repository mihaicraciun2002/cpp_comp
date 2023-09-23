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
#include <algorithm>
#include <vector>

// START CODE HERE

std::vector <char> A, B, ans;
int rest = 0;

// END CODE HERE

int main()  {
    #if USE_MODE
    started_time = std::chrono::high_resolution_clock::now(); freopen("aux.in", "r", stdin);  freopen("aux.out", "w", stdout);
    #endif

// START CODE HERE

    int N;
    std::cin >> N;
    for(int i = 1;i <= N;i++)  {
        int a, b;
        std::cin >> a >> b;
        A.push_back(a);
        B.push_back(b);
    }
    std::reverse(A.begin(), A.end());
    std::reverse(B.begin(), B.end());

    int index = 0;
    while(index < A.size() && index < B.size())  {
        int toPush = A[index] + B[index] + rest;
        rest = toPush / 10;
        toPush %= 10;
        ans.push_back(toPush);
        index++;
    }
    while(index < A.size())  {
        int toPush = A[index] + rest;
        rest = toPush / 10;
        toPush %= 10;
        ans.push_back(toPush);
        index++;
    }
    while(index < B.size())  {
        int toPush = B[index] + rest;
        rest = toPush / 10;
        toPush %= 10;
        ans.push_back(toPush);
        index++;
    }
    if(rest)  {
        ans.push_back(rest);
        rest = 0;
    }
    for(int i = ans.size() - 1;i >= 0;i--)
        std::cout << (int)ans[i];

// END CODE HERE

    #if USE_MODE
    endTimeCHRONO();
    #endif
    return 0;
}