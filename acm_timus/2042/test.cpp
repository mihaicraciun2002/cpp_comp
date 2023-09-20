#include <iostream>
#include <string>

std::string s;
int k;
int queryNo;

inline void fillString(std::string &s, const char& ch, const int& l, const int& r)  {
    for(int i = l;i <= r;i++)
        s[i] = ch;
}

inline long long query(std::string &s, const int &l, const int &r)  {
    long long ans = 0;
    for(int i = l;i <= r;i++)  {
        for(int j = i;j <= r;j++)  {
            if(j - i + 1 > k)
                continue;
            long long toAdd = 1;
            int copyi = i;
            int copyj = j;
            while(toAdd && copyi < copyj)
                toAdd = (s[copyi] == s[copyj]),
                copyi++, copyj--;
            ans += toAdd;
        }
    }
    return ans;
}

#define STRING_CHECK 0

int main()  {
    freopen("aux.in", "r", stdin);
    freopen("test.out", "w", stdout);
    #if STRING_CHECK
    FILE *stringCheck = fopen("stringtest.out", "w");
    #endif
    std::cin >> s >> k >> queryNo;
    while(queryNo--)  {
        #if STRING_CHECK
        for(const auto& ch : s)  {
            fprintf(stringCheck, "%c", ch);
        }
        fprintf(stringCheck, "\n");
        #endif
        int type, l, r;
        std::cin >> type >> l >> r;
        l--, r--;
        if(type == 1)  {
            char ch;
            std::cin >> ch;
            fillString(s, ch, l, r);
        }else  {
            std::cout << query(s, l, r) << "\n";
        }
    }
    return 0;
}