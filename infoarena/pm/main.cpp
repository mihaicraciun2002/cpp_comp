#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

const int maxn = 500 + 1;
const int maxx = 250 + 1;
const int maxy = 250 + 1;

namespace myclass  {
    class bigInt  {
        private:
        std::vector <char> digits;
        public:
        bigInt()  {}
        bigInt(int nr)  {
            while(nr)
                digits.push_back(nr % 10), nr /= 10;
        }
        void operator = (int nr)  {
            digits.clear();
            while(nr)
                digits.push_back(nr % 10), nr /= 10;
        }
        void operator = (const bigInt &oth)  {
            digits = oth.digits;
        }
        bigInt operator + (const bigInt &oth) const  {
            bigInt ans;
            char rest = 0;
            int index = 0;
            while(index < oth.digits.size() && index < digits.size())  {
                ans.digits.push_back((digits[index] + oth.digits[index] + rest) % 10);
                rest = (digits[index] + oth.digits[index] + rest) / 10;
                index++;
            }
            while(index < oth.digits.size())  {
                ans.digits.push_back((oth.digits[index] + rest) % 10);
                rest = (oth.digits[index] + rest) / 10;
                index++;
            }
            while(index < digits.size())  {
                ans.digits.push_back((digits[index] + rest) % 10);
                rest = (digits[index] + rest) / 10;
                index++;
            }
            if(rest)  {
                ans.digits.push_back(rest);
                rest = 0;
            }
            return ans;
        }
        void operator += (const bigInt &oth)  {
            char rest = 0;
            int index = 0;
            while(index < oth.digits.size() && index < digits.size())  {
                digits[index] = (digits[index] + oth.digits[index] + rest);
                rest = digits[index] / 10;
                digits[index] %= 10;
                index++;
            }
            while(index < oth.digits.size())  {
                digits.push_back(0);
                digits[index] = (oth.digits[index] + rest);
                rest = digits[index] / 10;
                digits[index] %= 10;
                index++;
            }
            while(index < digits.size())  {
                digits[index] = (digits[index] + rest);
                rest = digits[index] / 10;
                digits[index] %= 10;
                index++;
            }
            if(rest)  {
                digits.push_back(rest);
                rest = 0;
            }
        }
        std::string print() const  {
            if(digits.size() == 0)  {
                return std::string ("0");
            }
            std::string ans;
            for(int i = digits.size() - 1;i >= 0;i--)  {
                ans.push_back(digits[i] + '0');
            }
            return ans;
        }
    };
}

FILE *fin;

int X, Y, N;
myclass::bigInt sumDCol[3][maxy];

myclass::bigInt ans = 0;

int main()  {
    fin = fopen("pm.in", "r");
    freopen("pm.out", "w", stdout);
    fscanf(fin, "%d%d", &X, &Y);
    N = X + Y;
    if(Y == 1)  {
        std::cout << N << "\n";
        fclose(fin);
        return 0;
    }

    int nLast, nMid, nOld;

    for(int n = 1;n <= N;n++)  {
        nLast = n % 3; // n
        nMid = (n + 2) % 3; // n - 1
        nOld = (n + 1) % 3; // n - 2
        sumDCol[nLast][1] = 1;
        sumDCol[nLast][1] = sumDCol[nLast][1] + sumDCol[nMid][1];
        for(int y = 2;y <= std::min(n, Y);y++)  {
            sumDCol[nLast][y] = sumDCol[nMid][y];
            sumDCol[nLast][y] = sumDCol[nLast][y] + sumDCol[nOld][y - 1];
            if(y == Y)  {
                ans = ans + sumDCol[nOld][y - 1];
            }
        }
    }
    std::cout << ans.print() << "\n";
    fclose(fin);
    return 0;
}