//Straightforward implementation of the idea from the editorial
#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 1e5 + 10;

int N, M;
vector<vector<int>> tree(MAXN);
int down[MAXN], up[MAXN];
vector<int> pref[MAXN]; // pref[i][k] -> product of the first K children node I
vector<int> suff[MAXN]; // suff[i][k] -> product of the last K children node I

void dfs2(int node, int par)
{
    vector<int> children;
    
    for (const int& to : tree[node]) if (to != par) children.push_back(to);

    for (int j = 0; j < children.size(); ++j)
    {
        int to = children[j];
        
        long long left  = (j ? pref[node][j-1] : 1);
        long long right = (j+  1 < children.size() ? suff[node][j + 1] : 1);
        
        up[to] = ((up[node] * left % M) * right + 1) % M;   
        
        dfs2(to, node);
    }

}

void dfs1(int node, int par)
{
    bool isLeaf = true;

    down[node] = 1;

    for(const int& to : tree[node])
    {
        if(to == par) continue;
        
        isLeaf = false;

        dfs1(to, node);

        down[node] *= down[to];
        down[node] %= M;
    }

    down[node]++;
    down[node] %= M;

    vector<int> children;

    for(const int& to : tree[node])
    {
        if(to == par) continue;
        children.push_back(to);
    }

    int m = children.size();

    if(m == 0) return;

    pref[node].assign(m, 1);
    suff[node].assign(m, 1);

    pref[node][0] = down[children[0]];
    pref[node][0] %= M; 
    for(int i = 1 ; i < m ; ++i)
    {

        pref[node][i] = pref[node][i - 1] * down[children[i]];
        pref[node][i] %= M; 
    }

    suff[node][m - 1] = down[children[m - 1]];
    suff[node][m - 1] %= M; 
    for(int i = m - 2 ; i >= 0 ; --i)
    {
        suff[node][i] = suff[node][i + 1] * down[children[i]];
        suff[node][i] %= M; 
    }
}

void solve()
{
    cin >> N >> M;

    for(int i = 1 ; i <= N - 1 ; ++i)
    {
        int a, b; cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    dfs1(1, 0);
    
    up[1] = 1;
    dfs2(1, 0);

    for(int i = 1 ; i <= N ; ++i)
    {
        long long a = (down[i] - 1) % M;
        
        if (a < 0) a += M;
        
        cout << (a * (up[i] % M)) % M << ' ';
    }

    cout << "\n";
}

void fastIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

signed main()
{
    fastIO();
    solve();
}