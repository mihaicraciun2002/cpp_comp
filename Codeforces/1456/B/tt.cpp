#include <bits/stdc++.h>

bool check(std::vector <int> v){
    for(int i = 1;i < v.size();i++){
        if(v[i] < v[i - 1]){
            return true;
        }
    }
    return false;
}

void bck(std::vector <int> v, int n, int stop){
    if(n == stop){
        for(auto x : v){
            std::cerr << x << ' ';
        }
        std::cerr << '\n';
        assert(!check(v) && "Worked!");
        return;
    }
    for(int i = 1;i < v.size();i++){
        std::vector <int> cv;
        for(int j = 0;j < i - 1;j++){
            cv.push_back(v[j]);
        }
        cv.push_back(v[i] ^ v[i - 1]);
        for(int j = i + 1;j < n;j++){
            cv.push_back(v[j]);
        }
        if(cv[0] == 29 && cv[1] == 27){
            std::cerr << v[0] << ' ' << v[1] << ' ' << v[2] << '\n';
        }
        bck(cv, n - 1, stop);
    }
}

int main(){
    std::vector <int> v{11, 22, 71, 92};
    int n = v.size();
    bck(v, n, n - 2);
}