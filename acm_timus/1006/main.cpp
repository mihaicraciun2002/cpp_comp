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
#include <fstream>
#include <cassert>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <algorithm>
#include <cassert>

// START CODE HERE

const int maxColumn = 50 + 1;
const int maxLine = 20 + 1;

const unsigned char leftUpper = 218;
const unsigned char rightUpper = 191;
const unsigned char rightBottom = 217;
const unsigned char leftBottom = 192;
const unsigned char verticalBar = 179;
const unsigned char horizontalBar = 196;
const unsigned char star = '*';
const unsigned char dot = '.';

int realCharCount = 0;
const unsigned char specialChars[] = {0, leftUpper, rightUpper, rightBottom, leftBottom, verticalBar, horizontalBar, '*'};
const int dx[] = {0, 1,  0, -1};
const int dy[] = {1, 0, -1,  0};
unsigned char grid[maxLine][maxColumn + 1];
unsigned char uCharacterCode[256];
int evalIndex;

inline bool isOriginal(const unsigned char& ch)  {
    return (uCharacterCode[ch] >= 1 && uCharacterCode[ch] <= 6);
}

class square  {
    public:
    int X;
    int Y;
    int length;
    double realRatio = 0;
    int realCount = 0;
    int lastEval = 0;
    private:
    inline double evaluateCompleteness()  {
        realCount = 0;
        int currX = X, currY = Y;
        for(int dir = 0;dir < 4;dir++)  {
            realCount += (grid[currX][currY] == specialChars[dir + 1]);
            currX += dx[dir];
            currY += dy[dir];
            unsigned char barChar = specialChars[6 - dir % 2];
            for(int index = 1;index + 1 < length;index++)  {
                realCount += (grid[currX][currY] == barChar);
                currX += dx[dir];
                currY += dy[dir];
            }
        }
        realRatio = 1.0 * realCount / (length * length - length);
        return realRatio;
    }
    public:
    square(){}
    square(const int& X, const int& Y, const int& length)  {
        this -> X = X;
        this -> Y = Y;
        this -> length = length;
    }
    inline double observeCompleteness()  {
        if(lastEval == evalIndex)  {
            return realRatio;
        }
        lastEval = evalIndex;
        return evaluateCompleteness();
    }
    inline bool isWorthy()  {
        int currX = X, currY = Y;
        for(int dir = 0;dir < 4;dir++)  {
            if(uCharacterCode[grid[currX][currY]] == 0)  {
                assert(grid[currX][currY] == dot);
                return false;
            }
            currX += dx[dir];
            currY += dy[dir];
            unsigned char barChar = specialChars[6 - dir % 2];
            for(int index = 1;index + 1 < length;index++)  {
                if(uCharacterCode[grid[currX][currY]] == 0)  {
                    assert(grid[currX][currY] == dot);
                    return false;
                }
                currX += dx[dir];
                currY += dy[dir];
            }
        }
        return true;
    }
    inline bool canFillYet() const  {
        int currX = X, currY = Y;
        for(int dir = 0;dir < 4;dir++)  {
            if(grid[currX][currY] != specialChars[dir + 1] && grid[currX][currY] != star)
                return false;
            currX += dx[dir];
            currY += dy[dir];
            unsigned char barChar = specialChars[6 - dir % 2];
            for(int index = 1;index + 1 < length;index++)  {
                if(grid[currX][currY] != barChar && grid[currX][currY] != star)
                    return false;
                currX += dx[dir];
                currY += dy[dir];
            }
        }
        return true;
    }
    inline void fillGrid()  {
        int currX = X, currY = Y;
        for(int dir = 0;dir < 4;dir++)  {
            realCharCount -= isOriginal(grid[currX][currY]);
            grid[currX][currY] = star;
            currX += dx[dir];
            currY += dy[dir];
            unsigned char barChar = specialChars[6 - dir % 2];
            for(int index = 1;index + 1 < length;index++)  {
                realCharCount -= isOriginal(grid[currX][currY]);
                grid[currX][currY] = star;
                currX += dx[dir];
                currY += dy[dir];
            }
        }
    }
    bool operator ==(const square& oth) const  {
        return (oth.X == X && oth.Y == Y && oth.length == length);
    }
};

std::vector <square> squares;
std::vector <square> ans;

namespace myfunc  {
    inline double abs(const double& a)  {
        if(a >= 0.0)
            return a;
        return -a;
    }
}

bool cmp(square& a, square& b)  {
    if(myfunc::abs(a.observeCompleteness() - b.observeCompleteness()) < 1e-9)
        return a.length < b.length;
    return a.observeCompleteness() < b.observeCompleteness();
}

#define ATTEMPT_SHORTENING 0

inline void extractSquare()  {
    evalIndex++;
    #if ATTEMPT_SHORTENING
    std::vector <int> toErase;
    for(int i = 0;i < squares.size();i++)  {
        squares[i].observeCompleteness();
        if(squares[i].realCount == 0)  {
            toErase.push_back(i);
        }
    }
    for(const auto& x : toErase)  {
        std::swap(squares[x], squares.back());
        squares.pop_back();
    }
    #endif
    std::vector <square> actualSquares;
    for(const auto& x : squares)  {
        if(x.canFillYet())
            actualSquares.push_back(x);
    }
    std::sort(actualSquares.begin(), actualSquares.end(), cmp);
    square& toExtract = actualSquares.back();
    ans.push_back(toExtract);
    toExtract.fillGrid();
    for(int i = 0;i < squares.size();i++)  {
        if(squares[i] == toExtract)  {
            std::swap(squares[i], squares.back());
            squares.pop_back();
            break;
        }
    }
}

// END CODE HERE

int main()  {
    #if USE_MODE
    started_time = std::chrono::high_resolution_clock::now();
    freopen("aux.in", "r", stdin);
    freopen("aux.out", "w", stdout);
    #endif

// START CODE HERE

    for(int i = 1;i <= 7;i++)
        uCharacterCode[specialChars[i]] = i;

    for(int i = 1;i < maxLine;i++)  {
        std::cin >> grid[i] + 1;
    }

    for(int i = 1;i < maxLine;i++)
        for(int j = 1;j < maxColumn;j++)  {
            if(uCharacterCode[grid[i][j]])  {
                realCharCount++;
            }
        }

    for(int i = 1;i < maxLine;i++)
        for(int j = 1;j < maxColumn;j++)  {
            for(int length = 2;length <= 20;length++)  {
                if(i + length - 1 >= maxLine || j + length - 1 >= maxColumn)  {
                    continue;
                }
                square candidate = square(i, j, length);
                if(candidate.isWorthy())  {
                    squares.push_back(candidate);
                }
            }
        }

    while(realCharCount)  {
        extractSquare();
    }

    std::reverse(ans.begin(), ans.end());
    std::cout << ans.size() << "\n";

    for(const auto &solSquare : ans)  {
        std::cout << solSquare.Y - 1 << " " << solSquare.X - 1 << " " << solSquare.length << "\n";
    }

// END CODE HERE

    #if USE_MODE
    endTimeCHRONO();
    #endif
    return 0;
}