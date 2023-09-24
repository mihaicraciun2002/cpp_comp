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
#include <vector>
#include <algorithm>
#include <map>
#include <cassert>

// START CODE HERE

int oth[] = {0, 2, 1, 5, 6, 3, 4};



// END CODE HERE

int main()  {
    #if USE_MODE
    started_time = std::chrono::high_resolution_clock::now(); freopen("aux.in", "r", stdin);  freopen("aux.out", "w", stdout);
    #endif

// START CODE HERE

    int N;
    std::cin >> N;
    int cntSol = 0;
    std::map <std::vector <int>, std::vector <int>> vf;
    std::map <int, std::vector <int>> order;
    for(int index = 1;index <= N;index++)  {
        std::vector <int> v(7, 0);
        int pos1 = 0;
        for(int j = 1;j <= 6;j++)  {
            std::cin >> v[j];
            if(v[j] == 1)
                pos1 = j;
        }
        int othPos = oth[pos1];
        if(pos1 != 1 && pos1 != 2)  {
            if(pos1 == 4 || pos1 == 6)  {
                std::swap(v[pos1], v[1]);
                std::swap(v[othPos], v[2]);
                std::swap(v[pos1], v[othPos]);
            }else{
                std::swap(v[pos1], v[1]);
                std::swap(v[othPos], v[2]);
                std::swap(v[pos1], v[othPos]);
            }
        }
        int parity = 1;
        if(v[1] > v[2])
            parity = -1;
        int perm[4];
        int posMin = 3;
        for(int i = 3;i <= 6;i++)  {
            if(v[i] < v[posMin])
                posMin = i;
        }
        int cnt = 1;
        for(int i = posMin;cnt <= 4;)  {
            assert(i >= 3 && i <= 6);
            perm[cnt - 1] = v[i];
            i = (i - 3 + parity + 4) % 4 + 3;
            cnt++;
        }
        std::vector <int> content;
        content.push_back(1);
        content.push_back(v[2] + v[1] - 1);
        for(int i = 0;i < 4;i++)
            content.push_back(perm[i]);
        if(vf[content].size() == 0)  {
            cntSol++;
            order[index] = content;
        }
        vf[content].push_back(index);
    }

    std::cout << cntSol << "\n";
    for(const auto& x : order)  {
        std::sort(vf[x.second].begin(), vf[x.second].end());
        for(const auto& y : vf[x.second])
            std::cout << y << " ";
        std::cout << "\n";
    }


// END CODE HERE

    #if USE_MODE
    endTimeCHRONO();
    #endif
    return 0;
}
