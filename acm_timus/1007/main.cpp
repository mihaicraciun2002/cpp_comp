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
#include <string>

// START CODE HERE

int N;

inline void solveToRemove(std::string &s)  {
    int rightOne;
    rightOne = 0;
    int numberOnes = 0;
    int posSum = 0, pos = 0;
    for(const auto& x : s)
        numberOnes += (x == '1'), ++pos, posSum += (x == '1') * pos;
    rightOne = numberOnes;
    pos = 0;
    for(int i = 0;i < s.length();i++)  {
        ++pos;
        int substract = 0;
        if(s[i] == '1')
            rightOne--, substract = pos;

        if((posSum - rightOne - substract) % (N + 1) == 0)  {
            std::string aux;
            for(int j = 0;j < i;j++)
                aux.push_back(s[j]);
            for(int j = i + 1;j < s.length();j++)
                aux.push_back(s[j]);
            s = aux;
            return;
        }
    }
}

inline void solveToReplace(std::string &s)  {
    int posSum = 0, pos = 0;
    for(const auto& x : s)
        ++pos, posSum += (x == '1') * pos;
    pos = 0;
    for(int i = 0;i < s.length();i++)  {
        ++pos;
        if(s[i] == '0')
            continue;
        if((posSum - pos) % (N + 1) == 0)  {
            s[i] = '0';
            return;
        }
    }
}

inline void solveToAdd(std::string &s)  {
    int posSum = 0, pos = 0;
    int rightOne = 0;
    for(const auto& x : s)
        ++pos, posSum += (x == '1') * pos, rightOne += (x == '1');
    pos = 0;
    // Try and add to the left of i
    for(int i = 0;i <= s.length();i++)  {
        ++pos;
        // Try adding a zero
        if((rightOne + posSum) % (N + 1) == 0)  {
            std::string aux;
            for(int j = 0;j < i;j++)
                aux.push_back(s[j]);
            aux.push_back('0');
            for(int j = i;j < s.length();j++)
                aux.push_back(s[j]);
            s = aux;
            return;
        }
        // Try adding a one
        if((rightOne + posSum + pos) % (N + 1) == 0)  {
            std::string aux;
            for(int j = 0;j < i;j++)
                aux.push_back(s[j]);
            aux.push_back('1');
            for(int j = i;j < s.length();j++)
                aux.push_back(s[j]);
            s = aux;
            return;
        }
        if(i < s.length() && s[i] == '1')
            rightOne--;
    }
}

inline bool solve()  {
    std::string s;
    std::cin >> s;
    if(s.length() == 0)
        return false;
    assert(s.length() == s.size());
    if(s.length() == N + 1)  {
        solveToRemove(s);
    }else if(s.length() == N){
        solveToReplace(s);
    }else if(s.length() == N - 1){
        solveToAdd(s);
    }
    std::cout << s << "\n";
    return true;
}



// END CODE HERE

int main()  {
    #if USE_MODE
    started_time = std::chrono::high_resolution_clock::now(); freopen("aux.in", "r", stdin);  freopen("aux.out", "w", stdout);
    #endif

// START CODE HERE

    int queryNo;
    std::cin >> N;
    while(solve()) {}


// END CODE HERE

    #if USE_MODE
    endTimeCHRONO();
    #endif
    return 0;
}
