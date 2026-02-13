#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 100000 + 10;
const int INF = 1e9 + 10;
const int MAXLOG = 20;

int n, q;
struct SegmentTree
{
    struct Node
    {
        int max;
        int lazy; 
    
        Node()
        {
            max = 0;
            lazy = 0;
        }
    };

    Node tree[4 * MAXN];

    void push(int node, int l, int r)
    {
        if(!tree[node].lazy)
        {
            return;
        }

        tree[node].max += tree[node].lazy;

        if(l != r)
        {
            tree[2*node].lazy += tree[node].lazy;
            tree[2*node + 1].lazy += tree[node].lazy;
        }

        tree[node].lazy = 0;
    }

    void update(int node, int l, int r, int queryL, int queryR, int queryVal)
    {
        push(node, l, r);
        if(r < queryL || l > queryR)
        {
            return;
        }

        if(queryL <= l && r <= queryR)
        {
            tree[node].lazy += queryVal;
            push(node, l, r);
            return;
        }

        int mid = l + r >> 1;
        update(2*node, l, mid, queryL, queryR, queryVal);
        update(2*node + 1, mid + 1, r, queryL, queryR, queryVal);
        tree[node].max = std::max(tree[2*node].max, tree[2*node + 1].max);
    }

    int query(int node, int l, int r, int queryL, int queryR)
    {
        push(node, l, r);
        if(r < queryL || l > queryR)
        {
            return -INF;
        }

        if(queryL <= l && r <= queryR)
        {
            return tree[node].max;
        }

        int res = -INF;
        int mid = l + r >> 1;
        res = std::max(res, query(2*node, l, mid, queryL, queryR));
        res = std::max(res, query(2*node + 1, mid + 1, r, queryL, queryR));
        return res;
    }

    void update(int l, int r, int val)
    {
        update(1, 1, n, l, r, val);
    }

    int query(int l, int r)
    {
        return query(1, 1, n, l, r);
    }
};

SegmentTree tree;
std::vector<int> g[MAXN];

namespace HLD
{
    int cnt = 1;
    int id[MAXN];
    int top[MAXN];
    int size[MAXN];
    int depth[MAXN];
    int parent[MAXN];
    
    void dfs(int node, int par, int dep)
    {
        size[node] = 1;
        depth[node] = dep;
        parent[node] = par;

        for(const int &to : g[node])
        {
            if(to == par) continue;
            dfs(to, node, dep + 1);
            size[node] += size[to];
        }
    }

    void decompose(int node, int par, int head)
    {
        id[node] = cnt++;
        top[node] = head;

        int heavy = -1;
        int heavySize = -1;
        for(const int &to : g[node])
        {
            if(to == par) continue;

            if(size[to] > heavySize)
            {
                heavy = to;
                heavySize = size[to];
            }
        }

        if(heavy == -1) return;
        decompose(heavy, node, head);

        for(const int &to : g[node])
        {
            if(to == par || to == heavy) continue;
            decompose(to, node, to);
        }
    }

    void build()
    {
        dfs(1, 0, 0);
        decompose(1, 0, 1);
    }

    void update(int node, int val)
    {
        tree.update(id[node], id[node] + size[node] - 1, val);
    }

    int query(int a, int b)
    {
        int res = -INF;

        while(top[a] != top[b])
        {
            if(depth[top[a]] < depth[top[b]]) std::swap(a, b);
            res = std::max(res, tree.query(id[top[a]], id[a]));
            a = parent[top[a]];
        }

        if(depth[a] > depth[b]) std::swap(a, b);
        res = std::max(res, tree.query(id[a], id[b]));
        return res == -INF ? 0 : res;
    }
};

void solve()
{
    std::cin >> n;
    for(int i = 1 ; i <= n - 1 ; ++i)
    {
        int a, b;
        std::cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    HLD::build();
    std::cin >> q;
    for(int i = 1 ; i <= q ; ++i)
    {
        std::string type; int x, y;
        std::cin >> type >> x >> y;

        if(type == "add")
        {
            HLD::update(x, y);
        }
        else
        {
            std::cout << HLD::query(x, y) << "\n";
        }
    }
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