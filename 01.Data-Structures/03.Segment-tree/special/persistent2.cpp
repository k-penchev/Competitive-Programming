/*
    Applications:
    - Find number of smaller (bigger) elements than X in [L, R]
    - Find the largest (smallest) element, which is smaller (bigger) than X in [L, R] 
    - Find how many elements are in the range [X, Y] in [L, R]
    - Find the k-th smallest (biggest) element in [L, R]

    PST has the same applications as MST.
    Note: PST -> O(log N) , MST -> O(log^2 N)
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

typedef long long llong;
const int MAXN = 100000 + 10;
const int MAXLOG = 25;
const int INF = 1e9 + 10;

int n, m;
struct PersistentSegmentTree
{
    struct Node
    {
        int sum;
        int left;
        int right;

        Node()
        {
            sum = 0;
            left = 0;
            right = 0;
        }

        void assign(const Node &left, const Node &right)
        {
            sum = left.sum + right.sum;
        }
    };

    int cnt;
    Node tree[MAXLOG * MAXN];

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

    int descent(int firstNode, int secondNode, int l, int r, int k)
    {
        if(l == r)
        {
            return l;
        }

        int mid = l + r >> 1;
        if(tree[tree[secondNode].left].sum - tree[tree[firstNode].left].sum >= k)
        {
            return descent(tree[firstNode].left, tree[secondNode].left, l, mid, k);
        }

        return descent(tree[firstNode].right, tree[secondNode].right, mid + 1, r, k - (tree[tree[secondNode].left].sum - tree[tree[firstNode].left].sum));
    }
    

    int build()
    {
        cnt = 1;
        build(1, 1, n);
        return 1;
    }

    int update(int oldRoot, int queryPos, int queryVal)
    {
        int newRoot = ++cnt;
        update(newRoot, oldRoot, 1, n, queryPos, queryVal);
        return newRoot;
    }

    int kth(int firstRoot, int secondRoot, int k)
    {
        return descent(firstRoot, secondRoot, 1, n, k);
    }
};

int a[MAXN];
int b[MAXN];
std::map<int, int> map;
std::map<int, int> rev;
PersistentSegmentTree tree;
int root[MAXN];

void solve()
{
    std::cin >> n >> m;
    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> a[i];
        b[i] = a[i];
    }

    int cnt = 1;
    std::sort(b + 1, b + n + 1);
    for(int i = 1 ; i <= n ; ++i)
    {
        map[b[i]] = cnt;
        rev[cnt] = b[i];
        if(i != n && b[i] != b[i + 1]) cnt += 1;
    }

    root[0] = tree.build();
    for(int i = 1 ; i <= n ; ++i)
    {
        root[i] = tree.update(root[i - 1], map[a[i]], +1);
    }

    for(int i = 1 ; i <= m ; ++i)
    {
        int l, r, k;
        std::cin >> l >> r >> k;
        std::cout << rev[tree.kth(root[l - 1], root[r], k)] << "\n";
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