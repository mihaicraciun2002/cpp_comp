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
#include <string>

// START CODE HERE

template <int base>
class bigInt  {
    private:
    std::vector <char> digits;
    public:
    bigInt(){}
    bigInt(const int& no)  {
        int cn = no;
        while(cn)
            digits.push_back(cn % base), cn /= base;
    }
    void operator = (const bigInt <base>& oth)  {
        digits = oth.digits;
    }
    bigInt <base> operator + (const bigInt <base>& oth)  {
        bigInt <base> ans = bigInt <base> (0);
        int rest = 0;
        int index = 0;
        while(index < oth.digits.size() && index < digits.size())  {
            int toPush = oth.digits[index] + digits[index] + rest;
            rest = toPush / base;
            toPush %= base;
            ans.digits.push_back(toPush);
            index++;
        }
        while(index < oth.digits.size())  {
            int toPush = oth.digits[index] + rest;
            rest = toPush / base;
            toPush %= base;
            ans.digits.push_back(toPush);
            index++;
        }
        while(index < digits.size())  {
            int toPush = digits[index] + rest;
            rest = toPush / base;
            toPush %= base;
            ans.digits.push_back(toPush);
            index++;
        }
        while(rest)  {
            ans.digits.push_back(rest % base);
            rest /= base;
        }
        return ans;
    }
    bigInt <base> operator * (const int& factor)  {
        bigInt <base> ans = bigInt <base> (0);
        int rest = 0;
        for(int i = 0;i < digits.size();i++)  {
            int toPush = (digits[i]) * factor + rest;
            rest = toPush / base;
            toPush %= base;
            ans.digits.push_back(toPush);
        }
        while(rest)  {
            ans.digits.push_back(rest % base);
            rest /= base;
        }
        return ans;
    }
    std::string show()  {
        std::string ans;
        if(digits.size() == 0)  {
            ans.push_back('0');
            return ans;
        }
        for(int i = digits.size() - 1;i >= 0;i--)  {
            ans.push_back(digits[i] + '0');
        }
        return ans;
    }
};



// END CODE HERE

int main()  {
    #if USE_MODE
    started_time = std::chrono::high_resolution_clock::now(); freopen("aux.in", "r", stdin);  freopen("aux.out", "w", stdout);
    #endif

// START CODE HERE

    int N, K;
    std::cin >> N >> K;

    bigInt <10> prev[2];
    prev[1] = bigInt <10> (K - 1);

    for(int i = 2;i <= N;i++)  {
        bigInt <10> aux[2];
        aux[0] = prev[1];
        aux[1] = prev[0] + prev[1];
        aux[1] = aux[1] * (K - 1);
        prev[0] = aux[0];
        prev[1] = aux[1];
    }

    std::cout << (prev[0] + prev[1]).show() << "\n";

// END CODE HERE

    #if USE_MODE
    endTimeCHRONO();
    #endif
    return 0;
}
