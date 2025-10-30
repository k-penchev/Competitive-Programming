//Finding subsegments with the maximal sum
#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 1e5 + 10;
const int INF = 1e9 + 10;

int n;
int a[MAXN];

struct SegmentTree
{
    struct Node
    {
        int sum;
        int maxSum;
        int prefix;
        int suffix;

        Node()
        {
            sum = 0;
            maxSum = -INF;
            prefix = suffix = -INF;
        }

        Node(int s)
        {
            sum = s;
            maxSum = s;
            prefix = suffix = s;
        }
    };

    Node tree[4 * MAXN];

    Node combine(const Node& x, const Node& y)
    {
        Node res;

        res.sum = x.sum + y.sum;
        res.prefix = std::max(x.prefix, x.sum + y.prefix);
        res.suffix = std::max(y.suffix, y.sum + x.suffix);
        res.maxSum = std::max(std::max(x.maxSum, y.maxSum), x.suffix + y.prefix);

        return res;
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

    Node query(int idx, int low, int high, int queryL, int queryR)
    {
        if(queryL > high || queryR < low)
        {
            return Node();
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

    void update(int pos, int val)
    {
        update(1, 1, n, pos, val);
    }

    int query(int l, int r)
    {
        return query(1, 1, n, l, r).maxSum;
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

    std::cout << tree.query(1, 5) << "\n";
    tree.update(2, -100);
    std::cout << tree.query(1, 5) << "\n";
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