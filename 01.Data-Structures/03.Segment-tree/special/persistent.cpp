#include <iostream>
#include <algorithm>
#include <vector>

typedef long long llong;
const int MAXN = 25000 + 10;
const int MAXLOG = 20;
const int INF = 1e9 + 10;

int n;
int a[MAXN];

struct PersistentSegmentTree
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

        friend Node operator + (const Node &left, const Node &right)
        {
            Node res;
            res.sum = left.sum + right.sum;
            return res;
        }
    };  

    Node tree[2 * MAXN * MAXLOG];
    int cnt = 0;

    void build(int node, int l, int r, int arr[])
    {
        if(l == r)
        {
            tree[node].sum = arr[l];
            return;
        }

        int mid = l + r >> 1;
        tree[node].left = ++cnt;
        tree[node].right = ++cnt;
        build(tree[node].left, l, mid, arr);
        build(tree[node].right, mid + 1, r, arr);
        tree[node].assign(tree[tree[node].left], tree[tree[node].right]);
    }

    void update(int newNode, int oldNode, int l, int r, int queryVal, int queryPos)
    {
        tree[newNode] = tree[oldNode];

        if(l == r)
        {
            tree[newNode].sum = queryVal;
            return;
        }

        int mid = l + r >> 1;
        if(queryPos <= mid)
        {
            tree[newNode].left = ++cnt;
            update(tree[newNode].left, tree[oldNode].left, l, mid, queryVal, queryPos);
        }
        else
        {
            tree[newNode].right = ++cnt;
            update(tree[newNode].right, tree[oldNode].right, mid + 1, r, queryVal, queryPos);
        }

        tree[newNode].assign(tree[tree[newNode].left], tree[tree[newNode].right]);
    }

    Node query(int node, int l, int r, int queryL, int queryR)
    {
        if(queryL <= l && r <= queryR)
        {
            return tree[node];
        }

        Node res;
        int mid = l + r >> 1;
        if(queryL <= mid) res = res + query(tree[node].left, l, mid, queryL, queryR);
        if(mid + 1 <= queryR) res = res + query(tree[node].right, mid + 1, r, queryL, queryR);
        return res;
    }

    int build(int arr[])
    {
        cnt = 1;
        build(1, 1, n, arr);
        return 1;
    }

    int update(int oldRoot, int queryVal, int queryPos)
    {
        int newRoot = ++cnt;
        update(newRoot, oldRoot, 1, n, queryVal, queryPos);
        return newRoot;
    }

    int query(int root, int l, int r)
    {
        return query(root, 1, n, l, r).sum;
    }
};

int version;
int root[MAXN];
PersistentSegmentTree tree;

void solve()
{
    std::cin >> n;

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> a[i];
    }

    version = 1;
    root[1] = tree.build(a);
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