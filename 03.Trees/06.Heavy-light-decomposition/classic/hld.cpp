#include <iostream>
#include <algorithm>
#include <vector>

typedef long long llong;
const int MAXN = 200000 + 10;
const int INF = 1e9 + 10;
const int MAXLOG = 20;

int n, q;
namespace SegmentTree
{
    int tree[4 * MAXN];

    void build(int node, int l, int r, int v[])
    {
        if(l == r)
        {
            tree[node] = v[l];
            return;
        }

        int mid = l + r >> 1;
        build(2*node, l, mid, v);
        build(2*node + 1, mid + 1, r, v);
        tree[node] = std::max(tree[2*node], tree[2*node + 1]);
    }

    void update(int node, int l, int r, int queryPos, int queryVal)
    {
        if(l == r)
        {
            tree[node] = queryVal;
            return;
        }

        int mid = l + r >> 1;
        if(queryPos <= mid) update(2*node, l, mid, queryPos, queryVal);
        else update(2*node + 1, mid + 1, r, queryPos, queryVal);
        tree[node] = std::max(tree[2*node], tree[2*node + 1]);
    }

    int query(int node, int l, int r, int queryL, int queryR)
    {
        if(queryL <= l && r <= queryR)
        {
            return tree[node];
        }

        int res = -INF;
        int mid = l + r >> 1;
        if(queryL <= mid) res = std::max(res, query(2*node, l, mid, queryL, queryR));
        if(mid + 1 <= queryR) res = std::max(res, query(2*node + 1, mid + 1, r, queryL, queryR));
        return res;
    }
};

int label[MAXN];
std::vector<int> tree[MAXN];

namespace HLD
{
    int cnt;
    int id[MAXN];
    int top[MAXN];
    int depth[MAXN];
    int parent[MAXN];
    int size[MAXN];
    int flat[MAXN];

    void dfs(int node, int par, int dp)
    {
        size[node] = 1;
        depth[node] = dp;
        parent[node] = par;

        for(const int &to : tree[node])
        {
            if(to == par)
            {
                continue;
            }

            dfs(to, node, dp + 1);
            size[node] += size[to];
        }
    }

    void decompose(int node, int par, int head)
    {
        id[node] = ++cnt;
        top[node] = head;

        int heavy = -1;
        int heavysize = -1;
        for(const int &to : tree[node])
        {
            if(to == par)
            {
                continue;
            }

            if(size[to] > heavysize)
            {
                heavy = to;
                heavysize = size[to];
            }
        }

        if(heavy == -1) return;
        decompose(heavy, node, head);

        for(const int &to : tree[node])
        {
            if(to == par || to == heavy)
            {
                continue;
            }

            decompose(to, node, to);
        }
    }

    void build()
    {
        dfs(1, 0, 0);
        decompose(1, 0, 1);

        for(int i = 1 ; i <= n ; ++i)
        {
            flat[id[i]] = label[i];
        }

        SegmentTree::build(1, 1, n, flat);
    }

    void update(int node, int val)
    {
        SegmentTree::update(1, 1, n, id[node], val);
    }

    int query(int u, int v)
    {
        int res = -INF;
        while(top[u] != top[v])
        {
            if(depth[top[u]] < depth[top[v]]) std::swap(u, v);
            res = std::max(res, SegmentTree::query(1, 1, n, id[top[u]], id[u]));
            u = parent[top[u]];
        }

        if(depth[u] > depth[v]) std::swap(u, v);
        res = std::max(res, SegmentTree::query(1, 1, n, id[u], id[v]));
        return res;
    }
};

void solve()
{
    std::cin >> n >> q;
    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> label[i];
    }

    for(int i = 1 ; i <= n - 1 ; ++i)
    {
        int u, v; std::cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }   

    HLD::build();
    for(int i = 1 ; i <= q ; ++i)
    {
        int type, x, y;
        std::cin >> type >> x >> y;

        if(type == 1)
        {
            HLD::update(x, y);
        }
        else
        {
            std::cout << HLD::query(x, y) << " ";
        }
    }

    std::cout << "\n";
}

void fastIO()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
}

int main()
{
    fastIO();
    solve();
    return 0;
}