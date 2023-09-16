#include <bits/stdc++.h>


using namespace std;

const long double inf = 1e9;
const long double small = 1e-14;
const long double smallForChecks = 1e-11;
const long double lessSmall = small * 2.0;

int N;
vector <long double> a;

namespace myfunc  {
    inline long double pow(long double a, int n)  {
        long double ans = 1.0;
        while(n)  {
            if(n & 1)
                ans *= a;
            a *= a;
            n >>= 1;
        }
        return ans;
    }
    inline long double sqrt(long double a)  {
        long double res = 0;
        long double pas = (long double)(1LL << 15);
        long double r = -small;
        while(pas >= small)  {
            if((r + pas) * (r + pas) <= a)
                r += pas;
            pas /= 2.0;
        }
        if(abs(r) <= small * 10.0)
            r = 0.0;
        return r;
    }
}

vector <long double> derivative(int N, const vector <long double>& a)  {
    vector <long double> ans;
    long double exp = 1.0 * N;
    for(int i = 0;i < N;i++)  {
        ans.push_back(exp * a[i]);
        exp = 1.0 * (N - i - 1);
    }
    return ans;
}

long double evaluate(long double x, int N, const vector <long double>& a)  {
    long double ans = 0.0;
    long double exp = 1.0 * N;
    for(int i = 0;i <= N;i++)  {
        ans += myfunc::pow(x, exp) * a[i];
        exp = 1.0 * (N - i - 1);
    }
    return ans;
}

inline string PrintPolyn(int N, const vector <long double>&a)  {
    string ans;
    for(const auto& x : a)  {
        if(N == 0)  {
            ans.append(to_string(x));
            break;
        }
        ans.append(to_string(x));
        ans.append(" * x ^ ");
        ans.append(to_string(N--));
        ans.append(" + ");
    }
    return ans;
}

vector <long double> division(int N, const vector <long double>& a, long double sol)  {
    vector <long double> ans;
    vector <long double> cpy = a;
    for(int i = 0;i < N;i++)  {
        ans.push_back(cpy[i]);
        cpy[i + 1] += cpy[i] * sol;
    }
    return ans;
}

vector <long double> solve(int N, vector <long double> a)  {
    if(N == 2)  {
        long double det = (a[1] * a[1] - 4.0 * a[0] * a[2]);
        if(a[0] == 0)  {
            return solve(N - 1, vector <long double> (a[1], a[2]));
        }
        if(det < 0)  {
            return vector <long double> {};
        }
        det = myfunc::sqrt(det);
        long double x1, x2;
        x1 = (-a[1] + det) / (2.0 * a[0]);
        x2 = (-a[1] - det) / (2.0 * a[0]);
        if(x1 > x2)
            swap(x1, x2);
        return vector <long double> {x1, x2};
    }
    if(N == 1)  {
        if(a[0] == 0)  {
            return vector <long double> {};
        }
        return vector <long double> {a[1] / a[0]};
    }
    if(N == 0)  {
        return vector <long double> {};
    }
    long double cpA0 = a[0];
    for(int i = 0;i <= N;i++)
        a[i] /= cpA0;
    vector <long double> deriv = derivative(N, a);
    vector <long double> derivSols = solve(N - 1, deriv);


#define DBG_DERIV 0
#if DBG_DERIV
    std::cerr << "First derivative solutions for " << PrintPolyn(N, a) << " is:\n";
    for(auto x : derivSols)  {
        std::cerr << setprecision(7) << fixed << x << " ";
    }
    std::cerr << "\n";
    std::cerr << "Derivative is: " << PrintPolyn(N - 1, deriv) << "\n";
#endif

#define TREAT_SADDLES 0

    vector <long double> nonSaddles;
    nonSaddles.push_back(-inf);

    for(auto x : derivSols)  {
    #if TREAT_SADDLES
        if(evaluate(x + lessSmall, N - 1, deriv) * evaluate(x - lessSmall, N - 1, deriv) > 0)
            continue;
    #endif
        nonSaddles.push_back(x);
    }

    nonSaddles.push_back(inf);


    vector <long double> ans;
    for(int i = 1;i < nonSaddles.size();i++)  {
        long double frst = nonSaddles[i - 1];
        long double scnd = nonSaddles[i];
        long double csgn;
        if(abs(frst - scnd) < small)  {
            if(abs( evaluate(frst, N, a) ) < lessSmall)  {
                ans.push_back(frst);
            }
            continue;
        }
        if(evaluate(frst, N, a) > evaluate(scnd, N, a))
            csgn = -1;
        else
            csgn = 1;
        if((csgn * evaluate(frst, N, a) <= 0 && csgn * evaluate(scnd, N, a) >= 0))  {
            long double r = frst - small;
            long double pas = (long double) (1LL << 30);
            while(pas >= small)  {
                if(frst <= r + pas && r + pas <= scnd)  {
                    if(csgn * evaluate(r + pas, N, a) <= 0)
                        r += pas;
                }
                pas /= 2.0;
            }
            if(abs(r) < small * 10.0)
                r = 0;
            ans.push_back(r);
        }
    }
    if(ans.size() == 0)  {
        return ans;
    }

    vector <long double> newAux = a;

    for(auto sol : ans)
        newAux = division(newAux.size() - 1, newAux, sol);
    newAux = solve(newAux.size() - 1, newAux);
    for(auto sol : newAux)  {
        ans.push_back(sol);
    }
    sort(ans.begin(), ans.end());
    return ans;
}

#define EASY_IO 0
int main()  {
    #if EASY_IO
    freopen("1503.in", "r", stdin);
    freopen("1503.out", "w", stdout);
    #endif
    cin >> N;
    a.resize(N + 1);
    for(int i = 0;i <= N;i++)  {
        cin >> a[i];
    }
    vector <long double> sol = solve(N, a);
    for(auto x : sol)  {
        std::cout << setprecision(8) << fixed << x << "\n";
    }
    return 0;
}