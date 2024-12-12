#include <bits/stdc++.h>

int biggestDig(int n){
    int a = 1;
    while(a <= n)
        a <<= 1;
    a >>= 1;
    return a;
}

int main(){
    int n;
    std::cin >> n;
    std::vector <int> a(n);
    for(int i = 0;i < n;i++){
        std::cin >> a[i];
    }
    // Ans is at most n - 2
    std::vector <int> partSum(n);
    partSum[0] = a[0];
    for(int i = 1;i < n;i++){
        partSum[i] = partSum[i - 1] ^ a[i];
    }
    int ans = -1;
    for(int i = 2;i < n;i++){
        if(i >= 2 && biggestDig(a[i]) == biggestDig(a[i - 1]) && biggestDig(a[i - 1]) == biggestDig(a[i - 2])){
            if(ans == -1){
                ans = 1;
            }else{
                ans = std::min(ans, 1);
            }
            std::cout << ans << '\n';
            return 0;
        }
    }
    std::vector<std::vector <int>> smallest(n), biggest(n);
    for(int i = 0;i < n;i++){
        smallest[i] = biggest[i] = {a[i]};
        int tt = a[i];
        for(int j = i - 1;j >= 0;j--){
            tt ^= a[j];
            biggest[i].push_back(tt);
        }
        tt = a[i];
        for(int j = i + 1;j < n;j++){
            tt ^= a[j];
            smallest[i].push_back(tt);
        }
    }
    for(int i = 1;i < n;i++){
        int o = i - 1, r = i;
        for(int index = 0;index < biggest[o].size();index++){
            for(int indexr = 0;indexr < smallest[r].size();indexr++){
                if(biggest[o][index] > smallest[r][indexr]){
                    ans = std::min(ans, index + indexr);
                    if(ans == -1){
                        ans = index + indexr;
                    }
                }
            }
        }
    }
    std::cout << ans << "\n";
    return 0;
}