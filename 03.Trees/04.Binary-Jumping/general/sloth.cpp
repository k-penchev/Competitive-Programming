#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3 * 1e5 + 10;
const int MAXLOG = 20 + 1;

int n, q;
vector<vector<int>> tree(MAXN);
int depth[MAXN], up[MAXN][MAXLOG];

void dfs(int node, int par, int currDepth)
{
    depth[node] = currDepth;
    up[node][0] = par;

    for(int i = 1 ; i < MAXLOG ; ++i)
    {
        int prev = up[node][i - 1];
        up[node][i] = up[prev][i - 1];
    }

    for(const int& child : tree[node])
    {
        if(child == par) continue;

        dfs(child, node, currDepth + 1);
    }
}

int kth_ancestor(int a, int k)
{
    for(int i = 0 ; i < MAXLOG ; ++i)
    {
        if(k & (1 << i))
        {
            a = up[a][i];
        }
    }

    return a;
}

int lca(int a, int b)
{
    if(depth[a] < depth[b]) swap(a, b);

    a = kth_ancestor(a, depth[a] - depth[b]);

    if(a == b) return a;

    for(int i = MAXLOG - 1 ; i >= 0 ; --i)
    {
        if(up[a][i] != up[b][i])
        {
            a = up[a][i];
            b = up[b][i];
        }
    }

    return up[a][0];
}

int dist(int a, int b)
{
    return depth[a] + depth[b] - 2 * depth[lca(a, b)];
}

int query(int a, int b, int c)
{
    int par = lca(a, b);

    int dist1 = dist(a, par);
    int dist2 = dist(b, par);

    if(c <= dist1)
    {
        return kth_ancestor(a, c);
    }
    else if(c <= dist1 + dist2)
    {
        return kth_ancestor(b, dist2 - (c - dist1));
    }

    return b;
}

void solve()
{
    cin >> n;

    for(int i = 1 ; i <= n - 1 ; ++i)
    {
        int a, b; cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    dfs(1, 0, 0);

    cin >> q;

    for(int i = 1 ; i <= q ; ++i)
    {
        int a, b, c; cin >> a >> b >> c;
        cout << query(a, b, c) << "\n";
    }
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