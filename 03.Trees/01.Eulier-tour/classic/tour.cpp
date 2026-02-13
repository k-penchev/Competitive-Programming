#include <iostream>
#include <algorithm>
#include <vector>

#define int long long

const int MAXN = 200000 + 10;
const int INF = 1e9 + 10;

int n, q;
struct SegmentTree
{
    int tree[4 * MAXN];

    void build(int node, int l, int r, int arr[])
    {
        if(l == r)
        {
            tree[node] = arr[l];
            return;
        }

        int mid = l + r >> 1;
        build(2*node, l, mid, arr);
        build(2*node + 1, mid + 1, r, arr);
        tree[node] = tree[2*node] + tree[2*node + 1];
    }

    void update(int node, int l, int r, int pos, int val)
    {
        if(l == r)
        {
            tree[node] = val;
            return;
        }

        int mid = l + r >> 1;
        if(pos <= mid) update(2*node, l, mid, pos, val);
        else update(2*node + 1, mid + 1, r, pos, val);
        tree[node] = tree[2*node] + tree[2*node + 1];
    }

    int query(int node, int l, int r, int queryL, int queryR)
    {
        if(queryL <= l && r <= queryR)
        {
            return tree[node];
        }

        int res = 0;
        int mid = l + r >> 1;
        if(queryL <= mid) res += query(2*node, l, mid, queryL, queryR);
        if(mid + 1 <= queryR) res += query(2*node + 1, mid + 1, r, queryL, queryR);
        return res;
    }

    void build(int arr[])
    {
        build(1, 1, n, arr);
    }

    void update(int pos, int val)
    {
        update(1, 1, n, pos, val);
    }

    int query(int l, int r)
    {
        return query(1, 1, n, l, r);
    }
};

int timer;
int a[MAXN];
int in[MAXN];
int out[MAXN];
int flat[MAXN];
SegmentTree tree;
std::vector<int> g[MAXN];

void euler(int node, int par)
{
    in[node] = ++timer;
    for(const int &to : g[node])
    {
        if(to == par) continue;
        euler(to, node);
    }

    out[node] = timer;
}

void solve()
{
    std::cin >> n >> q;
    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> a[i];
    }

    for(int i = 1 ; i <= n - 1 ; ++i)
    {
        int u, v;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    euler(1, 0);
    for(int i = 1 ; i <= n ; ++i)
    {
        flat[in[i]] = a[i];
    }

    tree.build(flat);
    for(int i = 1 ; i <= q ; ++i)
    {
        int type, x, y;
        std::cin >> type;

        if(type == 1)
        {
            std::cin >> x >> y;
            tree.update(in[x], y);
        }
        else
        {
            std::cin >> x;
            std::cout << tree.query(in[x], out[x]) << "\n";
        }
    }
}

void fastIO()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
}

signed main()
{
    fastIO();
    solve();
    return 0;
}