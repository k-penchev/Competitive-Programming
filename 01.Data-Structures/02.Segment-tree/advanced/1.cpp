//finding the maximum and the number of times it appears
#include <iostream>
#include <algorithm>
#include <vector>

const int MAXN = 1e5 + 10;
const int INF = 1e9;

int n;
int a[MAXN];

struct SegmentTree
{
    struct Node
    {
        int max;
        int cnt;

        Node()
        {
            max = -INF;
            cnt = 0;
        }

        Node(int x, int x_cnt)
        {
            max = x;
            cnt = x_cnt;
        }
    };

    Node tree[4 * MAXN];

    Node combine(const Node& x, const Node& y)
    {
        if(x.max == y.max)
        {
            return Node(x.max, x.cnt + y.cnt);
        }

        return (x.max > y.max ? x : y);
    }

    void build(int idx, int low, int high, int * arr)
    {
        if(low == high)
        {
            tree[idx] = Node(arr[low], 1);
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
            tree[idx] = Node(val, 1);
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

    Node query(int l, int r)
    {
        return query(1, 1, n, l, r);
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

    SegmentTree::Node result;

    result = tree.query(1, 5);
    std::cout << result.max << " " << result.cnt << "\n";

    tree.update(2, 0);

    result = tree.query(1, 5);
    std::cout << result.max << " " << result.cnt << "\n";
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