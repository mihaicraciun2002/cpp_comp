#define CHRONO_IN 0

#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <utility>
#include <cmath>

#if CHRONO_IN
#include <chrono>
#endif
long long prepMan, saves;

inline void printString();
inline void printString(const int& l, const int& r);

inline int size(const int& l, const int& r)  {
	return r - l + 1;
}

inline int threeMax(const int& a, const int& b, const int& c)  {
	return std::max(a, std::max(b, c));
}

inline int threeMin(const int& a, const int& b, const int& c)  {
	return std::min(a, std::min(b, c));
}

int updateCounter = 0, queryCounter = 0;
bool qType;

int lastSeen[(int)1e5 + 1];
std::vector <int> updates;
std::string sInit;

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
        return sInit[pos];
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

int blockCorespondent[(int)1e5 + 1];

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
                sInit[i] = blocks[indexLeft].fillCh;
        }
        // then apply the new paint
        for(int i = l;i <= std::min(blocks[indexLeft].r, r);i++)
            sInit[i] = fillCh;
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
                sInit[i] = blocks[indexRight].fillCh;
        }
        for(int i = std::max(l, blocks[indexRight].l);i <= r;i++)
            sInit[i] = fillCh;
    }
}



template <typename T>
class SegmentTree  {
	private:
	std::vector <T> arbint, lazy;
	int size;
	bool isDp = false;

	void update(const int& node, const int& treeLeft, const int& treeRight, const int& l, const int& r, const T& value)  {
		int nodeLeft = (node << 1);
		int nodeRight = nodeLeft + 1;
		if(lazy[node])  {

			arbint[node] = lazy[node] * ::size(treeLeft, treeRight);
			if(!isDp)
				arbint[node] = lazy[node];
			if(treeLeft != treeRight)  {
				lazy[nodeLeft] = lazy[node];
				lazy[nodeRight] = lazy[node];
			}else{
				if(!isDp)  {
					sInit[treeLeft] = updates[arbint[node]];
					lastSeen[treeLeft] = updateCounter;
				}
			}
			lazy[node] = 0;
		}
		if(r < treeLeft || treeRight < l)
			return;
		if(l <= treeLeft && treeRight <= r)  {
			arbint[node] = value * ::size(treeLeft, treeRight);
			if(!isDp)
				arbint[node] = value;

			if(treeLeft != treeRight)  {
				lazy[nodeLeft] = value;
				lazy[nodeRight] = value;
			}else{
				if(!isDp)  {
					sInit[treeLeft] = updates[arbint[node]];
					lastSeen[treeLeft] = updateCounter;
				}
			}
			return;
		}
		const int treeMiddle = (treeRight + treeLeft) >> 1;
		update(nodeLeft, treeLeft, treeMiddle, l, r, value);
		update(nodeRight, treeMiddle + 1, treeRight, l, r, value);
		arbint[node] = arbint[nodeLeft] + arbint[nodeRight];
		if(!isDp)
			arbint[node] = std::max(arbint[nodeLeft], arbint[nodeRight]);
	}

	T query(const int& node, const int& treeLeft, const int& treeRight, const int& l, const int& r)  {
		int nodeLeft = (node << 1);
		int nodeRight = nodeLeft + 1;
		if(!isDp)
			prepMan++;

		if(lazy[node])  {
			arbint[node] = lazy[node] * ::size(treeLeft, treeRight);
			if(!isDp)
				arbint[node] = lazy[node];
			if(treeLeft != treeRight)  {
				lazy[nodeLeft] = lazy[node];
				lazy[nodeRight] = lazy[node];
			}
			lazy[node] = 0;
		}
		if(r < treeLeft || treeRight < l)
			return 0;

		if(l <= treeLeft && treeRight <= r)  {
			if(!isDp)  {
				lastSeen[r] = updateCounter;
				if(arbint[node])
					sInit[l] = updates[arbint[node]];
			}
			return arbint[node];
		}
		if(isDp)  {
			const int treeMiddle = (treeRight + treeLeft) >> 1;
			const T& queryLeft = query(nodeLeft, treeLeft, treeMiddle, l, r);
			const T& queryRight = query(nodeRight, treeMiddle + 1, treeRight, l, r);
			return queryLeft + queryRight;
		}else{
			if(lastSeen[r] >= arbint[node])  {
				saves++;
				return lastSeen[r];
			}else{
				const int treeMiddle = (treeRight + treeLeft) >> 1;
				const T& queryLeft = query(nodeLeft, treeLeft, treeMiddle, l, r);
				const T& queryRight = query(nodeRight, treeMiddle + 1, treeRight, l, r);
				return queryLeft + queryRight;
			}
		}
	}
	public:
	SegmentTree()  {}
	SegmentTree(int size)  {
		this -> size = size;
		arbint = std::vector <T> (4 * size + 1, 0);
		lazy = std::vector <T> (4 * size + 1, 0);
	}

	inline T get(const int& pos)  {
		return query(1, 1, size, pos, pos);
	}
	inline void update(const int& l, const int& r, const T& value)  {
		update(1, 1, size, l, r, value);
	}

	inline T query(const int& l, const int& r)  {
		return query(1, 1, size, l, r);
	}
	inline int size1()  {
		return this -> size;
	}
	inline void toggleDp()  {
		isDp = !isDp;
	}
};

SegmentTree <long long> dp;
SegmentTree <long long> string;
int n, k, queryNo;
int kEven, kOdd;

const int maxNLength = 1e5 + 1;
char s[maxNLength];
char sManacher[maxNLength * 2];
bool initStar = false;
int dManacher[maxNLength * 2];

inline char getInit(int pos)  {
	return blocks[blockCorespondent[pos]].getCh(pos);	
}


// Reads data from the string segment tree and updates the 
// manacher string

inline void prepareManacherString(const int& l, const int& r)  {
	if(!initStar)  {
		for(int i = 1;i <= n;i++)
			sManacher[(i << 1) + 1] = '*';
		sManacher[1] = '*';
		initStar = true;
	}
	for(int i = l;i <= r;i++)  {
		sManacher[(i << 1)] = getInit(i), prepMan++;
	}
}

namespace manacherConsts  {
	// Tells manacher if it should use the centres as the limits
	// as well instead of calculating the limits
	// Useful for print queries
	bool shouldUseManualBool = false;
	int manualL;
	int manualR;
	bool manualLimitsSet = false;
	inline bool shouldUseManual()  {
		bool aux = shouldUseManualBool;
		shouldUseManualBool = false;
		return aux;
	}
	inline std::pair <int, int> retrieveManual()  {
		manualLimitsSet = false;
		return std::make_pair(manualL, manualR);
	}

	inline void setManual(const int& l, const int& r)  {
		manualL = l;
		manualR = r;
		manualLimitsSet = true;
		shouldUseManualBool = true;
	}
}

// Manacher, for shorter queries
// centreL and centreR are the centre bounds that need to be used
// l and r and the bounds of the the manacher string, and (l, r) and
// (centreL, centreR) sometimes differ!
inline long long manacher(const int& centreL, const int& centreR, const bool& shouldUpdate)  {
	if(centreL > centreR)  {
		manacherConsts::shouldUseManualBool = false;
		manacherConsts::manualLimitsSet = false;
		return 0;
	}


	int l = std::max(1, std::min(centreL - kEven, centreL - kOdd + 1));
	int r = std::min(n, std::max(centreR + kOdd - 1, centreR + kEven - 1));

	if(manacherConsts::shouldUseManual())  {
		l = centreL;
		r = centreR;

		if(manacherConsts::manualLimitsSet)  {
			const std::pair <int, int> lr = manacherConsts::retrieveManual();
			l = lr.first;
			r = lr.second;
		}
	}



	prepareManacherString(l, r);
	int newL = (l << 1) - 1;
	int newR = (r << 1) + 1;

	int bestIndex = newL;
	int bestRange = -1;
	for(int index = newL;index <= newR;index++)  {
		dManacher[index] = 0;
		if(bestIndex + bestRange >= index)  {
			dManacher[index] = std::min(dManacher[2 * bestIndex - index],
				(bestIndex - index + bestRange));
		}
		while(index + dManacher[index] + 1 <= newR && index - dManacher[index] - 1 >= newL &&
			sManacher[index + dManacher[index] + 1] == sManacher[index - dManacher[index] - 1])
			dManacher[index]++;

		if(index + dManacher[index] > bestIndex + bestRange)  {
			bestIndex = index;
			bestRange = dManacher[index];
		}
	}

	long long ans = 0;

	long long previousAns = 0;

	for(int i = newL;i <= newR;i++)  {
		int actualPosition = (i + 1) >> 1;

		if(actualPosition < centreL || actualPosition > centreR)  {
			continue;
		}
		int preAns = (dManacher[i] + 1) >> 1;

		if(!(i & 1))  {
			preAns = std::min(preAns, (k + 1) >> 1);
			// Make sure we don't go out of bounds
			preAns = std::min(preAns, actualPosition - l + 1);
			preAns = std::min(preAns, r - actualPosition + 1);
			ans += preAns;
		}else{
			preAns = std::min(preAns, k >> 1);
			preAns = std::min(preAns, actualPosition - l);
			preAns = std::min(preAns, r - actualPosition + 1);
			ans += preAns;
		}

		if(shouldUpdate)  {
			previousAns += preAns;
			if(!(i & 1))  {
				dp.update(actualPosition, actualPosition, previousAns);
				previousAns = 0;
			}
		}
	}
	return ans;
}

inline void updateDp(const int& l, const int& r)  {

	const int lowerBound = std::max(l + kEven, l + kOdd - 1);
	const int upperBound = std::min(r - kEven + 1, r - kOdd + 1);

	int centreLimits[2];

	// We need to manually recalculate dps that intersect with [l, r],
	// but aren't fully covered by [l, r]


	centreLimits[0] = std::max(1, std::min(l - kEven + 1, l - kOdd + 1));
	centreLimits[1] = std::min(n, std::max(r + kOdd - 1, r + kEven));

	if(lowerBound <= upperBound)  {
		dp.update(lowerBound, upperBound, k);
		manacher(centreLimits[0], lowerBound - 1, true);
		manacher(upperBound + 1, centreLimits[1], true);
	}else{
		manacher(centreLimits[0],
			centreLimits[1], true);
	}
}

inline long long queryDp(const int& l, const int& r)  {

	const int lowerBound = std::max(l + kEven, l + kOdd - 1);
	const int upperBound = std::min(r - kEven + 1, r - kOdd + 1);

	long long ans = 0;

	if(lowerBound <= upperBound)  {
		ans += dp.query(lowerBound, upperBound);

		manacherConsts::setManual(l, std::min(r, lowerBound - 1 + std::max(kEven, kOdd) - 1));
		ans += manacher(l, lowerBound - 1, false);

		manacherConsts::setManual(std::max(l, upperBound + 1 - std::max(kEven, kOdd - 1)), r);
		ans += manacher(upperBound + 1, r, false);
	}else{
		manacherConsts::setManual(l, r);
		ans += manacher(l, r, false);
	}

	return ans;
}

inline void printString(FILE *out)  {
	for(int i = 1;i <= string.size1();i++)  {
		string.get(i);
		fprintf(out, "%c", getInit(i));
	}
	fprintf(out, "\n");
}



#define EASY_IO 0
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
	std::cin >> sInit >> k >> queryNo;
	n = sInit.size();
	kEven = k >> 1;
	kOdd = k - kEven;
	sInit.insert(0, 1, 0);
	dp = SegmentTree <long long>(n);
	dp.toggleDp();
	string = SegmentTree <long long>(n);
	updates.push_back(0);

    blockSize = std::max(k, (int)sqrt(n));
    for(int i = 1;i <= n;i += blockSize)  {
        int l = i;
        int r = std::min(n, i + blockSize - 1);
        blocks.push_back(block(l, r, blockIndex, false, 0));
		for(int pos = l;pos <= r;pos++)
			blockCorespondent[pos] = blockIndex;
        blockIndex++;
    }

	manacher(1, n, true);
	while(queryNo--)  {
		#if EASY_IO && STRING_CHECK
		printString(stringCheck);
		#endif
		#if EASY_IO && CHRONO_IN
		if((queryNo + 1) % (int)1e4 == 0)
		std::cerr << "Working... " << queryNo << "\n";
		#endif
		int queryType, l, r;
		std::cin >> queryType >> l >> r;
		if(queryType == 1)  {
			updateCounter++;
			qType = 0;
			char fillCh;
			std::cin >> fillCh;
			updates.push_back(fillCh);
			// string.update(l, r, updateCounter);
			fillBlocks(l, r, fillCh);
			updateDp(l, r);
		}else  {
			qType = 1;
			queryCounter++;

			std::cout << queryDp(l, r) << "\n";
		}
	}

    #if CHRONO_IN
    auto finished_time = std::chrono::high_resolution_clock::now();
    std::cerr << "Time elapsed (s):\n";
    std::cerr << (double)std::chrono::duration_cast<std::chrono::milliseconds>(finished_time - started_time).count() / 1000.0 << "\n";
	std::cerr << prepMan << "\n" << saves << "\n";
    #endif

	return 0;
}