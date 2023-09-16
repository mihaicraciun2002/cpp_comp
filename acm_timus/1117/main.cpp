#include <cstdio>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <climits>

#define SOLVE_PROBLEM 1
#define TESTING_PROBLEM !SOLVE_PROBLEM

long long N, M;
long long ans;
long long levels[32];


inline int level(const long long &nr)  {
    int lvl = 0;
    auto cnr = nr;
    while(cnr)  {
        if(cnr & 1LL)
            break;
        lvl++;
        cnr >>= 1;
    }
    return lvl;
}

inline long long nextPow(const long long &nr)  {
    long long power = 1LL;
    while(power < nr)
        power <<= 1LL;
    return power;
}

long long road(const long long &N)  {
    if(N <= 2)  {
        return 0;
    }
    long long start = 1;
    long long pp = nextPow(N) / 2;
    if(pp * 2 == N)  {
        return levels[level(pp)] + level(pp);
    }
    return levels[level(pp)] - (levels[level(pp) - 1] - road(N - pp));
}

int main()  {
    #if SOLVE_PROBLEM
    std::scanf("%lld%lld", &N, &M);
    if(N > M)
        std::swap(N, M);
    #endif
    levels[1] = 0;
    for(int i = 2;i <= 31;i++)  {
        levels[i] = levels[i - 1] * 2LL + 2LL * (i - 1);
        // std::cerr << levels[i] << "\n";
    }
    #if SOLVE_PROBLEM
    std::printf("%lld", road(M) - road(N));
    #endif

    #if TESTING_PROBLEM
    std::ifstream fin("test.txt");
    static int test_no = 0;
    while(!fin.eof())  {
        test_no++;
        long long m, n, ans;
        fin >> m >> n >> ans;
        if(m > n)
            std::swap(m, n);
        if(ans != road(n) - road(m))  {
            std::cerr << "Wrong answer on test: " << test_no << "\n";
            std:: cerr << "Test details: " << ans << " " << road(n) - road(m) << "\n";
        }
    }
    #endif
    return 0;
}