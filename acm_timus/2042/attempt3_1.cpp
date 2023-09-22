#include <cstdio>
#include <vector>
#include <cassert>
#include <string>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>

inline int size(const int& l, const int& r)  {
	assert(l <= r);
	return r - l + 1;
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
};

SegmentTree <long long> dpEven, dpOdd;
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

// Manacher on the string from l to r
inline long long manacher(const int& l, const int& r, const int& k)  {
	prepareManacherString(l, r);
	int newL = l * 2 - 1;
	int newR = r * 2 + 1;
	memset(dManacher + newL, 0, (newR - newL + 1) * sizeof(int));
	for(int i = newL;i <= newR;i++)
		assert(dManacher[i] == 0);
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
	for(int i = newL;i <= newR;i++)
		ans += 1LL * (dManacher[i] + 1) / 2;
	return ans;
}


#define EASY_IO 1



int main()  {
	#if EASY_IO
	freopen("aux.in", "r", stdin);
	freopen("aux.out", "w", stdout);
	#endif
	std::cin >> sInit >> k >> queryNo;
	n = sInit.size();
	sInit.insert(0, 1, 0);
	dpEven = SegmentTree <long long>(n);
	dpOdd = SegmentTree <long long>(n);
	string = SegmentTree <long long>(n);

	for(int i = 1;i <= n;i++)
		string.update(i, i, sInit[i]);
	std::cerr << "Manacher answer: " << manacher(1, n, k) << "\n";
	return 0;
}