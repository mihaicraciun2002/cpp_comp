#include <bits/stdc++.h>

class Test{
    public:
    int x; long long m;
    Test(int x, long long m){
        this->x = x;
        this->m = m;
    }
};

int t;
std::vector <Test> tests;
std::vector <long long> ans;

inline void print_test(FILE* out){
    fprintf(out, "%d\n", t);
    for(const auto& x : tests){
        fprintf(out, "%d %lld\n", x.x, x.m);
    }
}

inline void brute_test(){
    ans.clear();
    for(const auto &test : tests){
        int x = test.x;
        long long m = test.m, ans_ = 0;
        for(long long y = 1;y <= m;y++){
            long long div = x ^ y;
            if(div % x == 0 or div % y == 0){
                ans_++;
            }
        }
        ans.push_back(ans_);
    }
}

inline void test_out(FILE* in){
    for(int i = 0;i < t;i++){
        long long ans_;
        fscanf(in, "%lld", &ans_);
        if(ans_ != ans[i]){
            /*
            auto test = tests[i];
            int x = test.x;
            long long m = test.m, ans_ = 0;
            for(long long y = 1;y <= m;y++){
                long long div = x ^ y;
                if(div % x == 0 or div % y == 0){
                    std::cerr << y << "\n";
                }
            } */
            std::cerr << "Output mismatch at " << tests[i].x << " " << tests[i].m << " ; " << ans_ << " vs correct " << ans[i] << "\n";
        }
    }
}

inline void test1(){
    t = 0;
    tests.clear();
    for(int x = 1;x <= 100;x++){
        for(int m = 1;m <= 100;m++){
            t++;
            tests.push_back(Test(x, m));
        }
    }
}

inline void test2(){
    t = 1;
    tests.clear();
    tests.push_back(Test(3, 12));
}

int main(){
    FILE *input = fopen("chard.in", "w");

    test2();
    print_test(input);
    brute_test();

    FILE *output = fopen("chard.out", "r");

    test_out(output);

    return 0;
}