#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <unordered_map>

std::string s;
int k, n;
int queryNo;
// Number of blocks
int blockSize;

class block  {
    public:
    int l;
    int r;
    int index;
    bool filled = false;
    char fillCh;
    bool calculated = false;
    long long ans = 0;
    // Constructor
    block(int l, int r, int index, bool filled, char fillCh)  {
        this -> l = l;
        this -> r = r;
        this -> index = index;
        this -> filled = filled;
        this -> fillCh = fillCh;
    }
    // For debugging
    void print() const {
        std::cerr << l << " " << r << " index: " << index << " filled: " << filled << " fillChar: " << fillCh << "\n";
    }
    int size() const  {
        return r - l + 1;
    }
    char getCh(int pos) const  {
        if(pos < l || pos > r)
            return 0;
        if(filled)  {
            return fillCh;
        }
        return s[pos];
    }
};

std::vector <block> blocks;
int blockIndex = 0;


// Finds which block contains position toFind
inline int getBlock(const int& toFind)  {
    int pas = 1 << 20;
    int index;
    index = -1;
    while(pas)  {
        if(index + pas < blockIndex && blocks[index + pas].r < toFind)
            index += pas;
        pas >>= 1;
    }
    index++;
    return index;
}

// Same as previous function, but overwrites the index parameter
inline void getBlock(int &index, const int& toFind)  {
    int pas = 1 << 20;
    index = -1;
    while(pas)  {
        if(index + pas < blockIndex && blocks[index + pas].r < toFind)
            index += pas;
        pas >>= 1;
    }
    index++;
}

// Function to fill blocks in a given range O(sqrt(n)) worst case
inline void fillBlocks(int l, int r, char fillCh)  {
    int indexLeft, indexRight;
    // First, find which will be the edge indexes
    getBlock(indexLeft, l);
    getBlock(indexRight, r);
    // Fill the middle blocks
    for(int index = indexLeft + 1;index < indexRight;index++)  {
        blocks[index].filled = true;
        blocks[index].fillCh = fillCh;
        blocks[index].calculated = false;
        blocks[index].ans = 0;
    }
    // If our leftmost block is completely filled
    if(blocks[indexLeft].l == l && blocks[indexLeft].r <= r)  {
        blocks[indexLeft].filled = true;
        blocks[indexLeft].fillCh = fillCh;
        blocks[indexLeft].calculated = false;
        blocks[indexLeft].ans = 0;
    }else{
        // Otherwise we have to paint it manually
        // Any computations about this block are now unusable
        blocks[indexLeft].calculated = false;
        blocks[indexLeft].ans = 0;
        // If the block was already painted, we first have to
        // manually apply the previous paint
        if(blocks[indexLeft].filled == true)  {
            blocks[indexLeft].filled = false;
            for(int i = blocks[indexLeft].l;i <= blocks[indexLeft].r;i++)
                s[i] = blocks[indexLeft].fillCh;
        }
        // then apply the new paint
        for(int i = l;i <= std::min(blocks[indexLeft].r, r);i++)
            s[i] = fillCh;
    }
    if(indexLeft == indexRight)  {
        return;
    }

    // Similarly for the rightmost block
    if(blocks[indexRight].r == r && blocks[indexRight].l >= l)  {
        blocks[indexRight].filled = true;
        blocks[indexRight].fillCh = fillCh;
        blocks[indexRight].calculated = false;
        blocks[indexRight].ans = 0;
    }else{
        blocks[indexRight].calculated = false;
        blocks[indexRight].ans = 0;
        if(blocks[indexRight].filled == true)  {
            blocks[indexRight].filled = false;

            for(int i = blocks[indexRight].l;i <= blocks[indexRight].r;i++)
                s[i] = blocks[indexRight].fillCh;
        }
        for(int i = std::max(l, blocks[indexRight].l);i <= r;i++)
            s[i] = fillCh;
    }
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



std::unordered_map <int, std::pair <int, int>> comp[2]; // here we store the current palindromes by parity
int compSize[2];

// The function that returns an answer for a query between l and r
inline long long solve(const int& l, const int& r)  {
    long long ans = 0;
    int indexLeft = getBlock(l);
    int indexRight = getBlock(r);
    // Median blocks O(1) best case, O(sqrt(n) * k) to compute a block
    for(int index = indexLeft + 1;index < indexRight;index++)  {
        if(blocks[index].filled)  {
            int sz = blocks[index].size();
            ans += segmentCount(sz, k);
        }else if(blocks[index].calculated)  {
            ans += blocks[index].ans;
        }else  {
            blocks[index].calculated = true;
            blocks[index].ans = 0;
            int blockL, blockR;
            blockL = blocks[index].l;
            blockR = blocks[index].r;
            comp[1].clear();
            comp[0].clear();
            compSize[0] = 0;
            compSize[1] = 0;
            if(k >= 1)
                for(int i = blockL;i <= blockR;i++)  {
                    comp[1][compSize[1]++] = std::make_pair(i, i);
                    blocks[index].ans++;
                }
            if(k >= 2)
                for(int i = blockL;i < blockR;i++)  {
                    if(s[i] == s[i + 1])
                        comp[0][compSize[0]++] = std::make_pair(i, i + 1),
                        blocks[index].ans++;
                }
            for(int kaux = 3;kaux <= k && comp[1].size();kaux += 2)  {
                std::vector <int> toErase;
                for(auto& candidateMap : comp[1])  {
                    std::pair <int, int> candidate = candidateMap.second;
                    if(candidate.first - 1 < blockL or candidate.second + 1 > blockR)  {
                        toErase.push_back(candidateMap.first);
                    }else if(s[candidate.first - 1] != s[candidate.second + 1])  {
                        toErase.push_back(candidateMap.first);
                    }else{
                        candidateMap.second = std::make_pair(candidate.first - 1, candidate.second + 1);
                        blocks[index].ans++;
                    }
                }
                for(const auto&x : toErase)
                    comp[1].erase(x);
            }
            for(int kaux = 4;kaux <= k && comp[0].size();kaux += 2)  {
                std::vector <int> toErase;
                for(auto& candidateMap : comp[0])  {
                    std::pair <int, int> candidate = candidateMap.second;
                    if(candidate.first - 1 < blockL or candidate.second + 1 > blockR)  {
                        toErase.push_back(candidateMap.first);
                    }else if(s[candidate.first - 1] != s[candidate.second + 1])  {
                        toErase.push_back(candidateMap.first);
                    }else{
                        candidateMap.second = std::make_pair(candidate.first - 1, candidate.second + 1);
                        blocks[index].ans++;
                    }
                }
                for(const auto&x : toErase)
                    comp[0].erase(x);
            }
            ans += blocks[index].ans;
        }
    }

    // Edge blocks O(k*sqrt(n))
    int areEdgesSame = (indexRight == indexLeft);
    for(int indexEdge = indexLeft;indexEdge <= indexRight;indexEdge += indexRight - indexLeft + areEdgesSame)  {
        int L, R;
        L = std::max(l, blocks[indexEdge].l);
        R = std::min(r, blocks[indexEdge].r);
        bool addCalculated = (L == blocks[indexEdge].l && R == blocks[indexEdge].r);
        int ansEdge = 0;
        if(blocks[indexEdge].filled)  {
            ansEdge = segmentCount(R - L + 1, k);
            addCalculated = false;
        }else if(addCalculated && blocks[indexEdge].calculated)  {
            ansEdge = blocks[indexEdge].ans;
        }else{
            // To add: similar to the for loop upstairs, calculate the partial palindromes
            int blockL, blockR;
            blockL = L;
            blockR = R;
            comp[1].clear();
            comp[0].clear();
            compSize[1] = 0;
            compSize[0] = 0;
            if(k >= 1)
                for(int i = blockL;i <= blockR;i++)  {
                    comp[1][compSize[1]++] = std::make_pair(i, i);
                    ansEdge++;
                }
            if(k >= 2)
                for(int i = blockL;i < blockR;i++)  {
                    if(s[i] == s[i + 1])
                        comp[0][compSize[0]++] = std::make_pair(i, i + 1),
                        ansEdge++;
                }
            for(int kaux = 3;kaux <= k && comp[1].size();kaux += 2)  {
                std::vector <int> toErase;
                for(auto& candidateMap : comp[1])  {
                    std::pair <int, int> candidate = candidateMap.second;
                    if(candidate.first - 1 < blockL or candidate.second + 1 > blockR)  {
                        toErase.push_back(candidateMap.first);
                    }else if(s[candidate.first - 1] != s[candidate.second + 1])  {
                        toErase.push_back(candidateMap.first);
                    }else{
                        candidateMap.second = std::make_pair(candidate.first - 1, candidate.second + 1);
                        ansEdge++;
                    }
                }
                for(const auto&x : toErase)
                    comp[1].erase(x);
            }
            for(int kaux = 4;kaux <= k && comp[0].size();kaux += 2)  {
                std::vector <int> toErase;
                for(auto& candidateMap : comp[0])  {
                    std::pair <int, int> candidate = candidateMap.second;
                    if(candidate.first - 1 < blockL or candidate.second + 1 > blockR)  {
                        toErase.push_back(candidateMap.first);
                    }else if(s[candidate.first - 1] != s[candidate.second + 1])  {
                        toErase.push_back(candidateMap.first);
                    }else{
                        candidateMap.second = std::make_pair(candidate.first - 1, candidate.second + 1);
                        ansEdge++;
                    }
                }
                for(const auto&x : toErase)
                    comp[0].erase(x);
            }
        }
        ans += ansEdge;
        if(addCalculated)  {
            blocks[indexEdge].calculated = true;
            blocks[indexEdge].ans = ansEdge;
        }
        // To add: Right edge - added with the for loop that treats the two edges
    }
    // To add: inter-block calculation - completely independent of them being already calculated or not
    for(int index = indexLeft;index < indexRight;index++)  {
        int lIndex = index;
        int rIndex = index + 1;
        int leftmost = std::max(blocks[lIndex].l, l);
        int rightmost = std::min(blocks[rIndex].r, r);
        int mid1 = blocks[lIndex].r;
        int mid2 = blocks[rIndex].l;
        int length1 = mid1 - leftmost + 1;
        int length2 = rightmost - mid2 + 1;
        // leftmost..mid1 mid2..rightmost
        // The palindromes counted here need to have left index in leftmost..mid1 and
        // rightmost index in mid2..rightmost
        // Several cases to treat:
        // If they're both filled O(k)
        long long tempAns = 0;
        if(blocks[lIndex].filled && blocks[rIndex].filled)  {
            if(blocks[lIndex].fillCh == blocks[rIndex].fillCh)  {
                for(int partial1 = 1;partial1 <= std::min(k - 1, length1);partial1++)  {
                    // partial1 is the size of a block on the left side
                    // partial1 (mid1 mid2) partial2
                    int sumStop = std::min(length2, k - partial1);
                    tempAns += 1LL * sumStop;
                }
            }
        // Even if one of them is filled, we still have to do the inefficient
        // palindrome checking O(k^2*sqrt(n))
        }else  {
            comp[0].clear();
            comp[1].clear();
            compSize[0] = 0;
            compSize[1] = 0;
            if(k >= 2 && blocks[lIndex].getCh(mid1) == blocks[rIndex].getCh(mid2))  {
                tempAns++;
                comp[0][compSize[0]++] = std::make_pair(mid1, mid2);
            }
            if(k >= 3 && mid2 + 1 <= rightmost && blocks[lIndex].getCh(mid1) ==
                blocks[rIndex].getCh(mid2 + 1))  {
                    comp[1][compSize[1]++] = std::make_pair(mid1, mid2 + 1);
                    tempAns++;
                }
            if(k >= 3 && mid1 - 1 >= leftmost && blocks[lIndex].getCh(mid1 - 1) ==
                blocks[rIndex].getCh(mid2))  {
                    comp[1][compSize[1]++] = std::make_pair(mid1 - 1, mid2);
                    tempAns++;
                }
            for(int kaux = 4;kaux <= k;kaux += 2)  {
                std::vector <int> toErase;
                for(auto& candidateMap: comp[0])  {
                    std::pair <int, int> candidate = candidateMap.second;
                    int candidateL = candidate.first - 1;
                    int candidateR = candidate.second + 1;
                    if(candidateL < leftmost || candidateR > rightmost ||
                        blocks[lIndex].getCh(candidateL) != blocks[rIndex].getCh(candidateR))  {
                        toErase.push_back(candidateMap.first);
                    }else  {
                        candidateMap.second = std::make_pair(candidateL, candidateR);
                        tempAns++;
                    }
                }
                // Adding the two new edge cases with edges in mid1 and mid2
                int newL = mid2 - kaux + 1;
                int newR = mid1 + kaux - 1;
                int edgeL, edgeR;
                if(newL >= leftmost)  {
                    bool shouldAdd = (blocks[lIndex].getCh(newL) == blocks[rIndex].getCh(mid2));
                    edgeL = newL + 1;
                    edgeR = mid1;
                    while(shouldAdd && edgeL < edgeR)
                        shouldAdd = (blocks[lIndex].getCh(edgeL) == blocks[lIndex].getCh(edgeR)),
                        edgeL++, edgeR--;
                    if(shouldAdd)  {
                        comp[0][compSize[0]++] = std::make_pair(newL, mid2);
                        tempAns++;
                    }
                }
                if(newR <= rightmost)  {
                    bool shouldAdd = (blocks[lIndex].getCh(mid1) == blocks[rIndex].getCh(newR));
                    edgeL = mid2;
                    edgeR = newR - 1;
                    while(shouldAdd && edgeL < edgeR)
                        shouldAdd = (blocks[rIndex].getCh(edgeL) == blocks[rIndex].getCh(edgeR)),
                        edgeL++, edgeR--;
                    if(shouldAdd)  {
                        comp[0][compSize[0]++] = std::make_pair(mid1, newR);
                        tempAns++;
                    }
                }
                for(const auto&x : toErase)  {
                    comp[0].erase(x);
                }
            }
            for(int kaux = 5;kaux <= k;kaux += 2)  {
                std::vector <int> toErase;

                for(auto& candidateMap: comp[1])  {
                    std::pair <int, int> candidate = candidateMap.second;
                    int candidateL = candidate.first - 1;
                    int candidateR = candidate.second + 1;
                    if(candidateL < leftmost || candidateR > rightmost ||
                        blocks[lIndex].getCh(candidateL) != blocks[rIndex].getCh(candidateR))  {
                        toErase.push_back(candidateMap.first);
                    }else  {
                        candidateMap.second = std::make_pair(candidateL, candidateR);
                        tempAns++;
                    }
                }
                // Adding the two new edge cases with edges in mid1 and mid2
                int newL = mid2 - kaux + 1;
                int newR = mid1 + kaux - 1;
                int edgeL, edgeR;
                if(newL >= leftmost)  {
                    bool shouldAdd = (blocks[lIndex].getCh(newL) == blocks[rIndex].getCh(mid2));
                    edgeL = newL + 1;
                    edgeR = mid1;
                    while(shouldAdd && edgeL < edgeR)
                        shouldAdd = (blocks[lIndex].getCh(edgeL) == blocks[lIndex].getCh(edgeR)),
                        edgeL++, edgeR--;
                    if(shouldAdd)  {
                        comp[1][compSize[1]++] = std::make_pair(newL, mid2);
                        tempAns++;
                    }
                }
                if(newR <= rightmost)  {
                    bool shouldAdd = (blocks[lIndex].getCh(mid1) == blocks[rIndex].getCh(newR));
                    edgeL = mid2;
                    edgeR = newR - 1;
                    while(shouldAdd && edgeL < edgeR)
                        shouldAdd = (blocks[rIndex].getCh(edgeL) == blocks[rIndex].getCh(edgeR)),
                        edgeL++, edgeR--;
                    if(shouldAdd)  {
                        comp[1][compSize[1]++] = std::make_pair(mid1, newR);
                        tempAns++;
                    }
                }
                for(const auto&x : toErase)
                    comp[1].erase(x);
            }
        }
        ans += tempAns;
    }
    return ans;
}

inline void printString()  {
    for(const auto&block : blocks)  {
        if(block.filled)  {
            for(int i = block.l;i <= block.r;i++)  {
                std::cerr << block.fillCh;
            }
        }else{
            for(int i = block.l;i <= block.r;i++)  {
                std::cerr << s[i];
            }
        }
    }
    std::cerr << "\n";
    return;
}

inline void printString(const int& l, const int& r)  {
    int indexLeft = getBlock(l), indexRight = getBlock(r);
    for(int blockIndex = indexLeft;blockIndex <= indexRight;blockIndex++)  {
        int L = std::max(blocks[blockIndex].l, l);
        int R = std::min(blocks[blockIndex].r, r);
        for(int i = L;i <= R;i++)
            std::cerr << blocks[blockIndex].getCh(i);
    }
    std::cerr << "\n";
}

inline void printStringBlocks(const int&l, const int& r)  {
    int indexLeft = getBlock(l), indexRight = getBlock(r);
    for(int blockIndex = indexLeft;blockIndex <= indexRight;blockIndex++)  {
        int L = std::max(blocks[blockIndex].l, l);
        int R = std::min(blocks[blockIndex].r, r);
        blocks[blockIndex].print();
        std::cerr << "range: " << L << " " << R << "\n";
        for(int i = L;i <= R;i++)
            std::cerr << blocks[blockIndex].getCh(i);
        std::cerr << "\n";
    }
    std::cerr << "\n";
}

#define EASY_IO 0

int main()  {
    #if EASY_IO
    freopen("aux.in", "r", stdin);
    freopen("aux.out", "w", stdout);
    #endif
    std::cin >> s >> k >> queryNo;
    s.insert(0, 1, 0);
    n = s.size() - 1;
    k = std::min(n, k);
    blockSize = std::max(k, (int)sqrt(n));
    for(int i = 1;i <= n;i += blockSize)  {
        int l = i;
        int r = std::min(n, i + blockSize - 1);
        blocks.push_back(block(l, r, blockIndex, false, 0));
        blockIndex++;
    }
    while(queryNo--)  {
        int type, l, r;
        char fillCh;
        std::cin >> type >> l >> r;
        if(type == 1)  {
            std::cin >> fillCh;
            fillBlocks(l, r, fillCh);
        }else{
            std::cout << solve(l, r) << "\n";
        }
    }
    return 0;
}
