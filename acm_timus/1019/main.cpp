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
#include <utility>
#include <set>
#include <unordered_map>
#include <cassert>

// START CODE HERE


int queryNo;
std::vector <std::tuple <int, int, char>> queries;
std::set <int> uniqueQueries, originalQueries;
std::unordered_map <int, int> queryIndexes;
std::unordered_map <int, int> indexCorrespondents;
const int maxN = 1e9;


class SegmentTree  {
    private:
    std::vector <int> arbint;
    std::vector <int> lazy;
    int _size = 0;

    void update(const int& node, const int& treeLeft, const int& treeRight, const int& l, const int& r, const int& value)  {
        const int nodeLeft = node * 2;
        const int nodeRight = node * 2 + 1;
        const int treeMiddle = (treeLeft + treeRight) / 2;
        if(lazy[node])  {
            arbint[node] = lazy[node];
            if(treeLeft < treeRight)  {
                lazy[nodeLeft] = lazy[node];
                lazy[nodeRight] = lazy[node];
            }
            lazy[node] = 0;
        }
        if(treeRight < l || r < treeLeft)  {
            return;
        }
        if(l <= treeLeft && treeRight <= r)  {
            arbint[node] = value;
            if(treeLeft < treeRight)  {
                lazy[nodeLeft] = value;
                lazy[nodeRight] = value;
            }
            return;
        }
        update(nodeLeft, treeLeft, treeMiddle, l, r, value);
        update(nodeRight, treeMiddle + 1, treeRight, l, r, value);
        arbint[node] = arbint[node * 2] | arbint[node * 2 + 1];
    }
    int query(const int& node, const int& treeLeft, const int& treeRight, const int& l, const int& r)  {
        const int nodeLeft = node * 2;
        const int nodeRight = node * 2 + 1;
        const int treeMiddle = (treeLeft + treeRight) / 2;
        if(lazy[node])  {
            arbint[node] = lazy[node];
            if(treeLeft < treeRight)  {
                lazy[nodeLeft] = lazy[node];
                lazy[nodeRight] = lazy[node];
            }
            lazy[node] = 0;
        }
        if(treeRight < l || r < treeLeft)  {
            return 0;
        }
        if(l <= treeLeft && treeRight <= r)  {
            return arbint[node];
        }
        int queryLeft = query(nodeLeft, treeLeft, treeMiddle, l, r);
        int queryRight = query(nodeRight, treeMiddle + 1, treeRight, l, r);

        return (queryLeft | queryRight);
    }

    public:
    SegmentTree(){}
    SegmentTree(const int& sz)  {
        _size = sz;
        arbint = std::vector <int> (_size * 4 + 1, 0);
        lazy = std::vector <int> (_size * 4 + 1, 0);
    }

    inline void update(const int& l, const int& r, const int& value)  {
        update(1, 1, _size, l, r, value);
    }
    inline int query(const int& l, const int& r)  {
        return query(1, 1, _size, l, r);
    }
};



// END CODE HERE

int main()  {
    #if USE_MODE
    started_time = std::chrono::high_resolution_clock::now(); freopen("aux.in", "r", stdin);  freopen("aux.out", "w", stdout);
    #endif

// START CODE HERE

    std::cin >> queryNo;
    for(int i = 1;i <= queryNo;i++)  {
        int l, r;
        char ch;
        std::cin >> l >> r >> ch;
        r--;
        queries.push_back(std::make_tuple(l, r, ch));
        uniqueQueries.insert(l);
        uniqueQueries.insert(l - 1);
        uniqueQueries.insert(r);
        uniqueQueries.insert(r + 1);
        originalQueries.insert(l);
        originalQueries.insert(r + 1);
    }
    originalQueries.insert(0);
    originalQueries.insert(maxN);

    int indexHelper = 0;
    uniqueQueries.insert(0);
    uniqueQueries.insert(maxN - 1);
    for(const auto& query: uniqueQueries)  {
        queryIndexes[query] = ++indexHelper;
        indexCorrespondents[indexHelper] = query;
    }

    SegmentTree sg = SegmentTree(indexHelper);
    sg.update(1, indexHelper, 'w');

    for(int i = 1;i <= queryNo;i++)  {
        int l, r;
        char ch;
        l = std::get  <0> (queries[i  - 1]);
        r = std::get  <1> (queries[i  - 1]);
        ch = std::get <2> (queries[i  - 1]);
        int queryIndexL = queryIndexes[l];
        int queryIndexR = queryIndexes[r];
        sg.update(queryIndexL, queryIndexR, (int)ch);
    }

    int bestContiguous = 0;
    int bestL, bestR;
    bool foundBest = false;

    int currentBest = 0;
    int currentL, currentR;
    bool isCurrent = false;


    std::vector <int> originalQ;

    for(const auto&x : originalQueries)
        originalQ.push_back(x);


    for(int i = 0;i + 1 < originalQ.size();i++)  {
        int iL = queryIndexes[originalQ[i]], iR = queryIndexes[originalQ[i + 1] - 1];
        int L = originalQ[i], R = originalQ[i + 1];
        char segment = sg.query(iL, iR);
        if(segment == 'b')  {
            currentBest = 0;
            isCurrent = false;
        }else{
            if(isCurrent)  {
                currentBest += R - L;
                currentR = R;
            }else{
                isCurrent = true;
                currentBest = R - L;
                currentL = L;
                currentR = R;
            }
        }
        if(isCurrent)  {
            if(!foundBest || (currentBest > bestContiguous))  {
                foundBest = true;
                bestContiguous = currentBest;
                bestL = currentL;
                bestR = currentR;
            }
        }
    }

    std::cout << bestL << " " << bestR << "\n";

// END CODE HERE

    #if USE_MODE
    endTimeCHRONO();
    #endif
    return 0;
}
