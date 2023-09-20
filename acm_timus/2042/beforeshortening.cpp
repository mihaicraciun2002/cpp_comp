#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

#define EASY_IO 1

std::string s;
int n, k, queryNo;
int queryCounter;
// This helps with retrieving elements faster
std::vector <int> fillMemoization;

class Node {
    public:
    int l;
    int r;
    int node;
    bool filled = false;
    char fillCh;
    bool calculated = false;
    long long ans = 0;
    // Constructor

    Node() {
    }
    Node(int l, int r, int node, bool filled, char fillCh)  {
        this -> l = l;
        this -> r = r;
        this -> node = node;
        this -> filled = filled;
        this -> fillCh = fillCh;
    }
    // For debugging
    void print() const {
        std::cerr << l << " " << r << " node: " << node << " filled: " << filled << " fillChar: " << fillCh << "\n";
    }
    int size() const  {
        return r - l + 1;
    }
};

std::vector <Node> arbint;

char getCh(const int& node, const int& treeLeft, const int& treeRight, const int& pos)  {
    if(arbint[node].filled)  {
        return arbint[node].fillCh;
    }
    if(treeLeft == treeRight)  {
        return s[pos];
    }
    const int treeMiddle = (treeLeft + treeRight) / 2;
    if(pos <= treeMiddle)  {
        return getCh(node * 2, treeLeft, treeMiddle, pos);
    }else{
        return getCh(node * 2 + 1, treeMiddle + 1, treeRight, pos);
    }
}

// Method to find what character is currently at this position
// O(log(n)) complexity, with memoization the constant is better
inline char getCh(const int& pos)  {
    if(fillMemoization[pos] == queryCounter)  {
        return s[pos];
    }
    s[pos] = getCh(1, 1, n, pos);
    fillMemoization[pos] = queryCounter;
    return getCh(1, 1, n, pos);
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

void fillString(const int&node, const int& treeLeft, const int& treeRight, const int& l, const int& r, char fillCh)  {
    if(treeRight < l || treeLeft > r)  {
        return;
    }
    if(l <= treeLeft && treeRight <= r)  {
        arbint[node].filled = true;
        arbint[node].fillCh = fillCh;
        arbint[node].calculated = false;
        arbint[node].ans = 0;
        return;
    }
    const int treeMiddle = (treeLeft + treeRight) / 2;
    arbint[node].filled = false;
    arbint[node].calculated = false;
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
    if(treeRight < l || treeLeft > r)  {
        return 0;
    }
    if(treeLeft == treeRight)  {
        return 1;
    }
    const int treeMiddle = (treeLeft + treeRight) / 2;
    if(l <= treeLeft && treeRight <= r)  {
        if(arbint[node].filled)  {
            return segmentCount(treeRight - treeLeft + 1, k);
        }
        if(arbint[node].calculated)  {
            return arbint[node].ans;
        }

        // We have to calculate the answer for the current node

        arbint[node].calculated = true;
        arbint[node].ans = 0;
        arbint[node].ans += query(node * 2, treeLeft, treeMiddle, l, r);
        arbint[node].ans += query(node * 2 + 1, treeMiddle + 1, treeRight, l, r);

        // For the intersection of the two segments:

        int sons[] = {node * 2, node * 2 + 1};

        int leftmost = treeLeft;
        int rightmost = treeRight;
        int mid1 = treeMiddle;
        int mid2 = treeMiddle + 1;
        int length1 = mid1 - leftmost + 1;
        int length2 = rightmost - mid2 + 1;

        // If they're both filled O(k)
        if(arbint[sons[0]].filled && arbint[sons[1]].filled)  {
            if(arbint[sons[0]].fillCh == arbint[sons[1]].fillCh)  {
                for(int partial1 = 1;partial1 <= std::min(k - 1, length1);partial1++)  {
                    // partial1 is the size of a block on the left side
                    // partial1 (mid1 mid2) partial2
                    int sumStop = std::min(length2, k - partial1);
                    arbint[node].ans += 1LL * sumStop;
                }
            }
        }else{
        // If some are unfilled, we need to calculate manually and inefficiently
            std::unordered_map <int, std::pair <int, int>> comp[2];
            int compSize[2] = {0, 0};
            if(k >= 2)  {
                if(getCh(mid1) == getCh(mid2))  {
                    comp[0][compSize[0]++] = std::make_pair(mid1, mid2);
                    arbint[node].ans++;
                }
            }
            if(k >= 3)  {
                if(mid2 + 1 <= rightmost && getCh(mid1) == getCh(mid2 + 1))  {
                    comp[1][compSize[1]++] = std::make_pair(mid1, mid2 + 1);
                    arbint[node].ans++;
                }
                if(mid1 - 1 >= leftmost && getCh(mid1 - 1) == getCh(mid2))  {
                    comp[1][compSize[1]++] = std::make_pair(mid1 - 1, mid2);
                    arbint[node].ans++;
                }
            }
            for(int kaux = 4;kaux <= k;kaux += 2)  {
                std::vector <int> toErase;
                for(auto& candidateMap: comp[0])  {
                    std::pair <int, int> candidate = candidateMap.second;
                    int candidateL = candidate.first - 1;
                    int candidateR = candidate.second + 1;
                    if(candidateL < leftmost || candidateR > rightmost || getCh(candidateL) != getCh(candidateL))  {
                        toErase.push_back(candidateMap.first);
                    }else{
                        candidateMap.second = std::make_pair(candidateL, candidateR);
                        arbint[node].ans++;
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
                        arbint[node].ans++;
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
                        arbint[node].ans++;
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
                    if(candidateL < leftmost || candidateR > rightmost || getCh(candidateL) != getCh(candidateL))  {
                        toErase.push_back(candidateMap.first);
                    }else{
                        candidateMap.second = std::make_pair(candidateL, candidateR);
                        arbint[node].ans++;
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
                        arbint[node].ans++;
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
                        arbint[node].ans++;
                    }
                }
                for(const auto&x : toErase)
                    comp[1].erase(x);
            }
        }

        return arbint[node].ans;
    }

    int mid1 = treeMiddle;
    int mid2 = treeMiddle + 1;
    int leftmost = std::max(l, treeLeft);
    int rightmost = std::min(r, treeRight);

    if(arbint[node].filled)  {
        int sz = std::min(r, treeRight) - std::max(l, treeLeft) + 1;
        return segmentCount(sz, k);
    }
    if(arbint[node].calculated && treeLeft >= l && treeRight <= r)  {
        return arbint[node].ans;
    }
    long long pieceWise = query(node * 2, treeLeft, treeMiddle, l, r) + query(node * 2 + 1, treeMiddle + 1, treeRight, l, r);
    if(treeMiddle < l)  {
        return pieceWise;
    }
    if(treeMiddle <= r)  {
        return pieceWise;
    }

    // We only combine the two subtrees if they have length at least 1 wrt (l, r)

    // We have to calculate the answer for the current node

    // For the intersection of the two segments:

    int sons[] = {node * 2, node * 2 + 1};

    int length1 = mid1 - leftmost + 1;
    int length2 = rightmost - mid2 + 1;

    // If they're both filled O(k)
    if(arbint[sons[0]].filled && arbint[sons[1]].filled)  {
        if(arbint[sons[0]].fillCh == arbint[sons[1]].fillCh)  {
            for(int partial1 = 1;partial1 <= std::min(k - 1, length1);partial1++)  {
                // partial1 is the size of a block on the left side
                // partial1 (mid1 mid2) partial2
                int sumStop = std::min(length2, k - partial1);
                pieceWise += 1LL * sumStop;
            }
        }
    }else{
    // If some are unfilled, we need to calculate manually and inefficiently
        std::unordered_map <int, std::pair <int, int>> comp[2];
        int compSize[2] = {0, 0};
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
                if(candidateL < leftmost || candidateR > rightmost || getCh(candidateL) != getCh(candidateL))  {
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
                if(candidateL < leftmost || candidateR > rightmost || getCh(candidateL) != getCh(candidateL))  {
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
    }
    return pieceWise;
}

int main()  {
    #if EASY_IO
    freopen("aux.in", "r", stdin);
    freopen("aux.out", "w", stdout);
    #endif
    std::cin >> s >> k >> queryNo;
    s.insert(0, 1, 0);
    n = s.size() - 1;
    fillMemoization = std::vector <int> (n, 0);
    arbint.resize(n * 4 + 1);
    for(auto &node : arbint)  {
        node = Node();
    }
    buildTree(1, 1, n);
    while(queryNo--)  {
        int queryType, l, r;
        std::cin >> queryType >> l >> r;
        if(queryType == 1)  {
            char fillCh;
            queryCounter++;
            std::cin >> fillCh;
            fillString(1, 1, n, l, r, fillCh);
        }else{
            std::cout << query(1, 1, n, l, r) << "\n";
        }
    }
    return 0;
}