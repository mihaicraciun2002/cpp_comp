#include <bits/stdc++.h>

using namespace std;

#define pii pair <int, int>
#define l first
#define c second

const int maxn = 151;
const int maxm = 16;
const int maxconf = (1 << 15) + 1;
int confMAX;

int d[maxn][maxconf], dnegat[maxn][maxconf];
bool viz[maxn][maxm];

int n, m, k;

inline bool valid(int linie, int conf)  {
    bool ok = 1;
    int prev = -2, cnt = 0;
    vector <int> tiles;
    while(conf)  {
        if(conf & 1)  {
            tiles.push_back(cnt);
            if(cnt - prev < 2)  {
                return 0;
            }
            prev = cnt;
        }
        cnt++;
        conf >>= 1;
    }
    if(tiles[tiles.size() - 1] == m - 1)  {
        return 0;
    }
    for(auto tile : tiles)  {
        if(viz[linie][tile] or viz[linie][tile + 1] or
            viz[linie - 1][tile] or viz[linie - 1][tile + 1])
                return 0;
    }
    return ok;
}

int neg(int conf)  {
    int ans = 0;
    int nrb = 0, prev = 0;
    while(conf)  {
        if(conf % 4 == 0 && prev == 0)  {
            ans++;
        }
        prev = conf % 2;
        ans *= 2;
        conf /= 2;
    }
    return ans;
}

int main()  {
    freopen("pavare.in", "r", stdin);
    freopen("pavare.out", "w", stdout);
    cin >> n >> m >> k;
    for(int i = 0;i < k;i++)  {
        int x, y;
        cin >> x >> y;
        x--, y--;
        viz[x][y] = 1;
    }
    confMAX = 1 << m;
    for(int linie = 1;linie < n;linie++)  {
        // conf = 0
        for(int conf = 0;conf < confMAX;conf++)  {
            d[linie][0] = max(d[linie][0], d[linie - 1][conf]);
        }
        for(int conf = 1;conf < confMAX;conf++)  {
            if(valid(linie, conf))  {
                int confcpy = conf;
                int bits = 1;
                int nrbits = 0;
                while(confcpy)  {
                    if(confcpy & 1)  {
                        nrbits++;
                        d[linie][conf] = max(d[linie][conf], d[linie][conf - bits]);
                    }
                    bits <<= 1;
                    confcpy >>= 1;
                }
                d[linie][conf] = max(d[linie][conf], dnegat[linie - 1][conf] + nrbits);
            }else{
                int confcpy = conf;
                int bits = 1;
                while(confcpy)  {
                    if(confcpy & 1)  {
                        d[linie][conf] = max(d[linie][conf], d[linie][conf - bits]);
                    }
                    bits <<= 1;
                    confcpy >>= 1;
                }
            }
        }
        for(int conf = 0;conf < confMAX;conf++)  {
            dnegat[linie][conf] = d[linie][neg(conf)];
        }
    }
    int ans = 0;
    for(int conf = 0;conf < confMAX;conf++)  {
        ans = max(ans, d[n - 1][conf]);
    }
    cout << ans;
    return 0;
}