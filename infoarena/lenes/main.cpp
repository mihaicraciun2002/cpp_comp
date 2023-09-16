#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>

const int bufsize = 4096;
int bufCounter = bufsize;
char buffer[bufsize];

inline char nextCh()  {
    if(bufCounter == bufsize)  {
        fread(buffer, sizeof(char), bufsize, stdin);
        bufCounter = 0;
    }
    return buffer[bufCounter++];
}

inline void readInt(int &number)  {
    char ch = nextCh();
    number = 0;
    while(isdigit(ch))  {
        number = number * 10 + ch - '0';
        ch = nextCh();
    }
}


const int maxn = 500 + 1;
const int maxm = 500 + 1;

int p;

int M, N, k1, k2;

std::vector <int> a[maxm];

int sumk1[maxm];
int sumk2[maxm];
int sumTot[maxm];

int sumSidek1[maxm];
int sumSidek2[maxm];

int ans = 1e9;

inline void solve1()  {
    for(int i = 2;i < M;i++)  {
        int cntL = 1, cntR = 1, cntTot = 0;
        while(cntTot < k1)  {
            if(a[i - 1][cntL] < a[i + 1][cntR])  {
                sumk1[i] += a[i - 1][cntL];
                cntL++;
            }else{
                sumk1[i] += a[i + 1][cntR];
                cntR++;
            }
            cntTot++;
        }
    }
    for(int i = 1;i <= k1;i++)
        sumk1[1] += a[2][i],
        sumk1[M] += a[M - 1][i];
    for(int i = 1;i <= M;i++)  {
        ans = std::min(ans, sumTot[i] + sumk1[i]);
    }
}

inline void advance(int lCol, int midCol, int rCol, int& cntL, int& cntMid, int& cntR);
int currSum = 0;
int threshold[3];

inline void solve2()  {
    for(int i = 2;i < M;i++)  {
        int cntL = 1, cntR = 1, cntTot = 0;
        while(cntTot < k1)  {
            if(a[i - 1][cntL] < a[i + 1][cntR])  {
                sumk1[i] += a[i - 1][cntL];
                cntL++;
            }else{
                sumk1[i] += a[i + 1][cntR];
                cntR++;
            }
            cntTot++;
        }
    }
    for(int i = 1;i <= k1;i++)
        sumk1[1] += a[2][i],
        sumk1[M] += a[M - 1][i];

    for(int i = 2;i < M;i++)  {
        int cntL = 1, cntR = 1, cntTot = 0;
        while(cntTot < k2)  {
            if(a[i - 1][cntL] < a[i + 1][cntR])  {
                sumk2[i] += a[i - 1][cntL];
                cntL++;
            }else{
                sumk2[i] += a[i + 1][cntR];
                cntR++;
            }
            cntTot++;
        }
    }
    for(int i = 1;i <= k2;i++)
        sumk2[1] += a[2][i],
        sumk2[M] += a[M - 1][i];

    for(int i = 1;i <= M;i++)  {
        for(int j = 1;j <= k1;j++)
            sumSidek1[i] += a[i][j];
        for(int j = 1;j <= k2;j++)
            sumSidek2[i] += a[i][j];
    }

    for(int i = 1;i <= M;i++)
        for(int j = 1;j <= M;j++)  {
            if(std::abs(i - j) >= 3)  {
                // Daca sunt la distanta > 2
                ans = std::min(ans, sumTot[i] + sumk1[i] + sumTot[j] + sumk2[j]);
            }else if(i == j - 2)  {
                // Daca sunt la distanta exact 2, cu k1 pe dreapta si k2 pe stanga
                int cntL, cntMid, cntR;
                cntL = 1, cntMid = 1, cntR = 1;
                int lCol = i - 1;
                int midCol = i + 1;
                int rCol = j + 1;
                int cntTot = 0;
                currSum = 0;
                threshold[0] = k1;
                threshold[1] = N;
                threshold[2] = k2;
                while(cntTot < k1 + k2)  {
                    advance(lCol, midCol, rCol, cntL, cntMid, cntR);
                    cntTot++;
                }
                ans = std::min(sumTot[i] + sumTot[j] + currSum, ans);
            }else if(j == i - 2)  {
                // Daca sunt la distanta exact 2, cu k2 pe dreapta si k1 pe stanga
                int cntL, cntMid, cntR;
                cntL = 1, cntMid = 1, cntR = 1;
                int lCol = j - 1;
                int midCol = j + 1;
                int rCol = i + 1;
                int cntTot = 0;
                currSum = 0;
                threshold[0] = k2;
                threshold[1] = N;
                threshold[2] = k1;
                while(cntTot < k1 + k2)  {
                    advance(lCol, midCol, rCol, cntL, cntMid, cntR);
                    cntTot++;
                }
                ans = std::min(sumTot[i] + sumTot[j] + currSum, ans);
            }else if(i == j - 1)  {
                // Daca k1 e pe dreapta, k2 e pe stanga si sunt alaturate
                int cntL = 1;
                int cntR = 1;
                int sumk1, sumk2;
                sumk1 = 0, sumk2 = 0;
                if(i == 1 && k1 > 0)
                    continue;
                if(j == M && k2 > 0)
                    continue;
                sumk1 = sumSidek1[i - 1];
                sumk2 = sumSidek2[j + 1];
                ans = std::min(ans, sumTot[i] + sumTot[j] + sumk1 + sumk2);
            }else if(i == j + 1)  {
                // Daca k1 e pe stanga, k2 e pe dreapta si sunt alaturate
                int cntL = 1;
                int cntR = 1;
                int sumk1, sumk2;
                sumk1 = 0, sumk2 = 0;
                if(i == M && k1 > 0)
                    continue;
                if(j == 1 && k2 > 0)
                    continue;
                sumk1 = sumSidek1[i + 1];
                sumk2 = sumSidek2[j - 1];
                ans = std::min(ans, sumTot[i] + sumTot[j] + sumk1 + sumk2);
            }
        }
}

inline bool validCol(int col)  {
    return col >= 1 && col <= M;
}

inline bool validInx(int index, int pos)  {
    return index <= threshold[pos];
}

std::pair <int, char> auxAdv[3];
int auxAdvSz = 0;

inline void advance(int lCol, int midCol, int rCol, int& cntL, int& cntMid, int& cntR)  {
    auxAdvSz = 0;
    if(validCol(lCol) && validInx(cntL, 0))
        auxAdv[auxAdvSz++] = std::make_pair(a[lCol][cntL], 0);
    if(validCol(midCol) && validInx(cntMid, 1))
        auxAdv[auxAdvSz++] = std::make_pair(a[midCol][cntMid], 1);
    if(validCol(rCol) && validInx(cntR, 2))
        auxAdv[auxAdvSz++] = std::make_pair(a[rCol][cntR], 2);
    if(auxAdvSz == 2)  {
        if(auxAdv[0].first > auxAdv[1].first)  {
            swap(auxAdv[0], auxAdv[1]);
        }
    }else if(auxAdvSz == 3)  {
        if(auxAdv[1].first > auxAdv[2].first)  {
            swap(auxAdv[1], auxAdv[2]);
        }
        if(auxAdv[0].first > auxAdv[1].first)  {
            swap(auxAdv[0], auxAdv[1]);
        }
    }
    currSum += auxAdv[0].first;
    switch(auxAdv[0].second)  {
        case 0:
            cntL++;
        break;
        case 1:
            cntMid++;
        break;
        case 2:
            cntR++;
        break;
    }
}

int main()  {
    freopen("lenes.in", "r", stdin);
    freopen("lenes.out", "w", stdout);
    readInt(p);
    // Inversat N si M => N e nr de linii, M nr de coloane
    readInt(N), readInt(M), readInt(k1), readInt(k2);
    for(int i = 1;i <= M;i++)  {
        a[i].resize(N + 1);
    }
    for(int i = 1;i <= N;i++)
        for(int j = 1;j <= M;j++)
            readInt(a[j][i]);
    for(int i = 1;i <= M;i++)  {
        std::sort(a[i].begin() + 1, a[i].end());
        for(int j = 1;j <= N;j++)
            sumTot[i] += a[i][j];
    }
    if(p == 1)  {
        solve1();
    }
    else{
        solve2();
    }
    std::cout << ans << "\n";
    return 0;
}