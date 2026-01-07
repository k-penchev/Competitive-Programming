#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>

typedef long long llong;
const int MAXN = 100000 + 10;
const int MAXLOG = 25;

int n, q;
int a[MAXN];
int b[MAXN];

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
    };

    Node tree[MAXN * MAXLOG];
    int cnt;

    void build(int node, int l, int r)
    {
        if(l == r)
        {
            tree[node].sum = 0;
            return;
        }

        int mid = l + r >> 1;
        tree[node].left = ++cnt;
        tree[node].right = ++cnt;
        build(tree[node].left, l, mid);
        build(tree[node].right, mid + 1, r);
        tree[node].assign(tree[tree[node].left], tree[tree[node].right]);
    }

    void update(int newNode, int oldNode, int l, int r, int queryPos, int queryVal)
    {
        tree[newNode] = tree[oldNode];

        if(l == r)
        {
            tree[newNode].sum += queryVal;
            return;
        }

        int mid = l + r >> 1;
        if(queryPos <= mid)
        {
            tree[newNode].left = ++cnt;
            update(tree[newNode].left, tree[oldNode].left, l, mid, queryPos, queryVal);
        }
        else
        {
            tree[newNode].right = ++cnt;
            update(tree[newNode].right, tree[oldNode].right, mid + 1, r, queryPos, queryVal);
        }   

        tree[newNode].assign(tree[tree[newNode].left], tree[tree[newNode].right]);
    }

    int descent(int nodeFirst, int nodeSecond, int l, int r, int k)
    {
        if(l == r)
        {
            return l;
        }

        int mid = l + r >> 1;
        if(tree[tree[nodeSecond].left].sum - tree[tree[nodeFirst].left].sum >= k)
        {
            return descent(tree[nodeFirst].left, tree[nodeSecond].left, l, mid, k);
        }

        return descent(tree[nodeFirst].right, tree[nodeSecond].right, mid + 1, r, k - (tree[tree[nodeSecond].left].sum - tree[tree[nodeFirst].left].sum));
    }

    void build()
    {
        cnt = 1;
        build(1, 1, n);
    }

    int update(int oldNode, int queryPos, int queryVal)
    {
        int newNode = ++cnt;
        update(newNode, oldNode, 1, n, queryPos, queryVal);
        return newNode;
    }

    int descent(int nodeFirst, int nodeSecond, int k)
    {
        return descent(nodeFirst, nodeSecond, 1, n, k);
    }
};

int root[MAXN];
PersistentSegmentTree tree;
std::unordered_map<int, int> map;
std::unordered_map<int, int> rev;

void solve()
{
    std::cin >> n >> q;

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> a[i];
        b[i] = a[i];
    }

    int value = 1;
    std::sort(b + 1, b + n + 1);
    for(int i = 1 ; i <= n ; ++i)
    {
        map[b[i]] = value;
        rev[value] = b[i];

        if(i != n && b[i] != b[i + 1])
        {
            value += 1;
        }
    }
    
    root[0] = 1;
    tree.build();
    for(int i = 1 ; i <= n ; ++i)
    {
        root[i] = tree.update(root[i - 1], map[a[i]], +1);
    }

    for(int i = 1 ; i <= q ; ++i)
    {
        int l, r, k;
        std::cin >> l >> r >> k;
        std::cout << rev[tree.descent(root[l - 1], root[r], k)] << "\n";
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
}