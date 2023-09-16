#include <bits/stdc++.h>

using namespace std;

int N;
int ans, displays;
bool vf[15];
bool vfpoz[30];
bool vfpoz2[30];
int aux[15];

void bkt(int cnt)  {
    if(cnt == N)  {
        if(displays < 3)  {
            for(int i = 1;i <= N;i++)
                printf("%d ", aux[i]);
            printf("\n");
            displays++;
        }
        ans++;
        return;
    }
    for(int i = 1;i <= N;i++)  {
        if(vf[i] == 0 && vfpoz[i - (cnt + 1) + 14] == 0 && vfpoz2[i + (cnt + 1)] == 0)  {
            aux[cnt + 1] = i;
            vf[i] = 1;
            vfpoz[i - (cnt + 1) + 14] = 1;
            vfpoz2[i + cnt + 1] = 1;
            bkt(cnt + 1);
            aux[cnt + 1] = 0;
            vf[i] = 0;
            vfpoz[i - (cnt + 1) + 14] = 0;
            vfpoz2[i + cnt + 1] = 0;
        }
    }
}

int main()  {
    freopen("regine.in", "r", stdin);
    freopen("regine.out", "w", stdout);
    scanf("%d", &N);
    int mid = N / 2;
    int ansMid = 0;
    for(int i = 1;i <= mid;i++)  {
        aux[1] = i;
        vf[i] = 1;
        vfpoz[i - 1 + 14] = 1;
        vfpoz2[i + 1] = 1;
        bkt(1);
        aux[1] = 0;
        vf[i] = 0;
        vfpoz[i - 1 + 14] = 0;
        vfpoz2[i + 1] = 0;
    }
    if(N % 2)  {
        int anscp = ans;
        ans = 0;
        for(int i = mid + 1;i <= mid + 1;i++)  {
            aux[1] = i;
            vf[i] = 1;
            vfpoz[i - 1 + 14] = 1;
            vfpoz2[i + 1] = 1;
            bkt(1);
            aux[1] = 0;
            vf[i] = 0;
            vfpoz[i - 1 + 14] = 0;
            vfpoz2[i + 1] = 0;
        }
        ans += 2 * anscp;
    }else{ans *= 2;}
    int ii = N / 2 + N % 2 + 1;
    int anscp = ans;
    while(ii <= N && displays < 3)  {
        for(int i = ii;i <= ii;i++)  {
            aux[1] = i;
            vf[i] = 1;
            vfpoz[i - 1 + 14] = 1;
            vfpoz2[i + 1] = 1;
            bkt(1);
            aux[1] = 0;
            vf[i] = 0;
            vfpoz[i - 1 + 14] = 0;
            vfpoz2[i + 1] = 0;
        }
        ii++;
    }
    ans = anscp;
    printf("%d\n", ans);
    return 0;
}