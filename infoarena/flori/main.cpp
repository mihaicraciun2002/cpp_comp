#include <iostream>
#include <vector>

const int maxtoate = 1000 + 1;

int N, K;

int tata[maxtoate];
int firsts[maxtoate];

inline int find(int nod)  {
    int cp = nod;
    while(nod != tata[nod])  {
        nod = tata[nod];
    }
    int aux;
    while(cp != nod)  {
        aux = tata[cp];
        tata[cp] = nod;
        cp = aux;
    }
    return nod;
}

inline void union1(int a, int b)  {
    if(find(a) == find(b))
        return;
    tata[find(a)] = find(b);
}

std::vector <int> show[maxtoate];
bool vf[maxtoate];

int main()  {
    freopen("flori.in", "r", stdin);
    freopen("flori.out", "w", stdout);
    std::cin >> N >> K;
    for(int i = 1;i < maxtoate;i++)
        tata[i] = i;
    for(int i = 1;i <= N;i++)  {
        int x, y;
        std::cin >> x;
        firsts[i] = x;
        for(int j = 2;j <= K;j++)  {
            std::cin >> y;
            union1(x, y);
        }
    }
    for(int i = 1;i <= N;i++)  {
        firsts[i] = find(firsts[i]);
        show[firsts[i]].push_back(i);
    }
    for(int i = 1;i <= N;i++)  {
        if(vf[firsts[i]])
            continue;
        vf[firsts[i]] = 1;
        for(auto x : show[firsts[i]])
            std::cout << x << " ";
        std::cout << "\n";
    }
    return 0;
}