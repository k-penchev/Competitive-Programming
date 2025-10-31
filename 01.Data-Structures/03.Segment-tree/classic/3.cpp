//Searching for an array prefix with a given amount
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
        int sum;

        Node()
        {
            sum = 0;
        }

        Node(int x)
        {
            sum = x;
        }
    };

    Node tree[4 * MAXN];

    Node combine(const Node& x, const Node& y)
    {
        return Node(x.sum + y.sum);
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

    void update(int idx, int low, int high, int pos, int val)
    {
        if(low == high)
        {
            tree[idx] = Node(val);
            return;
        }

        int mid = (low + high) / 2;

        if(pos <= mid)
        {
            update(2 * idx, low, mid, pos, val);
        }
        else
        {
            update(2 * idx + 1, mid + 1, high, pos, val);
        }

        tree[idx] = combine(tree[2 * idx], tree[2 * idx + 1]);
    }

    int query(int idx, int low, int high, int x)
    {
        if(x > tree[idx].sum)
        {
            return -1;
        }

        if(low == high)
        {
            return low;
        }

        int mid = (low + high) / 2;

        if(tree[2 * idx].sum >= x)
        {
            return query(2 * idx, low, mid, x);
        }
        else
        {
            return query(2 * idx + 1, mid + 1, high, x - tree[2 * idx].sum);
        }
    }

    void build(int * arr)
    {
        build(1, 1, n, arr);
    }

    void update(int pos, int val)
    {
        update(1, 1, n, pos, val);
    }

    int query(int x)
    {
        return query(1, 1, n, x);
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

    std::cout << tree.query(4) << " " << tree.query(5) << " " << tree.query(12) << "\n";
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