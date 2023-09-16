#include <cstdio>
#include <algorithm>

int a, b;

inline int getPow(const int &a, int base)  {
    int cp = a, ans = 0;
    while(cp % base == 0)
        ans++, cp /= base;
    return ans;
}

int main()  {
    freopen("fractie.in", "r", stdin);
    freopen("fractie.out", "w", stdout);
    scanf("%d%d", &a, &b);
    int pow2, pow5, nPerioada;
    pow2 = getPow(b, 2) - getPow(a, 2);
    pow5 = getPow(b, 5) - getPow(a, 5);
    nPerioada = std::max(pow2, pow5);
    nPerioada = std::max(nPerioada, 0);
    printf("0.");
    while(nPerioada--)  {
        fputc((1LL * a * 10) / (b) + '0', stdout);
        a = (1LL * a * 10) % (b);
    }
    if(a == 0)  {
        return 0;
    }
    printf("(");
    int start = a;
    do  {
        fputc((1LL * a * 10) / (b) + '0', stdout);
        a = (1LL * a * 10) % (b);
    }while(start != a);
    printf(")");
    return 0;
}