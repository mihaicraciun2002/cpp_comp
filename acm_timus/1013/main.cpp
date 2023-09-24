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

long long N, K, M;

long long mul(long long A, long long B)  {
    long long powA = A;
    long long ans = 0LL;
    while(B)  {
        if(B % 2LL)  {
            ans += powA;
            ans %= M;
        }
        powA = powA * 2LL;
        powA %= M;
        B /= 2LL;
    }
    return ans;
}

template <typename T>
class matrix  {
    public:
    T d[2][2] = {};
    matrix(){}
    matrix(const T& a, const T& b, const T& c, const T& d)  {
        this -> d[0][0] = a % M;
        this -> d[0][1] = b % M;
        this -> d[1][0] = c % M;
        this -> d[1][1] = d % M;
    }
    matrix operator *(const matrix& oth)  {
        matrix ans;
        for(int i = 0;i < 2;i++)  {
            for(int j = 0;j < 2;j++)  {
                for(int k = 0;k < 2;k++)
                    ans.d[i][j] += mul(d[i][k], oth.d[k][j]), ans.d[i][j] %= M;
            }
        }

        return ans;
    }
    matrix pow(const long long& exp)  {
        matrix ans(1LL, 0LL, 0LL, 1LL);
        matrix aux(d[0][0], d[0][1], d[1][0], d[1][1]);
        long long expCp = exp;
        while(expCp)  {
            if(expCp % 2LL)  {
                ans = ans * aux;
            }
            aux = aux * aux;
            expCp /= 2LL;
        }
        return ans;
    }
    inline void print()  {
        for(int i = 0;i < 2;i++)  {
            for(int j = 0;j < 2;j++)
                std::cerr << d[i][j] << " ";
            std::cerr << '\n';
        }
    }
};



// END CODE HERE

int main()  {
    #if USE_MODE
    started_time = std::chrono::high_resolution_clock::now(); freopen("aux.in", "r", stdin);  freopen("aux.out", "w", stdout);
    #endif

// START CODE HERE



    std::cin >> N >> K >> M;
    matrix <long long> mt = matrix<long long>(0, K - 1, 1, K - 1);
    mt = mt.pow(N - 1);


    long long a = 0, b = K - 1;
    long long c, d;
    c = mul(a, mt.d[0][0]) + mul(b, mt.d[1][0]);
    c %= M;
    d = mul(a, mt.d[0][1]) + mul(b, mt.d[1][1]);
    d %= M;

    std::cout << (c + d) % M << "\n";

// END CODE HERE

    #if USE_MODE
    endTimeCHRONO();
    #endif
    return 0;
}
