#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;
const int MAXLOG = 16 + 1;

int n, q;
vector<vector<int>> tree(MAXN);
int in[MAXN], out[MAXN], timer = 0;
int depth[MAXN], siz[MAXN], up[MAXN][MAXLOG];

void dfs(int node, int par, int currDepth)
{
    in[node] = ++timer;
    siz[node] = 1;
    depth[node] = currDepth;
    up[node][0] = par;

    for(int i = 1 ; i < MAXLOG ; ++i)
    {
        int prv = up[node][i - 1];
        up[node][i] = up[prv][i - 1];
    }

    for(const int& child : tree[node])
    {
        if(child == par) continue;

        dfs(child, node, currDepth + 1);

        siz[node] += siz[child];
    }

    out[node] = timer;
}

int lift(int a, int k)
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

bool is_ancestor(int a, int b)
{
    return (in[a] <= in[b] && out[a] >= out[b]);
}

int lca(int a, int b)
{
    if(is_ancestor(a, b)) return a;
    if(is_ancestor(b, a)) return b;

    for(int i = MAXLOG - 1 ; i >= 0 ; --i)
    {
        int nxt = up[a][i];
        
        if(nxt != 0 && !is_ancestor(nxt, b))
        {
            a = nxt;
        }
    }

    return up[a][0];
}

int query(int a, int b, int c)
{
    int par = lca(a, b);

    if(par == c)
    {
        return (n - siz[lift(a, depth[a] - depth[par] - 1)]
                  - siz[lift(b, depth[b] - depth[par] - 1)]);
    }

    if(depth[c] < depth[par]) return 0;
    if(depth[c] > max(depth[a], depth[b])) return 0;

    int low = -1;

    for(int x : {a, b})
    {
        int candidate = lift(x, depth[x] - depth[c]);
        
        if(candidate == c)
        {
            low = lift(x, depth[x] - depth[c] - 1);
        }
    }

    if(low == -1) return 0;

    return siz[c] - siz[low];
}

void solve()
{
    cin >> n >> q;

    for(int i = 1 ; i <= n - 1 ; ++i)
    {
        int a, b; cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }
    
    dfs(1, 0, 0);

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