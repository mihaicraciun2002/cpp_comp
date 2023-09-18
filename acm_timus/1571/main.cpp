#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

int N;
std::unordered_map <std::string, bool> vf;
std::vector <std::string> ans;

int main()  {
    std::cin >> N;
    if(N == 1)  {
        std::cout << "0\n";
        return 0;
    }
    if(N == 2)  {
        std::string a1, a2;
        std::cin >> a1 >> a2;
        if(a1 == a2)  {
            std::cout << "0\n";
        }else{
            std::cout << "1\n";
            std::cout << a1 << "-" << a2 << "\n";
        }
        return 0;
    }
    for(int i = 0;i < N;i++)  {
        std::string aux;
        std::cin >> aux;
        if(vf[aux])  {
            std::cout << "Impossible\n";
            return 0;
        }
        vf[aux] = true;
        ans.push_back(aux + "-" + "bruh");
    }
    std::cout << N << "\n";
    for(const auto &ansStr : ans)
        std::cout << ansStr << "\n";
    return 0;
}