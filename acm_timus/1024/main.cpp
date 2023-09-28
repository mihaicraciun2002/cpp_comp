#include <cstdio>
#include <vector>

int N;
std::vector <int> v;
std::vector <bool> viz;
std::vector <int> cycles;

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
	for(const auto& x : cycles)  {
		printf("%d ", x);
	}
	return 0;
}