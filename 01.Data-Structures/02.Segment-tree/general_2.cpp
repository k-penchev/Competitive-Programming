//general segment tree with lazy propagation
//range query (sum)
//range update (add)
#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 1e5 + 10;

int n;
int a[MAXN];

struct SegmentTree
{
    struct Node
    {
        int val;
        int lazy;

        Node()
        {
            val = 0;
            lazy = 0;
        }

        Node(int x)
        {
            val = x;
            lazy = 0;
        }
    };

    Node tree[4 * MAXN];

    Node combine(const Node& x, const Node& y)
    {
        return Node(x.val + y.val);
    }

    void build(int idx, int low, int high, int * arr)
    {
        if(low == high)
        {
            tree[idx] = Node(arr[low]);
            return; 
        }

        int mid = (low + high) / 2;

        build(2 * idx, low, mid, arr);
        build(2 * idx + 1, mid + 1, high, arr);

        tree[idx] = combine(tree[2 * idx], tree[2 * idx + 1]);
    }

    void propagate(int idx, int low, int high)
    {
        if(tree[idx].lazy)
        {
            tree[idx].val += (high - low + 1) * tree[idx].lazy;

            if(low != high)
            {
                tree[2 * idx].lazy += tree[idx].lazy;
                tree[2 * idx + 1].lazy += tree[idx].lazy;
            }

            tree[idx].lazy = 0;
        }
    }

    void update(int idx, int low, int high, int queryL, int queryR, int val)
    {
        propagate(idx, low, high);

        if(queryL > high || queryR < low)
        {
            return;
        }
        else if(queryL <= low && high <= queryR)
        {
            tree[idx].lazy += val;
            propagate(idx, low, high);
            return;
        }

        int mid = (low + high) / 2;

        update(2 * idx, low, mid, queryL, queryR, val);
        update(2 * idx + 1, mid + 1, high, queryL, queryR, val);

        tree[idx] = combine(tree[2 * idx], tree[2 * idx + 1]);
    }

    Node query(int idx, int low, int high, int queryL, int queryR)
    {
        propagate(idx, low, high);

        if(queryL > high || queryR < low)
        {
            return Node(0);
        }
        else if(queryL <= low && high <= queryR)
        {
            return tree[idx];
        }

        int mid = (low + high) / 2;

        return combine(query(2 * idx, low, mid, queryL, queryR),
                query(2 * idx + 1, mid + 1, high, queryL, queryR));
    }

    void build(int * arr)
    {
        build(1, 1, n, arr);
    }

    void update(int l, int r, int val)
    {
        update(1, 1, n, l, r, val);
    }

    int query(int l, int r)
    {
        return query(1, 1, n, l, r).val;
    }
};

SegmentTree tree;

void solve()
{
    std::cin >> n;

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> a[i];
    }

    tree.build(a);

    std::cout << tree.query(1, 4) << "\n";
    tree.update(1, 2, +1);
    std::cout << tree.query(1, 4) << "\n";
    tree.update(1, 3, +1);
    std::cout << tree.query(1, 4) << "\n";
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
}