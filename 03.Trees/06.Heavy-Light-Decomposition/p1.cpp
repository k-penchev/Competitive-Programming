#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;

int n, q;
int val[MAXN];
vector<vector<int>> tree(MAXN);

namespace Fenwick
{
    int fen[MAXN];

    void set()
    {
        fill(fen + 1, fen + n + 1, 0);
    }

    void update(int idx, int val)
    {
        for(; idx <= n ; idx += (idx & (-idx)))
        {
            fen[idx] ^= val;
        }
    }

    int query(int idx)
    {
        int s = 0;
        
        for(; idx >= 1 ; idx -= (idx & (-idx)))
        {
            s ^= fen[idx];
        }

        return s;
    }

    int query(int l, int r)
    {
        return query(r) ^ query(l - 1);
    }
};

namespace HLD
{
    int depth[MAXN], siz[MAXN], parent[MAXN];
    int top[MAXN], id[MAXN], counter = 1;

    void dfs(int node, int par, int currDepth)
    {
        depth[node] = currDepth;
        parent[node] = par;
        siz[node] = 1;

        for(const int& child : tree[node])
        {
            if(child == par) continue;

            dfs(child, node, currDepth + 1);

            siz[node] += siz[child];
        }
    }

    void decompose(int node, int par, int head)
    {
        id[node] = counter++;
        top[node] = head;

        int heavy_child = -1, heavy_child_siz = -1;

        for(const int& child : tree[node])
        {
            if(child == par) continue;

            if(siz[child] > heavy_child_siz)
            {
                heavy_child_siz = siz[child];
                heavy_child = child;
            }
        }

        if(heavy_child == -1) return;
        decompose(heavy_child, node, head);

        for(const int& child : tree[node])
        {
            if(child == par || child == heavy_child) continue;
            decompose(child, node, child);
        }
    }

    void build()
    {
        dfs(1, 0, 0);

        top[0] = 0;
        depth[0] = -1;

        decompose(1, 0, 1);

        for(int i = 1 ; i <= n ; ++i)
        {
            Fenwick::update(id[i], val[i]);
        }
    }

    void update(int node, int newVal)
    {
        int delta = newVal ^ val[node];

        Fenwick::update(id[node], delta);

        val[node] ^= delta;
    }

    int query(int a, int b)
    {
        int ret = 0;

        while(top[a] != top[b])
        {
            if(depth[top[a]] < depth[top[b]]) swap(a, b);

            ret ^= Fenwick::query(id[top[a]], id[a]);

            a = parent[top[a]];
        }

        if(depth[a] > depth[b]) swap(a, b);

        ret ^= Fenwick::query(id[a], id[b]);

        return ret;
    }
};

void solve()
{
    freopen("cowland.in", "r", stdin);
    freopen("cowland.out", "w", stdout);

    cin >> n >> q;

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

    for(int i = 1 ; i <= q ; ++i)
    {
        int qType, x, y;
        cin >> qType >> x >> y;

        if(qType == 1)
        {
            HLD::update(x, y);
        }
        else
        {
            cout << HLD::query(x, y) << "\n";
        }
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