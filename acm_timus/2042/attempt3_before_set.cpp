#define CHRONO_IN 1
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <utility>
#include <algorithm>
#include <set>
#if CHRONO_IN
#include <chrono>
#endif


std::string s;
int n, k, queryNo;
int updateCounter;
int queryCounter;

inline void printString(const int& l, const int& r);

inline int size(const int&left, const int &right)  {
    assert(left <= right);
    return right - left + 1;
}

class SegmentTree  {
    private:
    std::vector <long long> arbint, lazy;
    int n;

    // Update a segment from l to r with value
    void update(const int& node, const int& treeLeft, const int& treeRight, const int& l, const int& r, const int& value)  {
        if(lazy[node])  {
            arbint[node] = lazy[node] * size(treeLeft, treeRight);
            if(treeRight != treeLeft)  {
                lazy[node * 2] = lazy[node];
                lazy[node * 2 + 1] = lazy[node];
            }
            lazy[node] = 0;
        }
        if(treeLeft > r || treeRight < l)  {
            return;
        }
        if(l <= treeLeft && treeRight <= r)  {
            arbint[node] = value * size(treeLeft, treeRight);
            if(treeRight != treeLeft)  {
                lazy[node * 2] = value;
                lazy[node * 2 + 1] = value;
            }
            return;
        }
        const int treeMiddle = (treeLeft + treeRight) / 2;
        update(node * 2, treeLeft, treeMiddle, l, r, value);
        update(node * 2 + 1, treeMiddle + 1, treeRight, l, r, value);
        arbint[node] = arbint[node * 2] + arbint[node * 2 + 1];
    }

    long long query(const int& node, const int& treeLeft, const int& treeRight, const int& l, const int& r)  {
        if(lazy[node] != 0)  {
            arbint[node] = lazy[node] * size(treeLeft, treeRight);
            if(treeLeft != treeRight)  {
                lazy[node * 2] = lazy[node];
                lazy[node * 2 + 1] = lazy[node];
            }
            lazy[node] = 0;
        }
        if(l > treeRight || r < treeLeft)  {
            return 0;
        }
        if(l <= treeLeft && treeRight <= r)  {
            return arbint[node];
        }
        const int treeMiddle = (treeLeft + treeRight) / 2;
        long long queryLeft = query(node * 2, treeLeft, treeMiddle, l, r);
        long long queryRight = query(node * 2 + 1, treeMiddle + 1, treeRight, l, r);

        return queryLeft + queryRight;
    }
    public:
    SegmentTree() {}
    SegmentTree(const int& size)  {
        arbint = std::vector <long long> (size * 4 + 1, 0);
        lazy = std::vector <long long> (size * 4 + 1, 0);
        n = size;
    }
    inline void update(const int& l, const int& r, const int& value)  {
        this -> update(1, 1, n, l, r, value);
    }
    inline long long query(const int& l, const int& r)  {
        return this -> query(1, 1, n, l, r);
    }
    inline long long get(const int& pos)  {
        return this -> query(1, 1, n, pos, pos);
    }
};

SegmentTree string;
SegmentTree dp;

inline void manualUpdate(const int& l, const int& r)  {
    std::set < std::pair <int, int> > comp;
    int currentAnswer = 0;
    long long lDp = 0;

    // for i = l, we have to initialize comp
    for(int leftEdge = l;leftEdge >= l - k + 1 && leftEdge >= 1;leftEdge--)  {
        // leftEdge -> l
        int edgeL = leftEdge;
        int edgeR = l;
        bool toAdd = true;
        while(edgeL < edgeR && toAdd)  {
            toAdd = (string.get(edgeL) == string.get(edgeR));
            edgeL++, edgeR--;
        }
        if(toAdd)  {
            lDp++;
            comp[compSize++] = std::make_pair(leftEdge, l);
        }
    }

    dp.update(l, l, lDp);
    currentAnswer = lDp;

    for(int i = l + 1;i <= r;i++)  {
        std::vector <int> toErase;
        for(auto& candidateMap : comp)  {
            std::pair <int, int> candidate = candidateMap.second;
            if(candidate.first - 1 < 1 || size(candidate.first - 1, candidate.second + 1) > k ||
                string.get(candidate.first - 1) != string.get(candidate.second + 1))  {
                toErase.push_back(candidateMap.first);
                currentAnswer--;
            }else{
                candidateMap.second = std::make_pair(candidate.first - 1, candidate.second + 1);
            }
        }
        for(const auto&x : toErase)  {
            comp.erase(x);
        }
        comp[compSize++] = std::make_pair(i, i);
        currentAnswer++;
        if(k >= 2 && i > 1 && string.get(i - 1) == string.get(i))  {
            comp[compSize++] = std::make_pair(i - 1, i);
            currentAnswer++;
        }
        dp.update(i, i, currentAnswer);
    }
}

// We have to manually update l -> l + k - 2, r + 1 -> r + k - 1

inline void updateDp(const int& l, const int& r)  {
    if(size(l, r) < k)  {
        manualUpdate(l, std::min(n, r + k - 1));
        return;
    }
    manualUpdate(l, l + k - 2);
    manualUpdate(r + 1, r + k - 1);
    dp.update(l + k - 1, r, k);
}

inline long long manualQuery(const int& l, const int& r)  {
    long long ans = 0;
    std::unordered_map <int, std::pair <int, int>> comp;
    int compSize = 0;
    for(int i = l;i <= r;i++)  {
        std::vector <int> toErase;
        for(auto& candidateMap: comp)  {
            std::pair <int, int> candidate = candidateMap.second;
            if(candidate.first - 1 < l || candidate.second + 1 > r || size(candidate.first - 1, candidate.second + 1) > k ||
                string.get(candidate.first - 1) != string.get(candidate.second + 1))  {
                    toErase.push_back(candidateMap.first);
                }else{
                    candidateMap.second = std::make_pair(candidate.first - 1, candidate.second + 1);
                    ans++;
                }
        }
        for(const auto& x : toErase)
            comp.erase(x);
        comp[compSize++] = std::make_pair(i, i);
        ans++;
        if(i > l && k >= 2 && string.get(i - 1) == string.get(i))  {
            comp[compSize++] = std::make_pair(i - 1, i);
            ans++;
        }
    }

    return ans;
}

inline long long queryDp(const int& l, const int& r)  {
    int manualQueryRightEdge = std::min(r, l + k - 2);
    long long ans = manualQuery(l, manualQueryRightEdge);
    if(manualQueryRightEdge == r)  {
        return ans;
    }
    ans += dp.query(manualQueryRightEdge + 1, r);
    return ans;
}

inline void printString()  {
    for(int i = 1;i <= n;i++)  {
        std::cerr << (char)string.get(i);
    }
    std::cerr << "\n";
}

inline void printString(FILE *out)  {
    for(int i = 1;i <= n;i++)  {
        fprintf(out, "%c", (char)string.get(i));
    }
    fprintf(out, "\n");
}

inline void printString(const int& l, const int& r)  {
    for(int i = l;i <= r;i++)  {
        std::cerr << (char)string.get(i);
    }
    std::cerr << "\n";
}


#define EASY_IO 1
#define STRING_CHECK 0

int main()  {
    #if CHRONO_IN
    auto started_time = std::chrono::high_resolution_clock::now();
    #endif

    #if EASY_IO
    freopen("aux.in", "r", stdin);
    freopen("aux.out", "w", stdout);
    #if STRING_CHECK
    FILE *stringCheck = fopen("strmain.out", "w");
    #endif
    #endif
    std::cin >> s >> k >> queryNo;
    s.insert(0, 1, 0);
    n = s.size() - 1;
    string = SegmentTree(n);
    dp = SegmentTree(n);

    for(int i = 1;i <= n;i++)  {
        string.update(i, i, s[i]);
    }

    // Dp initialization
    manualUpdate(1, n);
    std::cerr << n << "\n";
    while(queryNo--)  {
        #if EASY_IO && STRING_CHECK
        printString(stringCheck);
        #endif
        #if CHRONO_IN
        if((queryNo + 1) % (int)1e4 == 0)  {
            std::cerr << "Working... " << queryNo << "\n";
        }
        #endif
        int queryType, l, r;
        std::cin >> queryType >> l >> r;
        if(queryType == 1)  {
            char fillCh;
            std::cin >> fillCh;
            updateCounter++;
            string.update(l, r, fillCh);
            updateDp(l, r);
        }else{
            queryCounter++;
            // std::cout << queryDp(l, r) << '\n';
        }
    }
    #if CHRONO_IN
    auto finished_time = std::chrono::high_resolution_clock::now();
    std::cerr << "Time elapsed (s):\n";
    std::cerr << (double)std::chrono::duration_cast<std::chrono::milliseconds>(finished_time - started_time).count() / 1000.0 << "\n";
    #endif

    return 0;
}
