#include <iostream>
#include <algorithm>
#include <vector>

#define int long long

const int MAXN = 100000 + 10;
const int INF = 1e9 + 10;

int n, q;
struct SegmentTree
{
    struct Node
    {
        int sum;
        int max;

        Node()
        {
            sum = 0;
            max = INF;
        }

        void set(int x)
        {
            sum = x;
            max = x;
        }

        friend Node operator + (const Node &left, const Node& right)
        {
            Node res;
            res.sum = left.sum + right.sum;
            res.max = std::max(left.max, right.max);
            return res;
        }
    };

    Node tree[4 * MAXN];

    void build(int node, int l, int r, int arr[])
    {
        if(l == r)
        {
            tree[node].set(arr[l]);
            return;
        }

        int mid = l + r >> 1;
        build(2*node, l, mid, arr);
        build(2*node + 1, mid + 1, r, arr);
        tree[node] = tree[2*node] + tree[2*node + 1];
    }

    void update(int node, int l, int r, int queryL, int queryR, int modulo)
    {
        if(tree[node].max < modulo)
        {
            return;
        }

        if(queryL > r || queryR < l)
        {
            return;
        }

        if(l == r)
        {
            tree[node].set(tree[node].sum % modulo);
            return;
        }

        int mid = l + r >> 1;
        update(2*node, l, mid, queryL, queryR, modulo);
        update(2*node + 1, mid + 1, r, queryL, queryR, modulo);
        tree[node] = tree[2*node] + tree[2*node + 1];
    }

    void set(int node, int l, int r, int queryPos, int queryVal)
    {
        if(l == r)
        {
            tree[node].set(queryVal);
            return;
        }

        int mid = l + r >> 1;
        if(queryPos <= mid) set(2*node, l, mid, queryPos, queryVal);
        else set(2*node + 1, mid + 1, r, queryPos, queryVal);
        tree[node] = tree[2*node] + tree[2*node + 1];
    }

    int query(int node, int l, int r, int queryL, int queryR)
    {
        if(queryL <= l && r <= queryR)
        {
            return tree[node].sum;
        }

        int res = 0;
        int mid = l + r >> 1;
        if(queryL <= mid) res += query(2*node, l, mid, queryL, queryR);
        if(mid + 1 <= queryR) res += query(2*node + 1, mid + 1, r, queryL, queryR);
        return res; 
    }
};

int a[MAXN];
SegmentTree tree;

void solve()
{
    std::cin >> n >> q;
    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> a[i];
    }

    tree.build(1, 1, n, a);
    for(int i = 1 ; i <= q ; ++i)
    {
        int type, l, r, x;
        std::cin >> type;

        if(type == 1)
        {
            std::cin >> l >> r;
            std::cout << tree.query(1, 1, n, l, r) << "\n";
        }
        else if(type == 2)
        {
            std::cin >> l >> r >> x;
            tree.update(1, 1, n, l, r, x);
        }
        else
        {
            std::cin >> l >> x;
            tree.set(1, 1, n, l, x); 
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