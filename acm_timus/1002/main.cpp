#include <iostream>
#include <string>
#include <vector>

int coresp[] = {2, 2, 2, 3, 3, 3, 4, 4, 1, 1,
    5, 5, 6, 6, 0, 7, 0, 7, 7, 8, 8, 8, 9, 9, 9, 0};

inline int proc(char ch)  {
    return coresp[ch - 'a'];
}

inline bool solve()  {
    std::string m;
    std::cin >> m;
    if(m == "-1")  {
        return false;
    }
    m.insert(0, 1, 0);
    for(int i = 1;i < m.size();i++)
        m[i] -= '0';
    int nCount;
    std::cin >> nCount;
    std::vector <std::string> n(nCount);
    for(auto &x : n)
        std::cin >> x, x.insert(0, 1, 0);
    std::vector <std::vector <int>> pi(nCount);
    for(int i = 0;i < nCount;i++)  {
        pi[i].resize(n[i].size());
        std::fill(pi[i].begin(), pi[i].end(), 0);
        for(int j = 2;j < n[i].size();j++)  {
            int k = pi[i][j - 1];
            while(k > 0 && n[i][k + 1] != n[i][j])
                k = pi[i][k];
            if(n[i][k + 1] == n[i][j])
                k++;
            pi[i][j] = k;
        }
    }
    std::vector <int> d(m.size(), 1e9);
    std::vector <int> prev(m.size(), 0);
    std::vector <int> q(nCount, 0);
    d[0] = 0;
    for(int mIndex = 1;mIndex < m.size();mIndex++)  {
        for(int i = 0;i < nCount;i++)  {
            while(q[i] > 0 && proc(n[i][q[i] + 1]) != m[mIndex])  {
                q[i] = pi[i][q[i]];
            }
            if(proc(n[i][q[i] + 1]) == m[mIndex])
                q[i]++;
            if(q[i] == n[i].size() - 1)  {
                int pos = mIndex - q[i];
                if(d[mIndex] > d[pos] + 1)  {
                    d[mIndex] = d[pos] + 1;
                    prev[mIndex] = i;
                }
            }
        }
    }
    if(d[m.size() - 1] < 1e9)  {
        int index = m.size() - 1;
        std::vector <int> answerIndexes;
        while(index)  {
            answerIndexes.push_back(prev[index]);
            index -= n[prev[index]].size() - 1;
        }
        for(int i = answerIndexes.size() - 1;i >= 0;i--)  {
            for(int j = 1;j < n[answerIndexes[i]].size();j++)
                std::cout << n[answerIndexes[i]][j];
            std::cout << ' ';
        }
        std::cout << "\n";
    }else{
        std::cout << "No solution.\n";
    }
    return true;
}

#define EASY_IO 0

int main()  {
    #if EASY_IO
    freopen("aux.in", "r", stdin);
    freopen("aux.out", "w", stdout);
    #endif
    while(solve())  {}
    return 0;
}