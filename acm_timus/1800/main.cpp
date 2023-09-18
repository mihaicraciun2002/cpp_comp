#include <cstdio>
#include <cmath>

double l, h, w;
double g = 981.0;

char ans[][7] = {"butter", "bread"};

#define FAST_IO 0

int main()  {
    #if FAST_IO
    freopen("1800.in", "r", stdin);
    #endif

    scanf("%lf%lf%lf", &l, &h, &w);
    if(h < l / 2.0)  {
        printf("%s\n", ans[0]);
        return 0;
    }
    h -= l / 2.0;
    w /= 60.0; // from 360/minute to 360/second
    double t = sqrt(2.0 * h / g); // time to hit the ground
    double aux = w * t;
    aux -= (int) aux;
    if(aux >= 0.25 && aux <= 0.75)  {
        printf("%s\n", ans[1]);
    }else{
        printf("%s\n", ans[0]);
    }
    return 0;
}