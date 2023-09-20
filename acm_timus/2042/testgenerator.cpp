#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

int giveNo(int l, int r)  {
    return abs(rand()) % (r - l + 1) + l;
}

char giveCh()  {
    return (char)giveNo('a', 'z');
}

inline std::string generateString(int length)  {
    std::string ans;
    for(int i = 0;i < length;i++)  {
        ans.push_back(giveCh());
    }
    return ans;
}

const int maxN = 205;
const int maxM = maxN;
const int maxK = 40;

int main()  {
    freopen("aux.in", "w", stdout);
    srand(time(NULL));
    int k, m;
    int n;
    m = giveNo(1, maxM);
    n = giveNo(1, maxN);
    k = giveNo(1, std::min(maxK, n));
    std::cout << generateString(n) << " " << k << "\n" << m << "\n";
    for(int i = 1;i <= m;i++)  {
        int type, l, r;
        type = giveNo(1, 40);
        type = type > 30 ? 1 : 2;
        if(type == 1)  {
            char ch = giveCh();
            l = giveNo(1, n);
            r = giveNo(l, n);
            std::cout << type << " " << l << " " << r << " " << ch << "\n";
        }else  {
            l = giveNo(1, n);
            r = giveNo(l, n);
            std::cout << type << " " << l << " " << r << "\n";
        }
    }
    return 0;
}