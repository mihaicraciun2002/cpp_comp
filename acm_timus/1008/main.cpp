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
#include <utility>
#include <cctype>
#include <vector>
#include <algorithm>

// START CODE HERE

char lineBuffer[1000];
int lineBufferSize = 0;

inline void readLine()  {
    lineBufferSize = 0;
    char ch = fgetc(stdin);
    while(ch != '\n' && ch != EOF)  {
        lineBuffer[lineBufferSize++] = ch;
        ch = fgetc(stdin);
    }
}

inline bool isEOF()  {
    return (lineBufferSize == 0);
}

inline int countSpaces()  {
    int spacesCount = 0;
    for(int index = 0;index < lineBufferSize;index++)
        spacesCount += (lineBuffer[index] == ' ');
    return spacesCount;
}

int readIntIndex = 0;
inline int readInt()  {
    if(readIntIndex == lineBufferSize)  {
        readIntIndex = 0;
        readLine();
    }
    int ans = 0;
    while(readIntIndex < lineBufferSize && !isdigit(lineBuffer[readIntIndex]))  {
        readIntIndex++;
    }
    while(readIntIndex < lineBufferSize && isdigit(lineBuffer[readIntIndex]))  {
        ans = ans * 10 + lineBuffer[readIntIndex] - '0';
        readIntIndex++;
    }
    return ans;
}

const int maxGrid = 10 + 2;

bool viz[maxGrid][maxGrid];
int N;

const int dx[] = {1, 0, -1,  0};
const int dy[] = {0, 1,  0, -1};
char directionChar[] = {'R', 'T', 'L', 'B'};
int inverseDirectionChar[256];

inline void solveFirstToSecond()  {
    N = readInt();
    int firstX, firstY, pointsLeft = N;
    for(int i = 1;i <= N;i++)  {
        int x, y;
        x = readInt(), y = readInt();
        viz[x][y] = true;
        if(i == 1)
            firstX = x, firstY = y;
    }
    std::vector <std::pair <int, int>> Q;
    int qIndex = 0;
    Q.push_back(std::make_pair(firstX, firstY));
    viz[firstX][firstY] = 0;
    std::cout << firstX << " " << firstY << "\n";
    while(pointsLeft && qIndex < Q.size())  {
        pointsLeft--;
        std::pair <int, int> front = Q[qIndex++];
        for(int dir = 0;dir < 4;dir++)  {
            if(viz[front.first + dx[dir]][front.second + dy[dir]])  {
                std::cout << directionChar[dir];
                Q.push_back(std::make_pair(front.first + dx[dir], front.second + dy[dir]));
                viz[front.first + dx[dir]][front.second + dy[dir]] = false;
            }
        }
        if(pointsLeft)
            std::cout << ",\n";
        else
            std::cout << ".\n";
    }
}

inline void solveSecondtoFirst()  {
    inverseDirectionChar['R'] = 0;
    inverseDirectionChar['T'] = 1;
    inverseDirectionChar['L'] = 2;
    inverseDirectionChar['B'] = 3;
    int firstX, firstY;
    firstX = readInt();
    firstY = readInt();
    std::vector <std::pair <int, int>> Q;
    std::vector <std::pair <int, int>> ans;
    int qIndex = 0;
    Q.push_back(std::make_pair(firstX, firstY));
    readLine();
    while(!isEOF())  {
        firstX = Q[qIndex].first;
        firstY = Q[qIndex].second;
        qIndex++;
        for(int i = 0;i + 1 < lineBufferSize;i++)  {
            int dirCode = inverseDirectionChar[lineBuffer[i]];
            int obtainedX = firstX + dx[dirCode];
            int obtainedY = firstY + dy[dirCode];
            Q.push_back(std::make_pair(obtainedX, obtainedY));
        }
        readLine();
    }
    std::cout << Q.size() << "\n";
    std::sort(Q.begin(), Q.end());
    for(const auto& point : Q)
        std::cout << point.first << " " << point.second << "\n";
}

// END CODE HERE

int main()  {
    #if USE_MODE
    started_time = std::chrono::high_resolution_clock::now(); freopen("aux.in", "r", stdin);  freopen("aux.out", "w", stdout);
    #endif

// START CODE HERE
    readLine();
    if(countSpaces() == 0)  {
        solveFirstToSecond();
    }else{
        solveSecondtoFirst();
    }

// END CODE HERE

    #if USE_MODE
    endTimeCHRONO();
    #endif
    return 0;
}
