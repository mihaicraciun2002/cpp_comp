#include <bits/stdc++.h>

inline bool dif(char a, char b, char c){
    if(a == b || a == c || b == c)
        return false;
    return true;
}

inline void solve(){
    std::string s;
    std::cin >> s;
    for(int i = 0;i + 1 < s.size();i++){
        if(s[i] == s[i + 1]){
            std::cout << s[i] << s[i + 1] << "\n";
            return;
        }
        if(i > 0 && dif(s[i - 1], s[i], s[i + 1])){
            std::cout << s[i - 1] << s[i] << s[i + 1] << '\n';
            return;
        }
    }
    std::cout << "-1" << '\n';
}

int main(){
    int t;
    std::cin >> t;
    while(t--){
        solve();
    }
    return 0;
}