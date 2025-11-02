#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 2 * 1e5 + 10;
const int MAXM = 2 * 1e5 + 10;
const int MAXLOG = 20 + 1;

int n, m;

struct Edge
{
    int from;
    int to;
    int w;
    int idx;
};

Edge edge[MAXM];
bool selectedInMst[MAXM]; 
int ans[MAXM]; 

vector<vector<pair<int, int>>> tree(MAXN);
int lift[MAXN][MAXLOG], liftEdge[MAXN][MAXLOG];
int depth[MAXN], in[MAXN], out[MAXN], timer = 0;

struct DSU
{
    int par[MAXN], sz[MAXN];

    void set()
    {
        fill(sz + 1, sz + n + 1, 1);

        for(int i = 1 ; i <= n ; ++i)
        {
            par[i] = i;
        }
    }

    int find(int x)
    {
        if(par[x] == x) return x;
        return par[x] = find(par[x]);
    }

    void unite(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);

        if(rootX != rootY)
        {
            if(sz[rootX] < sz[rootY]) swap(rootX, rootY);

            par[rootY] = rootX;
            sz[rootX] += sz[rootY];
        }
    }

    bool are_connected(int x, int y)
    {
        return find(x) == find(y);
    }
};

DSU dsu;
int mstWeight;

void build_mst()
{
    dsu.set();

    sort(edge + 1, edge + m + 1, [&] (const Edge& a, const Edge& b)
    {
        return a.w < b.w;
    });

    int cnt = 0;

    for(int i = 1 ; i <= m ; ++i)
    {
        if(cnt == n - 1) break;

        auto& [from, to, w, idx] = edge[i];

        if(!dsu.are_connected(from, to))
        {
            selectedInMst[edge[i].idx] = true;
            ++cnt; mstWeight += w;
            
            tree[from].push_back({to, w});
            tree[to].push_back({from , w});

            dsu.unite(from, to);
        }
    }

    for(int i = 1 ; i <= m ; ++i)
    {
        if(selectedInMst[edge[i].idx])
        {
            ans[edge[i].idx] = mstWeight;
        }
    }
}

void dfs(int node, int par, int currDepth, int currWeight)
{
    in[node] = ++timer;
    depth[node] = currDepth;
    lift[node][0] = par;
    liftEdge[node][0] = currWeight;

    for(int i = 1 ; i < MAXLOG ; ++i)
    {
        int prev = lift[node][i - 1];

        lift[node][i] = lift[prev][i - 1];
        liftEdge[node][i] = max(liftEdge[node][i - 1], liftEdge[prev][i - 1]);
    }

    for(const auto& [child, w] : tree[node])
    {
        if(child == par) continue;
        dfs(child, node, currDepth + 1, w);
    }

    out[node] = timer;
}

int lift_path(int node, int k)
{
    int maxEdge = 0;

    for(int i = 0 ; i < MAXLOG ; ++i)
    {
        if(k & (1 << i))
        {
            maxEdge = max(maxEdge, liftEdge[node][i]);
            node = lift[node][i];
        }
    }

    return maxEdge;
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
        int up = lift[a][i];

        if(up != 0 && !is_ancestor(up, b))
        {
            a = up;
        }
    }

    return lift[a][0];
}

int dist(int a, int b)
{
    return depth[a] + depth[b] - 2 * depth[lca(a, b)];
}

int query(int a, int b, int w)
{
    int par = lca(a, b);

    int d1 = dist(a, par);
    int d2 = dist(b, par);

    return (mstWeight - max(lift_path(a, d1), lift_path(b, d2)) + w);
}

void solve()
{
    cin >> n >> m;

    for(int i = 1 ; i <= m ; ++i)
    {
        int a, b, w; cin >> a >> b >> w;
        edge[i] = {a, b, w, i};
    }

    build_mst();
    dfs(1, 0, 0, 0);

    for(int i = 1 ; i <= m ; ++i)
    {
        auto& [from, to, w, idx] = edge[i];

        if(!selectedInMst[idx])
        {
            ans[idx] = query(from, to, w);
        }
    }

    for(int i = 1 ; i <= m ; ++i)
    {
        cout << ans[i] << "\n";
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
    
    return 0;
}