#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 2 * 1e5 + 10;
const int MAXLOG = 21;

int n, q;
vector<vector<int>> tree(MAXN);
int U[MAXN], V[MAXN], W[MAXN];
int val[MAXN], edge[MAXN];
int in[MAXN], out[MAXN], depth[MAXN], par[MAXN][MAXLOG], timer = 0;

struct Fenwick
{
    int bit[MAXN];

    void set()
    {
        fill(bit, bit + MAXN, 0);
    }

    void update(int idx, int val)
    {
        for(; idx <= n ; idx += (idx & (-idx)))
        {
            bit[idx] += val;
        }
    }

    void range_update(int l, int r, int k)
    {
        update(l, k);
        update(r + 1, -k);
    }

    int query(int idx)
    {
        int s = 0;

        for(; idx >= 1 ; idx -= (idx & (-idx)))
        {
            s += bit[idx];
        }

        return s;
    }

    int range_query(int l, int r)
    {
        return query(r) - query(l - 1);
    }
};

Fenwick fen;

void euler(int node, int parent, int currentDepth)
{
    in[node] = ++timer;

    depth[node] = currentDepth;
    par[node][0] = parent;

    for(int i = 1 ; i <= 20 ; ++i)
    {
        par[node][i] = par[par[node][i - 1]][i - 1];
    }

    for(int& to : tree[node])
    {
        if(to == parent) continue;
        euler(to, node, currentDepth + 1);
    }

    out[node] = timer;
}

bool is_ancestor(int x, int y)
{
    return (in[x] <= in[y] && out[x] >= out[y]);
}

int findLCA(int x, int y)
{
    if(is_ancestor(x, y)) return x;

    for(int i = 20 ; i >= 0 ; --i)
    {
        if(par[x][i] > 0 && !is_ancestor(par[x][i], y))
        {
            x = par[x][i];
        }
    };

    return par[x][0];
}

int distance(int x, int y)
{
    if(depth[x] < depth[y]) swap(x, y);

    int lca = findLCA(x, y);

    int toX = fen.query(in[x]);
    int toY = fen.query(in[y]);
    int toLCA = fen.query(in[lca]);

    return toX + toY - 2 * toLCA;
}

void solve()
{
    cin >> n;

    for(int i = 1 ; i <= n - 1 ; ++i)
    {
        int a, b, w; cin >> a >> b >> w;

        tree[a].push_back(b);
        tree[b].push_back(a);

        U[i] = a, V[i] = b, W[i] = w;
        edge[i] = b;
    }

    euler(1, 0, 0);
    fen.set();

    for(int i = 1 ; i <= n - 1 ; ++i)
    {
        edge[i] = (par[U[i]][0] == V[i] ? U[i] : V[i]); 
        val[edge[i]] = W[i];
        int child = edge[i];
        fen.range_update(in[child], out[child], val[child]);
    }

    cin >> q;

    for(int qq = 1 ; qq <= q ; ++qq)
    {
        int qType, x, y; cin >> qType >> x >> y;

        if(qType == 1)
        {
            int child = edge[x];
            int delta = y - val[child];
            val[child] = delta;

            fen.range_update(in[child], out[child], delta);
        }
        else
        {
            cout << distance(x, y) << "\n";
        }
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