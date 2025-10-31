//general segment tree
//range query (sum)
//point update
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

        Node()
        {
            val = 0;
        }

        Node(int x)
        {
            val = x;
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

    void update(int idx, int low, int high, int pos, int newVal)
    {
        if(low == high)
        {
            tree[idx].val += newVal; //add 
            //tree[idx] = Node(newVal); //replace
            return;
        }

        int mid = (low + high) / 2;

        if(pos <= mid)
        {
            update(2 * idx, low, mid, pos, newVal);
        }
        else
        {
            update(2 * idx + 1, mid + 1, high, pos, newVal);
        }

        tree[idx] = combine(tree[2 * idx], tree[2 * idx + 1]);
    }

    Node query(int idx, int low, int high, int queryL, int queryR)
    {
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

    void update(int pos, int val)
    {
        update(1, 1, n, pos, val);
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
    tree.update(2, -2);
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