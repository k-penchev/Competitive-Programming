#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 2 * 1e5 + 10;
const int MAXLOG = 20 + 1;

int n, q;
vector<vector<pair<int, int>>> tree(MAXN);
int depth[MAXN], dist[MAXN], up[MAXN][MAXLOG];

void dfs(int node, int par, int currDepth, int currDist)
{
    dist[node] = currDist;
    depth[node] = currDepth;
    up[node][0] = par;

    for(int i = 1 ; i < MAXLOG ; ++i)
    {
        int prev = up[node][i - 1];
        up[node][i] = up[prev][i - 1];
    }

    for(const auto& [to, w] : tree[node])
    {
        if(to == par) continue;
        dfs(to, node, currDepth + 1, currDist + w);
    }
}

int find_lca(int a, int b)
{
    if(depth[a] < depth[b]) swap(a, b);

    int k = depth[a] - depth[b];

    for(int i = 0 ; i < MAXLOG ; ++i)
    {
        if(k & (1 << i))
        {
            a = up[a][i];
        }
    }

    if(a == b)
    {
        return a;
    }

    for(int i = MAXLOG - 1 ; i >= 0 ; --i)
    {
        if(up[a][i] != 0 && up[b][i] != 0 && (up[a][i] != up[b][i]))
        {
            a = up[a][i];
            b = up[b][i];
        }
    }

    return up[a][0];
}

int query(int a, int b)
{
    int lca = find_lca(a, b);

    return dist[a] + dist[b] - 2 * dist[lca];
}

void solve()
{
    cin >> n >> q;

    for(int i = 1 ; i <= n - 1 ; ++i)
    {
        int a, b, w; cin >> a >> b >> w;
        tree[a].push_back({b, w});
        tree[b].push_back({a, w});
    }

    dfs(1, 0, 0, 0);

    for(int qq = 1 ; qq <= q ; ++qq)
    {
        int a, b; cin >> a >> b;
        cout << query(a, b) << "\n";
    }
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