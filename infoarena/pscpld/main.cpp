#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <iostream>

const int maxlen = 1e6 + 2;

char s[maxlen];
char a[2 * maxlen];
int d[2 * maxlen];

int sLen, N;

int main()  {
	freopen("pscpld.in", "r", stdin);
	freopen("pscpld.out", "w", stdout);
	scanf("%s", s + 1);
	sLen = strlen(s + 1);
	N = 2 * sLen + 1;
	a[1] = '*';
	for(int i = 1;i <= sLen;i++)  {
		a[2 * i] = s[i];
		a[2 * i + 1] = '*';
	}
	int range, index;
	range = 0,
	index = 1;
	long long ans = 0LL;
	int bestRange, bestIndex;
	bestIndex = 1;
	bestRange = 0;
	for(int index = 1;index <= N;index++)  {
		if(bestIndex + bestRange >= index)
			d[index] = std::min(d[2 * bestIndex - index],
				bestIndex + bestRange - index);
		while(index - d[index] - 1 >= 1 && index + d[index] + 1 <= N &&
			a[index - d[index] - 1] == a[index + d[index] + 1])
				d[index]++;
		if(index + d[index] > bestIndex + bestRange)  {
			bestIndex = index;
			bestRange = d[index];
		}
	}

	for(int i = 1;i <= N;i++)
		ans += 1LL * (d[i] + 1) / 2;
	printf("%lld\n", ans);
	return 0;
}