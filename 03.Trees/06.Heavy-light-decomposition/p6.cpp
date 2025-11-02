#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 1e5 + 10;

int n, m;
vector<vector<int>> tree(MAXN);

namespace Fenwick
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

    void update(int l, int r, int val)
    {
        update(l, +val);
        update(r + 1, -val);
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

        int h_ch = -1, h_ch_siz = -1;

        for(const int& child : tree[node])
        {
            if(child == par) continue;

            if(siz[child] > h_ch_siz)
            {
                h_ch_siz = siz[child];
                h_ch = child;
            }
        }

        if(h_ch == -1) return;
        decompose(h_ch, node, head);

        for(const int& child : tree[node])
        {
            if(child == par || child == h_ch) continue;
            decompose(child, node, child);
        }
    }

    void build()
    {
        dfs(1, 0, 0);
        
        depth[0] = top[0] = 0;

        decompose(1, 0, 1);

        Fenwick::set();
    }

    void update(int a, int b)
    {
        while(top[a] != top[b])
        {
            if(depth[top[a]] < depth[top[b]]) swap(a, b);

            Fenwick::update(id[top[a]], id[a], +1);

            a = parent[top[a]];
        }

        if(depth[a] > depth[b]) swap(a, b);

        Fenwick::update(id[a] + 1, id[b], +1);
    }

    int query(int a, int b)
    {
        if(depth[a] < depth[b]) swap(a, b);

        return Fenwick::query(id[a]);
    }
};

void solve()
{
    cin >> n >> m;

    for(int i = 1 ; i <= n - 1 ; ++i)
    {
        int a, b; cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    HLD::build();

    for(int i = 1 ; i <= m ; ++i)
    {
        char qType;
        int x, y;

        cin >> qType >> x >> y;

        if(qType == 'P')
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

signed main()
{
    fastIO();
    solve();
}