#include <iostream>
#include <algorithm>
#include <vector>

typedef long long llong;
const int MAXN = 25000 + 10;
const int MAXLOG = 30;
const int INF = 1e9 + 10;

int n;
int a[MAXN];

struct DynamicSegmentTree
{
    struct Node
    {
        int sum;
        int left, right;

        Node()
        {
            sum = 0;
            left = right = 0;
        }

        void assign(const Node &left, const Node &right)
        {
            sum = left.sum + right.sum;
        }
    };

    int cnt = 1;
    Node tree[MAXLOG * MAXN];

    void update(int node, int l, int r, int queryPos, int queryVal)
    {
        if(l == r)
        {
            tree[node].sum += queryVal;
            return;
        }

        int mid = l + r >> 1;
        if(queryPos <= mid)
        {
            if(tree[node].left == 0)
            {
                tree[node].left = ++cnt;
            }

            update(tree[node].left, l, mid, queryPos, queryVal);
        }
        else
        {
            if(tree[node].right == 0)
            {
                tree[node].right = ++cnt;
            }

            update(tree[node].right, mid + 1, r, queryPos, queryVal);
        }

        tree[node].assign(tree[tree[node].left], tree[tree[node].right]);
    }

    int query(int node, int l, int r, int queryL, int queryR)
    {
        if(node == 0 || r < queryL || queryR < l)
        {
            return 0;
        }

        if(queryL <= l && r <= queryR)
        {
            return tree[node].sum;
        }

        int res = 0;
        int mid = l + r >> 1;
        res += query(tree[node].left, l, mid, queryL, queryR);
        res += query(tree[node].right, mid + 1, r, queryL, queryR);
        return res;
    }

    void update(int pos, int val)
    {
        update(1, 1, INF, pos, val);
    }

    int query(int l, int r)
    {
        return query(1, 1, INF, l, r);
    }
};

DynamicSegmentTree tree;

void solve()
{
    std::cin >> n;

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> a[i];
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