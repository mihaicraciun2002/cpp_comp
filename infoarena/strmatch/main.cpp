#include <cstdio>
#include <cstring>
#include <cctype>
#include <vector>

const int maxlen = 2e6 + 1;

char A[maxlen], B[maxlen];
int N, M;

int pi[maxlen];
int d[maxlen];
int ansCnt;
std::vector <int> ans;

int main()  {
	freopen("strmatch.in", "r", stdin);
	freopen("strmatch.out", "w", stdout);
	scanf("%s%s", A + 1, B + 1);
	N = strlen(A + 1);
	M = strlen(B + 1);
	pi[1] = 0;
	for(int i = 2;i <= N;i++)  {
		int aux = pi[i - 1];
		while(aux && A[i] != A[aux + 1])
			aux = pi[aux];
		if(A[i] == A[aux + 1])
			aux++;
		pi[i] = aux;
	}
	for(int i = 1;i <= M;i++)  {
		int aux = d[i - 1];
		while(aux && B[i] != A[aux + 1])
			aux = pi[aux];
		if(B[i] == A[aux + 1])
			aux++;
		d[i] = aux;
		ansCnt += (d[i] == N);
		if(d[i] == N && ans.size() < 1000)  {
			ans.push_back(i - N);
		}
	}
	printf("%d\n", ansCnt);
	for(const auto &x : ans)
		printf("%d ", x);
	printf("\n");
	return 0;
}