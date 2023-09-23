#include <cstdio>
#include <vector>
#include <cassert>
#include <string>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unordered_map>

inline int size(const int& l, const int& r)  {
	assert(l <= r);
	return r - l + 1;
}

inline int threeMax(const int& a, const int& b, const int& c)  {
	return std::max(a, std::max(b, c));
}

inline int threeMin(const int& a, const int& b, const int& c)  {
	return std::min(a, std::min(b, c));
}

template <typename T>
class SegmentTree  {
	private:
	std::vector <T> arbint, lazy;
	int size;

	void update(const int& node, const int& treeLeft, const int& treeRight, const int& l, const int& r, const T& value)  {
		if(lazy[node])  {
			arbint[node] = lazy[node] * ::size(treeLeft, treeRight);
			if(treeLeft != treeRight)  {
				lazy[node * 2] = lazy[node];
				lazy[node * 2 + 1] = lazy[node];
			}
			lazy[node] = 0;
		}
		if(r < treeLeft || treeRight < l)
			return;
		if(l <= treeLeft && treeRight <= r)  {
			arbint[node] = value * ::size(treeLeft, treeRight);
			if(treeLeft != treeRight)  {
				lazy[node * 2] = value;
				lazy[node * 2 + 1] = value;
			}
			return;
		}
		const int treeMiddle = (treeRight + treeLeft) / 2;
		update(node * 2, treeLeft, treeMiddle, l, r, value);
		update(node * 2 + 1, treeMiddle + 1, treeRight, l, r, value);
		arbint[node] = arbint[node * 2] + arbint[node * 2 + 1];
	}

	T query(const int& node, const int& treeLeft, const int& treeRight, const int& l, const int& r)  {
		if(lazy[node])  {
			arbint[node] = lazy[node] * ::size(treeLeft, treeRight);
			if(treeLeft != treeRight)  {
				lazy[node * 2] = lazy[node];
				lazy[node * 2 + 1] = lazy[node];
			}
			lazy[node] = 0;
		}
		if(r < treeLeft || treeRight < l)
			return 0;
		if(l <= treeLeft && treeRight <= r)  {
			return arbint[node];
		}
		const int treeMiddle = (treeRight + treeLeft) / 2;
		const T& queryLeft = query(node * 2, treeLeft, treeMiddle, l, r);
		const T& queryRight = query(node * 2 + 1, treeMiddle + 1, treeRight, l, r);
		return queryLeft + queryRight;
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
};

SegmentTree <long long> dp;
SegmentTree <long long> string;
std::string sInit;
int n, k, queryNo;
const int maxNLength = 1e5 + 1;
char s[maxNLength];
char sManacher[maxNLength * 2];
bool initStar = false;
int dManacher[maxNLength * 2];

// Reads data from the string segment tree
inline void prepareManacherString(const int& l, const int& r)  {
	if(!initStar)  {
		for(int i = 1;i <= n;i++)
			sManacher[2 * i + 1] = '*';
		sManacher[1] = '*';
		initStar = true;
	}
	for(int i = l;i <= r;i++)
		sManacher[2 * i] = (char)string.get(i);
}

// Manacher on the string from l to r, for shorter queries
inline long long manacher(const int& l1, const int& r1, const int& centreL, const int& centreR, const bool& shouldUpdate)  {
	if(l1 > r1)  {
		return 0;
	}
	const int l = std::max(1, l1);
	const int r = std::min(n, r1);
	prepareManacherString(l, r);
	int newL = l * 2 - 1;
	int newR = r * 2 + 1;
	memset(dManacher + newL, 0, (newR - newL + 1) * sizeof(int));
	for(int i = newL;i <= newR;i++)  {
		assert(dManacher[i] == 0);
	}
	int bestIndex = newL;
	int bestRange = -1;
	for(int index = newL;index <= newR;index++)  {
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

	std::unordered_map <int, long long> tmpAns;

	for(int i = newL;i <= newR;i++)  {
		int actualPosition = (i + 1) / 2;
		if(actualPosition < centreL || actualPosition > centreR)  {
			continue;
		}
		int preAns = (dManacher[i] + 1) / 2;
		if(i % 2 == 0)  {
			preAns = std::min(preAns, (k + 1) / 2);
			preAns = std::min(preAns, actualPosition - centreL + 1);
			preAns = std::min(preAns, centreR - actualPosition + 1);
			ans += 1LL * preAns;
		}else{
			preAns = std::min(preAns, k / 2);
			preAns = std::min(preAns, actualPosition - centreL);
			preAns = std::min(preAns, centreR - actualPosition + 1);
			ans += 1LL * preAns;
		}
		if(shouldUpdate)
			tmpAns[actualPosition] += 1LL * preAns;
	}
	if(shouldUpdate)
		for(const auto &x : tmpAns)
			dp.update(x.first, x.first, x.second);

	return ans;
}

inline void updateDp(const int& l, const int& r)  {
	const int kEven = k / 2;
	const int kOdd = k / 2 + k % 2;
	const int lowerBound = std::max(l + kEven, l + kOdd - 1);
	const int upperBound = std::min(r - kEven + 1, r - kOdd + 1);

	int centreLimits[2];

	centreLimits[0] = std::max(1, std::min(l - kEven + 1, l - kOdd + 1));
	centreLimits[1] = std::min(n, std::max(r + kOdd - 1, r + kEven));

	// Three piece update:
	// for all centres from centreLimits[0] -> lowerBound - 1, then a ranged update
	// from lowerBound to upperBound, then for all centres from upperbound + 1 to
	// centreLimits[1]
	// the bounds are for the range of dps that we can safely fill with k

	int limits[2][2];
/* 	limits[0][0] = threeMax(1, l - 2 * kOdd, l - 2 * kEven - 1);
	limits[0][1] = threeMin(n, l - 1 + 2 * kOdd, l - 1 + 2 * kEven - 1);
	limits[1][0] = threeMax(1, r + 1 - 2 * kOdd, r + 1 - 2 * kEven - 1);
	limits[1][1] = threeMin(n, r + 2 * kOdd, r + 2 * kEven - 1); */

	limits[0][0] = std::max(1, centreLimits[0] - k);
	limits[0][1] = std::min(n, lowerBound - 1 + k);
	limits[1][0] = std::max(1, upperBound + 1 - k);
	limits[1][1] = std::min(n, centreLimits[1] + k);

	std::cerr << lowerBound << " " << upperBound << "\n";

	if(lowerBound <= upperBound)  {
		dp.update(lowerBound, upperBound, k);
		manacher(limits[0][0], limits[0][1], centreLimits[0], lowerBound - 1, true);
		manacher(limits[1][0], limits[1][1], upperBound + 1, centreLimits[1], true);
	}else{
		manacher(limits[0][0], limits[1][1], centreLimits[0],
			centreLimits[1], true);
	}
}

inline long long queryDp(const int& l, const int& r)  {
	const int kEven = k / 2;
	const int kOdd = k / 2 + k % 2;
	const int lowerBound = std::max(l + kEven, l + kOdd);
	const int upperBound = std::min(r - kEven + 1, r - kOdd);

	long long ans = 0;

	if(lowerBound <= upperBound)  {
		ans += dp.query(lowerBound, upperBound);
		ans += manacher(std::max(1, l - kOdd), std::min(n, lowerBound - 1 + kOdd),
			l, lowerBound - 1, false);
		ans += manacher(std::max(1, upperBound - kOdd), std::min(n, r + kOdd),
			upperBound + 1, r, false);
	}else{
		ans += manacher(std::max(1, l - kOdd), std::min(n, r + kOdd),
			l, r, false);
	}

	return ans;
}


inline void printString(const int& l, const int& r)  {
	for(int i = l;i <= r;i++)
		std::cerr << (char)string.get(i);
	std::cerr << "\n";
}

inline void printString()  {
	for(int i = 1;i <= string.size1();i++)  {
		std::cerr << (char)string.get(i);
	}
	std::cerr << "\n";
}

inline void printString(FILE *out)  {
	for(int i = 1;i <= string.size1();i++)  {
		fprintf(out, "%c", (char)string.get(i));
	}
	fprintf(out, "\n");
}



#define EASY_IO 1
#define STRING_CHECK 0

int main()  {
	#if EASY_IO
	freopen("aux.in", "r", stdin);
	freopen("aux.out", "w", stdout);
	#if STRING_CHECK
	FILE *stringCheck = fopen("strmain.out", "w");
	#endif
	#endif
	std::cin >> sInit >> k >> queryNo;
	n = sInit.size();
	sInit.insert(0, 1, 0);
	dp = SegmentTree <long long>(n);
	string = SegmentTree <long long>(n);

	for(int i = 1;i <= n;i++)
		string.update(i, i, sInit[i]);
	manacher(1, n, 1, n, true);
	while(queryNo--)  {
		#if EASY_IO && STRING_CHECK
		printString(stringCheck);
		#endif
		int queryType, l, r;
		std::cin >> queryType >> l >> r;
		if(queryType == 1)  {
			char fillCh;
			std::cin >> fillCh;
			string.update(l, r, fillCh);
			updateDp(l, r);
		}else  {
			// printString(l, r);
			// std::cout << manacher(1, n, l, r, false) << "\n";
			// std::cout << queryDp(l, r) << "\n";
			std::cout << dp.query(1, n) << "\n";
		}
	}
	return 0;
}