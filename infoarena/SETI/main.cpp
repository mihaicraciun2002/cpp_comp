#include <bits/stdc++.h>

using namespace std;

const int maxm = 32001;

int N, M;

string s;

char decod(char ch);

class trie  {
    public:
    vector <int> vizitatori;
    unsigned short ap;
    map <char, trie*> sons;
    trie()  {
        ap = 0;
    }
};

trie *root = new trie();

int currAns;
string toRead;
int toReadIndex;

void add(trie* node)  {
    if(toReadIndex == toRead.size())  {
        node -> vizitatori.push_back(currAns);
        return;
    }
    char current = decod(toRead[toReadIndex]);
    if(node -> sons[current] == nullptr)  {
        node -> sons[current] = new trie();
    }
    toReadIndex++;
    add(node -> sons[current]);
}

int ans[maxm];

void add2(trie *node, int l, int r)  {
    if(l == r)  {
        return;
    }
    char current = decod(s[l]);
    if(node -> sons[current] == nullptr)  {
        return;
    }
    node -> sons[current] -> ap++;
    add2(node -> sons[current], l + 1, r);
}

void dfs(trie *node)  {
    for(auto x : node -> vizitatori)
        ans[x] = node -> ap;
    for(auto son : node -> sons)  {
        if(son.second != nullptr)
            dfs(son.second);
    }
}

char decod(char ch)  {
    if('a' <= ch && ch <= 'z')
        return ch - 'a';
    return ch - 'A' + 26;
}

int main()  {
    freopen("seti.in", "r", stdin);
    freopen("seti.out", "w", stdout);
    cin >> N;
    for(int i = 1;i <= N;i++)  {
        string aux;
        cin >> aux;
        s.append(aux);
    }
    cin >> M;
    for(int i = 1;i <= M;i++)  {
        cin >> toRead;
        currAns = i;
        toReadIndex = 0;
        add(root);
    }
    for(int i = 0;i < s.size();i++)  {
        add2(root, i, min((int)s.size(), i + 20));
    }
    dfs(root);
    for(int i = 1;i <= M;i++)
        cout << ans[i] << "\n";
    return 0;
}