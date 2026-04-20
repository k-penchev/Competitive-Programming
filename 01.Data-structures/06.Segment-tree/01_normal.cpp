#include <iostream>
#include <algorithm>
#include <vector>

typedef long long llong;
const int MAXN = 100000 + 10;
const int INF = 1e9 + 10;

int n;
struct SegmentTree
{
    int tree[4 * MAXN];

    void build(int node, int l, int r, int arr[])
    {
        if(l == r)
        {
            tree[node] = arr[l];
            return;
        }

        int mid = l + r >> 1;
        build(2*node, l, mid, arr);
        build(2*node + 1, mid + 1, r, arr);
        tree[node] = tree[2*node] + tree[2*node + 1];
    }

    void update(int node, int l, int r, int queryPos, int queryVal)
    {
        if(l == r)
        {
            tree[node] = queryVal;
            return;
        }

        int mid = l + r >> 1;
        if(queryPos <= mid) update(2*node, l, mid, queryPos, queryVal);
        else update(2*node + 1, mid + 1, r, queryPos, queryVal);
        tree[node] = tree[2*node] + tree[2*node + 1];
    }

    int query(int node, int l, int r, int queryL, int queryR)
    {
        if(queryL <= l && r <= queryR)
        {
            return tree[node];
        }

        int ans = 0;
        int mid = l + r >> 1;
        if(queryL <= mid) ans += query(2*node, l, mid, queryL, queryR);
        if(mid + 1 <= queryR) ans += query(2*node + 1, mid + 1, r, queryL, queryR);
        return ans;
    }
};

int a[MAXN];
SegmentTree tree;

void solve()
{
    std::cin >> n;
    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> a[i];
    }

    tree.build(1, 1, n, a);
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