#include <bits/stdc++.h>

using namespace std;

const int maxn = 32001;
const int maxm = 500001;

int N, M;
int points[maxn];

vector <int> v[maxn];
bool nonroots[maxn];

int root;

vector <int> euler;
vector <pair <int, int>> arbint;
bool viz[maxn];
int firsts[maxn];
int level[maxn];

void dfs(int node, int lvl)  {
    if(!viz[node])  {
        viz[node] = 1;
        firsts[node] = euler.size();
        level[node] = lvl;
    }
    euler.push_back(node);
    for(auto son : v[node])  {
        dfs(son, lvl + 1);
        euler.push_back(node);
    }
}

void buildArb(int node, int l, int r)  {
    if(l == r)  {
        arbint[node] = make_pair(level[euler[l]], euler[l]);
        return;
    }
    int mid = (l + r) / 2;
    buildArb(node * 2, l, mid);
    buildArb(node * 2 + 1, mid + 1, r);
    arbint[node] = min(arbint[node * 2], arbint[node * 2 + 1]);
}

pair <int, int> query(int node, int l, int r, int a, int b)  {
    if(r < a || l > b)
        return make_pair(1e9, 0);
    if(a <= l && r <= b)  {
        return arbint[node];
    }
    int mid = (l + r) / 2;
    return min(query(node * 2, l, mid, a, b), query(node * 2 + 1, mid + 1, r, a, b));
}

int main()  {
    freopen("concurs.in", "r", stdin);
    freopen("concurs.out", "w", stdout);
    cin >> N >> M;
    for(int i = 1;i <= N;i++)
        cin >> points[i];
    for(int i = 1;i < N;i++)  {
        int tata, fiu;
        cin >> tata >> fiu;
        v[tata].push_back(fiu);
        nonroots[fiu] = 1;
    }
    for(int i = 1;i <= N;i++)
        if(!nonroots[i])  {
            root = i;
            break;
        }
    euler.push_back(0);
    dfs(root, 0);
    arbint.resize(euler.size() * 4);
    fill(arbint.begin(), arbint.end(), make_pair(1e9, 0));
    buildArb(1, 1, euler.size() - 1);
    int maxi = 0, l = INT_MAX, r = INT_MAX;
    for(int i = 1;i <= M;i++)  {
        int a, b, aa, bb;
        cin >> a >> b;
        aa = a, bb = b;
        if(firsts[a] > firsts[b])
            swap(a, b);
        pair <int, int> lca = query(1, 1, euler.size() - 1, firsts[a], firsts[b]);
        a = aa, b = bb;
        if(points[lca.second] > maxi)  {
            maxi = points[lca.second];
            l = a;
            r = b;
        }else if(points[lca.second] == maxi)  {
            if(a < l)  {
                l = a;
                r = b;
            }else if(a == l && b < r)  {
                r = b;
            }
        }
    }
    cout << maxi << " " << l << " " << r;
    return 0;
}