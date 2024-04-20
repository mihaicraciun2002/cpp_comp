#include <cstdio>
#include <vector>

int N;
std::vector <int> v;
std::vector <bool> viz;
std::vector <int> cycles;

inline long long gcd(long long a, long long b)  {
	if(b == 0)
		return a;
	return gcd(b, a % b);
}

inline long long lcm(long long a, long long b)  {
	return a * b / gcd(a, b);
}

int main()  {
	scanf("%d", &N);
	v = std::vector <int> (N + 1, 0);
	viz = std::vector <bool> (N + 1, false);

	for(int i = 1;i <= N;i++)
		scanf("%d", &v[i]);
	for(int i = 1;i <= N;i++)  {
		if(viz[i])
			continue;
		int startPoint = i;
		cycles.push_back(0);
		do  {
			cycles.back()++;
			viz[startPoint] = true;
			startPoint = v[startPoint];
		}while(startPoint != i);
	}
	long long ans = 1;
	for(const auto& x : cycles)  {
		ans = lcm(ans, x);
	}
	printf("%lld\n", ans);
	return 0;
}
