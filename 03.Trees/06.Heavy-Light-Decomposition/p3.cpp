#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e3 + 10;

int n, m;
int val[MAXN];
vector<vector<int>> tree(MAXN);

namespace SegmentTree
{

};

namespace HLD
{
    int depth[MAXN], siz[MAXN], parent[MAXN];
    int top[MAXN], id[MAXN], counter = 1;

    void dfs(int node, int par, int currDepth)
    {
        depth[node] = currDepth;
    }
};

void solve()
{
    cin >> n >> m;

    for(int i = 1 ; i <= n ; ++i)
    {
        cin >> val[i];
    }

    for(int i = 1 ; i <= n - 1 ; ++i)
    {
        int a, b; cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    HLD::build();

    for(int i = 1 ; i <= m ; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;
        cout << HLD::query(a, b, c);
    }

    cout << "\n";
}

void fastIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

int main()
{
    fastIO();
    solve();
    
    return 0;
}