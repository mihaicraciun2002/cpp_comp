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
#include <cstring>
#include <string>
#include <utility>
#include <map>
#include <vector>
#include <queue>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <cassert>

// START CODE HERE

const int defaultPerm[] = {0, 1, 2, 3, 4, 5, 6};
const int left[]  = {0, 1, 2, 4, 5, 6, 3};
const int right[] = {0, 1, 2, 6, 3, 4, 5};
const int down[]  = {0, 3, 5, 2, 4, 1, 6};
const int up[]    = {0, 5, 3, 1, 4, 2, 6};
const int dx[] = { 0, 0, -1, 1};
const int dy[] = {-1, 1,  0, 0};
int dirPerm[4][7];
int oppositeDir[] = {1, 0, 3, 2};

class cube  {
    public:
    int faces[7] = {};
    int perm[7] = {0, 1, 2, 3, 4, 5, 6};
    cube(const int faces[])  {
        memcpy(this -> faces, faces, 7 * sizeof(int));
    }
    cube(){}
    inline void applyPermutation(const int perm[])  {
        int aux[7] = {};
        for(int i = 1;i <= 6;i++)  {
            aux[i] = this -> perm[perm[i]];
        }
        memcpy(this -> perm, aux, 7 * sizeof(int));
    }
    inline void printCube()  {
        for(int i = 1;i <= 6;i++)  {
            std::cerr << faces[perm[i]] << " ";
        }
        std::cerr << "\n";
    }
    inline int retrieveBottom()  {
        return faces[perm[5]];
    }
};
#define line first
#define column second

std::map <std::vector <int>, int> d;
std::map <std::vector <int>, bool> viz;
std::map <std::vector <int>, std::vector <int>> prev;

inline std::vector <int> combine(const std::pair <int, int>& pos, int perm[])  {
    std::vector <int> aux;
    aux.push_back(pos.line);
    aux.push_back(pos.column);
    for(int i = 1;i <= 6;i++)
        aux.push_back(perm[i]);
    return aux;
}
inline std::vector <int> combine(const std::pair <int, int>& pos, const int perm[])  {
    std::vector <int> aux;
    aux.push_back(pos.line);
    aux.push_back(pos.column);
    for(int i = 1;i <= 6;i++)
        aux.push_back(perm[i]);
    return aux;
}

// END CODE HERE

int main()  {
    #if USE_MODE
    started_time = std::chrono::high_resolution_clock::now(); freopen("aux.in", "r", stdin);  freopen("aux.out", "w", stdout);
    #endif

// START CODE HERE

    // cube test = cube(new int[7]{0, 0, 8, 1, 2, 1, 1});
    // test.applyPermutation(left);
    // test.printCube();
    // test.applyPermutation(down);
    // test.applyPermutation(right);
    // test.applyPermutation(up);
    // test.applyPermutation(down);
    // test.applyPermutation(left);
    // test.applyPermutation(up);
    // test.applyPermutation(right);
    // test.printCube();

    // cube test = cube(new int[7]{0, 0, 8, 1, 2, 1, 1});
    // test.applyPermutation(new int[7]{0, 4, 6, 2, 5, 1, 3});
    // test.printCube();
    // test.applyPermutation(right);
    // test.printCube();

    // cube test2 = cube(new int[7]{0, 2, 1, 8, 1, 0, 1});
    // test2.applyPermutation(right);
    // test2.printCube();

    // return 0;

    // std::cerr << "\n\n Problem: \n";


    memcpy(dirPerm[0], left, 7 * sizeof(int));
    memcpy(dirPerm[1], right, 7 * sizeof(int));
    memcpy(dirPerm[2], down, 7 * sizeof(int));
    memcpy(dirPerm[3], up, 7 * sizeof(int));

    std::string posStartString, posEndString;
    std::cin >> posStartString >> posEndString;
    std::pair <int, int> start, end;
    start.column = posStartString[0] - 'a' + 1;
    start.line = posStartString[1] - '0';
    end.column = posEndString[0] - 'a' + 1;
    end.line = posEndString[1] - '0';
    int faces[7] = {};
    for(int i = 1;i <= 6;i++)
        std::cin >> faces[i];
    cube initialState = cube(faces);

    std::queue <std::vector <int>> Q;
    auto startQueue = combine(start, defaultPerm);
    Q.push(startQueue);
    viz[startQueue] = true;
    d[startQueue] = faces[5];

    bool once = true;

    while(!Q.empty())  {
        const auto content = Q.front();
        Q.pop();
        const int permutation[] = {0, content[2], content[3], content[4], content[5], content[6], content[7]};
        const std::pair <int, int> nodePos = {content[0], content[1]};
        cube nodeCube = cube(faces);

        nodeCube.applyPermutation(permutation);

        for(int dir = 0;dir < 4;dir++)  {
            int newX = nodePos.line + dx[dir];
            int newY = nodePos.column + dy[dir];
            if(newX < 1 || newX > 8 || newY < 1 || newY > 8)
                continue;
            nodeCube.applyPermutation(dirPerm[dir]);
            const auto neighbor = combine(std::make_pair(newX, newY), nodeCube.perm);
            if(newX == 3 && newY == 5 && d[content] + nodeCube.retrieveBottom() == 3 && !once)  {
                once = true;
                std::cerr << nodePos.first << " " << nodePos.second << " " << dir << " " << nodeCube.retrieveBottom() << "\n";
                nodeCube.applyPermutation(dirPerm[oppositeDir[dir]]);
                std::cerr << "Perm: ";
                for(int i = 1;i <= 6;i++)
                    std::cerr << nodeCube.perm[i] << " ";
                std::cerr << "\n";

                nodeCube.printCube();
                nodeCube.applyPermutation(dirPerm[dir]);
                std::cerr << "Perm: ";
                for(int i = 1;i <= 6;i++)
                    std::cerr << nodeCube.perm[i] << " ";
                std::cerr << "\n";
                nodeCube.printCube();
            }

            if(!viz[neighbor] || d[neighbor] > d[content] + nodeCube.retrieveBottom())  {
                viz[neighbor] = true;
                d[neighbor] = d[content] + nodeCube.retrieveBottom();
                prev[neighbor] = content;
                Q.push(neighbor);
            }
            nodeCube.applyPermutation(dirPerm[oppositeDir[dir]]);
        }
    }

    int ans = 1e9;

    std::vector <int> helper;

    for(const auto& content : d)  {
        if(content.first[0] == end.line && content.first[1] == end.column)  {
            if(ans > content.second)  {
                helper = content.first;
                ans = content.second;
            }
        }
    }

    std::string sol;

    while(helper != startQueue)  {
        sol.push_back(helper[0] + '0');
        sol.push_back(helper[1] + 'a' - 1);
        sol.push_back(' ');
        helper = prev[helper];
    }

    std::reverse(sol.begin(), sol.end());

    std::cout << ans << " " << posStartString << sol << "\n";

// END CODE HERE

    #if USE_MODE
    endTimeCHRONO();
    #endif
    return 0;
}
