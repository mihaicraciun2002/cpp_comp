#include <bits/stdc++.h>

using namespace std;

#define ll long long

const int bufsize = 4096;
int bufpos = bufsize;
char buf[bufsize];

inline char nextCh()  {
    if(bufpos == bufsize)  {
        fread(buf, sizeof(char), sizeof(char) * bufsize, stdin);
        bufpos = 0;
    }
    return buf[bufpos++];
}

inline int readInt()  {
    char ch = nextCh();
    int num = 0;
    bool sgn = 0;
    while(!isdigit(ch) && ch != '-')
        ch = nextCh();
    if(ch  == '-')  {
        sgn = 1;
        ch = nextCh();
    }
    while(isdigit(ch))  {
        num = num * 10 + ch - '0';
        ch = nextCh();
    }
    return sgn ? -num : num;
}


class func  {
    public:
    ll A;
    ll B;
    int index;
};

const int maxn = 1e5 + 1;
const int maxm = 1e6 + 1;
const int maxval = 1e9;
const int minval = -1e9;

int N, M;
func f[maxn];
vector <func> trueF, finalF;

bool cmp(const func& one, const func& two)  {
    if(one.B == two.B)  {
        return one.A < two.A;
    }
    return one.B < two.B;
}

int intersectionTime(func one, func two)  {
    return (two.B - one.B) / (one.A - two.A) + 1;
}

vector <int> times;

int main()  {
    freopen("vmin.in", "r", stdin);
    freopen("vmin.out", "w", stdout);
    N = readInt(), M = readInt();
    for(int i = 1;i <= N;i++)  {
        f[i].A = readInt();
        f[i].B = readInt();
        f[i].index = i;
    }
    sort(f + 1, f + N + 1, cmp);
    int prevB, prevA;
    prevB = minval - 1;
    prevA = maxval + 1;
    for(int i = 1;i <= N;i++)  {
        if(f[i].B > prevB)  {
            if(f[i].A >= prevA)  {
                continue;
            }
            trueF.push_back(f[i]);
            prevB = f[i].B;
            prevA = f[i].A;
        }
    }
    finalF.push_back(trueF[0]);
    for(int i = 1;i < trueF.size();i++)  {
        finalF.push_back(trueF[i]);
        int cnt = finalF.size() - 1;
        while(cnt >= 2 && intersectionTime(finalF[cnt - 1], finalF[cnt]) <=
            intersectionTime(finalF[cnt - 2], finalF[cnt - 1]))
                swap(finalF[cnt], finalF[cnt - 1]), finalF.pop_back(), cnt--;
    }
    times.push_back(0);
    for(int i = 1;i < finalF.size();i++)
        times.push_back(intersectionTime(finalF[i - 1], finalF[i]));
    times.push_back(maxval + 1);
    for(int i = 1;i <= M;i++)  {
        int T;
        T = readInt();
        int r = -1, pas = (1 << 30);
        while(pas)  {
            if(r + pas < times.size() && times[r + pas] <= T)
                r += pas;
            pas >>= 1;
        }
        cout << finalF[r].index << " ";
    }
    return 0;
}