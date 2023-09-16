#include <bits/stdc++.h>

using namespace std;

class OutParser {
private:
    FILE *fout;
    char *buff;
    int sp;
 
    void write_ch(char ch) {
        if (sp == 50000) {
            fwrite(buff, 1, 50000, fout);
            sp = 0;
            buff[sp++] = ch;
        } else {
            buff[sp++] = ch;
        }
    }
 
 
public:
    OutParser(const char* name) {
        fout = fopen(name, "w");
        buff = new char[50000]();
        sp = 0;
    }
    ~OutParser() {
    }

    void closeFile()  {
        fwrite(buff, 1, sp, fout);
        fclose(fout);
    }
 
    OutParser& operator << (int vu32) {
        if (vu32 <= 9) {
            write_ch(vu32 + '0');
        } else {
            (*this) << (vu32 / 10);
            write_ch(vu32 % 10 + '0');
        }
        return *this;
    }
 
    OutParser& operator << (long long vu64) {
        if (vu64 <= 9) {
            write_ch(vu64 + '0');
        } else {
            (*this) << (vu64 / 10);
            write_ch(vu64 % 10 + '0');
        }
        return *this;
    }
 
    OutParser& operator << (char ch) {
        write_ch(ch);
        return *this;
    }
    OutParser& operator << (const char *ch) {
        while (*ch) {
            write_ch(*ch);
            ++ch;
        }
        return *this;
    }
};

OutParser fout("partmult.out");



int N;
int cor[11];
int szpart;
int cnt;

int categ;

void bkt()  {
    if(cnt == N)  {
        for(categ = 0;categ < szpart;categ++)  {
            for(int i = 1;i <= N;i++)  {
                if(cor[i] == categ)  {
                    fout << i << " ";
                }
            }
            if(categ + 1 < szpart)
                fout << "; ";
        }
        fout << "\n";
        return;
    }
    cnt++;

    for(int i = 0;i < szpart;i++)  {
        cor[cnt] = i;
        bkt();
    }
    szpart++;
    cor[cnt] = szpart - 1;
    bkt();
    szpart--;
    cnt--;
}

int main()  {
    freopen("partmult.in", "r", stdin);
    scanf("%d", &N);
    bkt();
    fout.closeFile();
    return 0;
}