#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <utility>
#include <cstring>

inline std::pair <int, bool> find(int node, std::vector <int> &dad, std::vector <std::pair <int, int>> &sons)  {
    int prev = node;
    if(node == dad[node])  {
        return std::make_pair(node, 0);
    }
    while(node != dad[node])  {
        prev = node;
        node = dad[node];
    }
    if(prev == sons[node].first)  {
        return std::make_pair(node, 0);
    }else{
        return std::make_pair(node, 1);
    }
}

inline bool unite(int node1, int node2, int code, std::vector <int> &dad, std::vector <std::pair <int, int>> &sons)  {
    std::pair <int, bool> T1, T2;
    T1 = find(node1, dad, sons);
    T2 = find(node2, dad, sons);
    if(T1.first == T2.first)  {
        if(code == 0 && (T1.second != T2.second))  {
            return false;
        }
        if(code == 1 && (T1.second == T2.second))  {
            return false;
        }
        return true;
    }
    if((T1.second == T2.second && code == 0) || (T1.second != T2.second && code == 1))  {
        dad[T2.first] = T1.first;
        if(sons[T1.first].second == -1)  {
            sons[T1.first].second = sons[T2.first].second;
            if(sons[T2.first].second != -1)
                dad[sons[T2.first].second] = T1.first;
            sons[T2.first].second = -1;
        }else  {
            if(sons[T2.first].second != -1)
                dad[sons[T2.first].second] = sons[T1.first].second;
            sons[T2.first].second = -1;
        }
        if(sons[T1.first].first != -1)
            dad[sons[T1.first].first] = T2.first;
        sons[T2.first].first = -1;
        sons[T1.first].first = T2.first;
    }else{
        dad[T2.first] = T1.first;
        if(sons[T1.first].first == -1)  {
            sons[T1.first].first = sons[T2.first].second;
            if(sons[T2.first].second != -1)
                dad[sons[T2.first].second] = T1.first;
            sons[T2.first].second = -1; 
        }else  {
            if(sons[T2.first].second != -1)
                dad[sons[T2.first].second] = sons[T1.first].first;
            sons[T2.first].second = -1;
        }
        if(sons[T1.first].second != -1)
            dad[sons[T1.first].second] = T2.first;
        sons[T2.first].first = -1;
        sons[T1.first].second = T2.first;
    }
    return true;
}


inline bool solve()  {
    int n;
    std::cin >> n;
    if(n < 0)  {
        // Opreste citirea
        return false;
    }
    int t, ct;
    std::cin >> t;
    ct = t;
    std::unordered_map <int, bool> viz;
    std::unordered_map <int, int> normalizedVals;
    std::vector <int> diffValues; // Used for normalization
    std::vector <std::tuple <int, int, char*>> originals; // All the tests
    while(ct--)  {
        int l, r;
        char *s = new char(4 * sizeof(char));
        std::cin >> l >> r >> s;
        originals.push_back(std::make_tuple(l - 1, r, s));
        if(!viz[l - 1])
            viz[l - 1] = 1, diffValues.push_back(l - 1);
        if(!viz[r])
            viz[r] = 1, diffValues.push_back(r);
    }
    std::sort(diffValues.begin(), diffValues.end());
    for(int i = 0;i < diffValues.size();i++)  {
        const int &x = diffValues[i];
        normalizedVals[x] = i;
    }
    const int maxVal = diffValues.size();
    for(auto &x : originals)  {
        std::get<0>(x) = normalizedVals[std::get<0>(x)];
        std::get<1>(x) = normalizedVals[std::get<1>(x)];
    }
    std::vector <int> dad(maxVal);
    std::vector <std::pair <int, int>> sons(maxVal);
    // Only dsu roots will have "sons" split into identical to root and opposite to root
    for(int i = 0;i < maxVal;i++)  {
        dad[i] = i;
        sons[i].first = -1;
        sons[i].second = -1;
    }
    for(ct = 0;ct < t;ct++)  {
        const auto &x = originals[ct];
        int l = std::get <0> (x);
        int r = std::get <1> (x);

        int add = 0;
        if(!strcmp(std::get <2> (x), "odd"))
            add = 1;
        bool result = unite(l, r, add, dad, sons);

        if(result == false)  {
            std::cout << ct << "\n";
            return true;
        }
    }
    std::cout << t << "\n";
    return true;
}

#define EASY_IO 0

int main()  {
    #if EASY_IO
    freopen("aux.in", "r", stdin);
    freopen("aux.out", "w", stdout);
    #endif
    while(solve())  {}
    return 0;
}