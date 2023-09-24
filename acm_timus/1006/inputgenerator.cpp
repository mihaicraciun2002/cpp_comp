#include <bits/stdc++.h>

using namespace std;

unordered_map <unsigned char, unsigned char> coresp;

int main()  {
    ifstream fin("helper.in");

    unsigned char s1[20];
    vector <unsigned char> s2;
    fin >> s1;
    for(int i = 0;i < 7;i++)  {
        int a;
        fin >> a;
        s2.push_back(a);
    }

    for(int i = 0;i < 7;i++)
        coresp[s1[i]] = s2[i];

    
    ofstream fout("aux.in");
    ifstream overwrite("dummyinput.in");

    for(int i = 0;i < 20;i++)  {
        unsigned char s[52];
        overwrite >> s;
        std::cerr << s << "\n";
         for(int j = 0;j < 50;j++)  {
            s[j] = (unsigned char) coresp[s[j]];
         }

        s[50] = '\n'; 
        for(int j = 0;j < 50;j++)
            fout << s[j];
        fout << "\n";
    }

    fin.close();
    fout.close();
    overwrite.close();

    return 0;
}