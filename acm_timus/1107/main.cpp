#include <cstdio>
#include <cctype>

const int maxn = 100 + 1;
const int maxk = 5e4 + 1;
const int maxm = 100 + 1;
const int bufsize = 4096;

int N, K, M;

#define EASY_IO 0

static char buf[bufsize];
static int bufpos = bufsize;

inline char getCh()  {
    if(bufsize == bufpos)  {
        bufpos = 0;
        std::fread(buf, sizeof(char), bufsize, stdin);
    }
    return buf[bufpos++];
}

inline void readInt(int &n)  {
    n = 0;
    char ch = getCh();
    while(std::isdigit(ch))  {
        n = n * 10 + ch - '0';
        ch = getCh();
    }
}


int main()  {
    #if EASY_IO
    std::freopen("1107.in", "r", stdin);
    std::freopen("1107.out", "w", stdout);
    #endif
    readInt(N);
    readInt(K);
    readInt(M);
    std::printf("YES\n");
    for(int i = 1;i <= K;i++)  {
        int ans = 0, size, x;
        readInt(size);
        for(int j = 1;j <= size;j++)  {
            readInt(x);
            ans += x;
        }
        ans %= (N + 1);
        std::printf("%d\n", ans + 1);
    }
    return 0;
}