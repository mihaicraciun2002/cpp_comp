#include <bits/stdc++.h>

using namespace std;

#define x first
#define y second
#define pii pair <int, int>
#define pdd pair <double, double>

const int maxn = 21;
const int maxm = 21;

int N, M;
pii P1[maxn], P2[maxm];

inline double arie(pii P[], int numVertices)  {
    double arie = 0;
    for(int i = 0;i < numVertices;i++)  {
        int i1 = (i + 1) % numVertices;
        arie += 1.0 * (P[i].x * P[i1].y) - 1.0 * (P[i1].x * P[i].y);
    }
    arie *= 0.5;
    return (arie > 0.0) ? arie : -arie;
}

int main()  {
    freopen("arie.in", "r", stdin);
    freopen("arie.out", "w", stdout);
    cin >> N;
    for(int i = 0;i < N;i++)
        cin >> P1[i].x >> P1[i].y;
    cin >> M;
    for(int i = 0;i < M;i++)
        cin >> P2[i].x >> P2[i].y;
    return 0;
}