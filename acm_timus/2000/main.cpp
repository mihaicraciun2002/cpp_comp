#include <cstdio>

const int maxn = 1e5 + 1;
int v[maxn];
int n;
int player1, player2;
int sum1, sum2;
int midPos;

#define EASY_IO 0

int main()  {
    #if EASY_IO
    freopen("aux.in", "r", stdin);
    #endif
    scanf("%d", &n);
    for(int i = 1;i <= n;i++)
        scanf("%d", &v[i]);
    scanf("%d%d", &player1, &player2);
    midPos = (player1 + player2) / 2;
    if(player1 > player2)  {
        if(player1 % 2 != player2 % 2)
            midPos++;
        for(int i = n;i >= midPos;i--)
            sum1 += v[i];
        for(int i = 1;i < midPos;i++)
            sum2 += v[i];
    }else if(player1 < player2){
        for(int i = 1;i <= midPos;i++)
            sum1 += v[i];
        for(int i = n;i > midPos;i--)
            sum2 += v[i];
    }else{
        for(int i = 1;i < midPos;i++)
            sum1 += v[i];
        for(int i = midPos + 1;i <= n;i++)
            sum2 += v[i];
        if(sum1 < sum2)  {
            int aux = sum2;
            sum2 = sum1;
            sum1 = aux;
        }
        sum1 += v[midPos];
    }
    printf("%d %d\n", sum1, sum2);
    return 0;
}