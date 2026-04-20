#include <iostream>
#include <algorithm>
#include <vector>
 
const int MAXN = 2 * 1e5 + 10;
const int MAXLOG = 25;
 
int n, q;
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
 
    int cnt;
    Node tree[MAXN * MAXLOG];
    
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
 
    void update(int newNode, int oldNode, int l, int r, int queryPos, int queryVal)
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
            update(tree[newNode].left, tree[oldNode].left, l, mid, queryPos, queryVal);
        }
        else
        {   
            tree[newNode].right = ++cnt;
            update(tree[newNode].right, tree[oldNode].right, mid + 1, r, queryPos, queryVal);
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
 
    int update(int oldRoot, int pos, int val)
    {
        int newRoot = ++cnt;
        update(newRoot, oldRoot, 1, n, pos, val);
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
    std::cin >> n >> q;
 
    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> a[i];
    }
 
    root[++version] = tree.build(a);
    for(int i = 1 ; i <= q ; ++i)
    {
        int type, x, y, z;
 
        std::cin >> type;
        if(type == 1)
        {
            std::cin >> x >> y >> z;
            root[x] = tree.update(root[x], y, z);
        }
        else if(type == 2)
        {
            std::cin >> x >> y >> z;
            std::cout << tree.query(root[x], y, z) << "\n";
        }
        else
        {
            std::cin >> x;
            root[++version] = root[x];
        }
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