#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;

int n, m;
int val[MAXN];
vector<vector<int>> tree(MAXN);
set<int> st[MAXN];

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

        depth[0] = top[0] = 0;

        decompose(1, 0, 1);

        for(int i = 1 ; i <= n ; ++i)
        {
            st[val[i]].insert(id[i]);
        }
    }

    int get(int l, int r, int c)
    {
        auto it = st[c].lower_bound(l);

        return (it != st[c].end() && (*it) <= r ? 1 : 0);
    }

    int query(int a, int b, int c)
    {
        int res = 0;

        while(top[a] != top[b])
        {
            if(depth[top[a]] < depth[top[b]]) swap(a, b);

            res |= get(id[top[a]], id[a], c);

            a = parent[top[a]];
        }

        if(depth[a] > depth[b]) swap(a, b);

        res |= get(id[a], id[b], c);

        return res;
    }
};

void solve()
{
    freopen("milkvisits.in", "r", stdin);
    freopen("milkvisits.out", "w", stdout);

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