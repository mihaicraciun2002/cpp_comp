#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>


std::string s;
int n, k, queryNo;

// This helps with retrieving elements faster
int queryCounter;
std::vector <int> fillMemoization;

class Node {
    public:
    int l;
    int r;
    int node;
    int lastFill = 0;
    char fillCh;
    int lastCalculated = -1;
    long long ans = 0;
    // Constructor

    Node() {
    }
    Node(int l, int r, int node, bool filled, char fillCh)  {
        this -> l = l;
        this -> r = r;
        this -> node = node;
        this -> fillCh = fillCh;
    }
    // For debugging
    void print() const {
        std::cerr << l << " " << r << " node: " << node << " fillChar: " << fillCh << "\n";
    }
    int size() const  {
        return r - l + 1;
    }
};

std::vector <Node> arbint;
int mostRecentFill = 0;
char fillChar = 0;

// Don't call this method directly! mostRecentFill needs to be up to date
void getCh(const int& node, const int& treeLeft, const int& treeRight, const int& pos)  {
    if(arbint[node].lastFill > mostRecentFill)  {
        mostRecentFill = arbint[node].lastFill;
        fillChar = arbint[node].fillCh;
    }
    // We can't find a more recent character
    if(arbint[node].lastFill == queryCounter)  {
        return;
    }
    if(treeLeft == treeRight)  {
        return;
    }
    const int treeMiddle = (treeLeft + treeRight) / 2;
    if(pos <= treeMiddle)  {
        getCh(node * 2, treeLeft, treeMiddle, pos);
    }else{
        getCh(node * 2 + 1, treeMiddle + 1, treeRight, pos);
    }
}

// Method to find what character is currently at this position
// O(log(n)) complexity, with memoization it runs a bit faster
inline char getCh(const int& pos)  {
    if(fillMemoization[pos] == queryCounter)  {
        return s[pos];
    }
    mostRecentFill = 0;
    fillChar = s[pos];
    getCh(1, 1, n, pos);
    s[pos] = fillChar;
    fillMemoization[pos] = queryCounter;
    return s[pos];
}

inline void printString(int l, int r)  {
    for(int i = l;i <= r;i++)
        std::cerr << getCh(i);
    std::cerr << "\n";
}

inline void printString (int l, int r, FILE *out)  {
    for(int i = 1;i <= r;i++)
        fprintf(out, "%c", getCh(i));
    fprintf(out, "\n");
}

void buildTree(const int& node, const int& treeLeft, const int& treeRight)  {
    if(treeLeft == treeRight)  {
        arbint[node].l = treeLeft;
        arbint[node].r = treeRight;
        arbint[node].node = node;
        return;
    }
    arbint[node].l = treeLeft;
    arbint[node].r = treeRight;
    arbint[node].node = node;
    const int treeMiddle = (treeLeft + treeRight) / 2;
    buildTree(node * 2, treeLeft, treeMiddle);
    buildTree(node * 2 + 1, treeMiddle + 1, treeRight);
}

// If a segment is marked with filled, check upstream to see if any newer fills are available
void checkLastFill(const int& node, const int& treeLeft, const int& treeRight, const int& segmentNode)  {
        int segmentL = arbint[segmentNode].l;
        int segmentR = arbint[segmentNode].r;
        if(segmentL > arbint[node].r || segmentR < arbint[node].l)  {
            return;
        }
        if(node == segmentNode)  {
            return;
        }

        if(1)  {
            if(arbint[node].lastFill > arbint[segmentNode].lastFill)  {
                arbint[segmentNode].fillCh = arbint[node].fillCh;
                arbint[segmentNode].lastCalculated = -1;
                arbint[segmentNode].ans = 0;
                arbint[segmentNode].lastFill = arbint[node].lastFill;
            }
        }
        const int& treeMiddle = (treeLeft + treeRight) / 2;
        checkLastFill(node * 2, treeLeft, treeMiddle, segmentNode);
        checkLastFill(node * 2 + 1, treeMiddle + 1, treeRight, segmentNode);
}

void fillString(const int& node, const int& treeLeft, const int& treeRight, const int& l, const int& r, char fillCh)  {
    if(treeRight < l || treeLeft > r)  {
        return;
    }
    if(l <= treeLeft && treeRight <= r)  {
        arbint[node].fillCh = fillCh;
        arbint[node].lastCalculated = -1;
        arbint[node].lastFill = queryCounter;
        arbint[node].ans = 0;
        return;
    }
    const int treeMiddle = (treeLeft + treeRight) / 2;
    arbint[node].lastCalculated = -1;
    arbint[node].ans = 0;
    fillString(node * 2, treeLeft, treeMiddle, l, r, fillCh);
    fillString(node * 2 + 1, treeMiddle + 1, treeRight, l, r, fillCh);
}

//Segment count for a filled block of size sz and k = k
inline long long segmentCount(const int& sz, const int& k)  {
    long long ansSegment = 0;
    // If the size is smaller than k (if we pass a partial block)
    // we only do the sum from 1 to maxk
    int maxK = std::min(k, sz);
    // This is just the sum sz + (sz - 1) + .. + (sz - maxk + 1)
    ansSegment += 1LL * sz * maxK + maxK - (1 + maxK) * maxK / 2;
    return ansSegment;
}

long long query(const int& node, const int& treeLeft, const int& treeRight, const int& l, const int& r)  {
    if(treeRight < l || r < treeLeft)  { // Out of bounds
        return 0;
    }
    if(treeLeft == treeRight)  { // One element
        return 1;
    }
    const int treeMiddle = (treeLeft + treeRight) / 2;

    int mid1 = treeMiddle;
    int mid2 = treeMiddle + 1;
    int leftmost = std::max(l, treeLeft);
    int rightmost = std::min(r, treeRight);

    int length1 = mid1 - leftmost + 1;
    int length2 = rightmost - mid2 + 1;


/*     if(arbint[node].filled)  {
        int sz = rightmost - leftmost + 1;
        return segmentCount(sz, k);
    } */
    if(arbint[node].lastCalculated == queryCounter && treeLeft >= l && treeRight <= r)  {
        return arbint[node].ans;
    }

    bool addCalculated = (treeLeft >= l && treeRight <= r);

    long long queryLeft = query(node * 2, treeLeft, treeMiddle, l, r);
    long long queryRight = query(node * 2 + 1, treeMiddle + 1, treeRight, l, r);
    long long pieceWise = queryLeft + queryRight;

    // We only combine the two subtrees if they have length at least 1 wrt (l, r)

    if(treeMiddle + 1 <= l)  {
        if(addCalculated)
            arbint[node].ans = pieceWise, arbint[node].lastCalculated = queryCounter;
        return pieceWise;
    }
    if(treeMiddle >= r)  {
        if(addCalculated)
            arbint[node].ans = pieceWise, arbint[node].lastCalculated = queryCounter;
        return pieceWise;
    }


    // We have to calculate the answer for the current node

    // For the intersection of the two segments:

    int sons[] = {node * 2, node * 2 + 1};


    std::unordered_map <int, std::pair <int, int>> comp[2];
    int compSize[2];
    compSize[0] = 0;
    compSize[1] = 0;
    if(k >= 2)  {
        if(getCh(mid1) == getCh(mid2))  {
            comp[0][compSize[0]++] = std::make_pair(mid1, mid2);
            pieceWise++;
        }
    }
    if(k >= 3)  {
        if(mid2 + 1 <= rightmost && getCh(mid1) == getCh(mid2 + 1))  {
            comp[1][compSize[1]++] = std::make_pair(mid1, mid2 + 1);
            pieceWise++;
        }
        if(mid1 - 1 >= leftmost && getCh(mid1 - 1) == getCh(mid2))  {
            comp[1][compSize[1]++] = std::make_pair(mid1 - 1, mid2);
            pieceWise++;
        }
    }
    for(int kaux = 4;kaux <= k;kaux += 2)  {
        std::vector <int> toErase;
        for(auto& candidateMap: comp[0])  {
            std::pair <int, int> candidate = candidateMap.second;
            int candidateL = candidate.first - 1;
            int candidateR = candidate.second + 1;
            if(candidateL < leftmost || candidateR > rightmost || getCh(candidateL) != getCh(candidateR))  {
                toErase.push_back(candidateMap.first);
            }else{
                candidateMap.second = std::make_pair(candidateL, candidateR);
                pieceWise++;
            }
        }
        int newL, newR;
        newL = mid2 - kaux + 1;
        newR = mid1 + kaux - 1;
        int edgeL, edgeR;
        if(newL >= leftmost)  {
            bool shouldAdd = (getCh(newL) == getCh(mid2));
            edgeL = newL + 1;
            edgeR = mid1;
            while(shouldAdd && edgeL < edgeR)
                shouldAdd = (getCh(edgeL) == getCh(edgeR)),
                edgeL++, edgeR--;
            if(shouldAdd)  {
                comp[0][compSize[0]++] = std::make_pair(newL, mid2);
                pieceWise++;
            }
        }
        if(newR <= rightmost)  {
            bool shouldAdd = (getCh(mid1) == getCh(newR));
            edgeL = mid2;
            edgeR = newR - 1;
            while(shouldAdd && edgeL < edgeR)
                shouldAdd = (getCh(edgeL) == getCh(edgeR)),
                edgeL++, edgeR--;
            if(shouldAdd)  {
                comp[0][compSize[0]++] = std::make_pair(mid1, newR);
                pieceWise++;
            }
        }
        for(const auto&x : toErase)
            comp[0].erase(x);
    }

    for(int kaux = 5;kaux <= k;kaux += 2)  {
        std::vector <int> toErase;
        for(auto& candidateMap: comp[1])  {
            std::pair <int, int> candidate = candidateMap.second;
            int candidateL = candidate.first - 1;
            int candidateR = candidate.second + 1;
            if(candidateL < leftmost || candidateR > rightmost || getCh(candidateL) != getCh(candidateR))  {
                toErase.push_back(candidateMap.first);
            }else{
                candidateMap.second = std::make_pair(candidateL, candidateR);
                pieceWise++;
            }
        }
        int newL, newR;
        newL = mid2 - kaux + 1;
        newR = mid1 + kaux - 1;
        int edgeL, edgeR;
        if(newL >= leftmost)  {
            bool shouldAdd = (getCh(newL) == getCh(mid2));
            edgeL = newL + 1;
            edgeR = mid1;
            while(shouldAdd && edgeL < edgeR)
                shouldAdd = (getCh(edgeL) == getCh(edgeR)),
                edgeL++, edgeR--;
            if(shouldAdd)  {
                comp[1][compSize[1]++] = std::make_pair(newL, mid2);
                pieceWise++;
            }
        }
        if(newR <= rightmost)  {
            bool shouldAdd = (getCh(mid1) == getCh(newR));
            edgeL = mid2;
            edgeR = newR - 1;
            while(shouldAdd && edgeL < edgeR)
                shouldAdd = (getCh(edgeL) == getCh(edgeR)),
                edgeL++, edgeR--;
            if(shouldAdd)  {
                comp[1][compSize[1]++] = std::make_pair(mid1, newR);
                pieceWise++;
            }
        }
        for(const auto&x : toErase)
            comp[1].erase(x);
    }
    if(addCalculated)  {
        arbint[node].lastCalculated = queryCounter;
        arbint[node].ans = pieceWise;
    }
    return pieceWise;
}

#define EASY_IO 0
#define STRING_CHECK 0

int main()  {
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
    fillMemoization = std::vector <int> (n + 1, 0);
    arbint.resize(n * 4 + 1);
    for(auto &node : arbint)  {
        node = Node();
    }
    buildTree(1, 1, n);
    int queryType2Counter = 0;
    while(queryNo--)  {
        #if EASY_IO && STRING_CHECK
        printString(1, n, stringCheck);
        #endif
        int queryType, l, r;
        std::cin >> queryType >> l >> r;
        if(queryType == 1)  {
            char fillCh;
            queryCounter++;
            std::cin >> fillCh;
            fillString(1, 1, n, l, r, fillCh);
        }else{
            queryType2Counter++;
            std::cout << query(1, 1, n, l, r) << '\n';
        }
    }
    return 0;
}
