#include <cstdio>
#include <iostream>
#include <stack>
#include <algorithm>

const int maxA = 99 + 1;
const int maxB = 999 + 1;
const int maxn = 1e6 + 1;

int vfA[2][maxA];
int vfB[3][maxB];

bool auxA[2][maxA]; // auxiliary frequency
bool auxB[3][maxB]; // auxiliary frequency

int extinsA[2][maxA];
int extinsB[3][maxB];

int N;
char s[maxn];



inline int decod(int nrCifre, int i)  {
    int nr = 0;
    while(nrCifre--)
        nr = nr * 10 + s[i++] - '0';
    return nr;
}

int main()  {
    freopen("text5.in", "r", stdin);
    freopen("text5.out", "w", stdout);
    scanf("%d%s", &N, &s);
    for(int i = 0;i + 1 < N;i++)
        vfA[i % 2][decod(2, i)] = i,
        extinsA[i % 2][decod(2, i)] = i;
    for(int i = 0;i + 2 < N;i++)
        vfB[i % 3][decod(3, i)] = i,
        extinsB[i % 3][decod(3, i)] = i;
    std::stack <int> auxStack;
    for(int offset = 0;offset < 2;offset++)  {
        auxStack = std::stack <int> ();
        for(int i = N - 1 - 1 - offset;i >= 0;i -= 2)  {
            int curr = decod(2, i);
            if(auxA[i % 2][curr])  {
if(offset == 1)
{                    std::cerr << curr << "\n";
                    std::stack <int> cpy = auxStack;
                    while(!cpy.empty())
                        std::cerr << cpy.top() << " ", cpy.pop();
                    std::cerr << "\n";
                }
                while(!auxStack.empty() && auxStack.top() != curr)  {
                    extinsA[i % 2][curr] = 
                        std::max(extinsA[i % 2][curr],
                        extinsA[i % 2][auxStack.top()]);
                    auxStack.pop();
                }
            }else{
                auxA[i % 2][curr] = true;
                auxStack.push(curr);
            }
        }
    }
    for(int offset = 0;offset < 3;offset++)  {
        auxStack = std::stack <int> ();
        for(int i = N - 1 - 2 - offset;i >= 0;i -= 3)  {
            int curr = decod(3, i);
            if(auxB[i % 3][curr])  {
                while(auxStack.top() != curr)  {
                    extinsB[i % 3][curr] = 
                        std::max(extinsB[i % 3][curr],
                        extinsB[i % 3][auxStack.top()]);
                    auxStack.pop();
                }
            }else  {
                auxB[i % 3][curr] = true;
                auxStack.push(curr);
            }
        }
    }
    return 0;
}