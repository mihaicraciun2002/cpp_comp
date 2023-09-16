#include <cstdio>
#include <iostream>
#include <algorithm>

FILE *fin, *fout;

const int maxn = 1e6 + 1;
const int maxk = 1e6 + 1;
const int maxval = 1e5 + 1;

int N, K;
int vf[maxval];
int v[maxn];

int main()  {
    fin = fopen("maxk.in", "r");
    fout = fopen("maxk.out", "w");
    fscanf(fin, "%d%d", &N, &K);
    bool is_trivial = true;
    int toDo = 0;
    for(int i = 1;i <= N;i++)  {
        fscanf(fin, "%d", &v[i]);
        vf[v[i]]++;
        if(vf[v[i]] == K + 1)
            is_trivial = false, toDo++;
    }
    if(is_trivial)  {
        fprintf(fout, "0\n");
        fclose(fin);
        fclose(fout);
        return 0;
    }
    int ans = maxn;
    int lIndex = 0;
    for(int rIndex = 1;rIndex <= N;rIndex++)  {
        vf[v[rIndex]]--;
        if(vf[v[rIndex]] == K)
            toDo--;
        while(lIndex < rIndex && vf[v[lIndex]] < K)  {
            vf[v[lIndex]]++;
            lIndex++;
        }
        if(toDo == 0)
            ans = std::min(ans, rIndex - lIndex + 1);
    }
    fprintf(fout, "%d", ans);
    fclose(fin);
    fclose(fout);
    return 0;
}