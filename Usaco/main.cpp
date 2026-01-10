#include <iostream>
#include <algorithm>
#include <vector>

typedef long long llong;
const int MAXN = 200000 + 10;
const int MAXLOG = 20;

int n, q;
int a[MAXN];

struct MST
{
    std::vector<int> tree[4 * MAXN];

    void build(int node, int l, int r, int arr[])
    {
        tree[node].reserve(r - l + 1);

        if(l == r)
        {
            tree[node].push_back(arr[l]);
            return;
        }

        int mid = l + r >> 1;
        build(2 * node, l, mid, arr);
        build(2 * node + 1, mid + 1, r, arr);

        int lPtr = 0, rPtr = 0;
        for(int i = 0 ; i < tree[2 * node].size() + tree[2 * node + 1].size() ; ++i)
        {
            if(lPtr == tree[2 * node].size())
            {
                tree[node].push_back(tree[2 * node + 1][rPtr++]);
                continue;
            }

            if(rPtr == tree[2 * node + 1].size())
            {
                tree[node].push_back(tree[2 * node][lPtr++]);
                continue;
            }

            if(tree[2 * node][lPtr] <= tree[2 * node + 1][rPtr])
            {
                tree[node].push_back(tree[2 * node][lPtr++]);
            }
            else
            {
                tree[node].push_back(tree[2 * node + 1][rPtr++]);
            }
        }
    }

    int binary(int node, int k)
    {
        int l = -1, r = tree[node].size();
        while(l + 1 < r)
        {
            int mid = l + r >> 1;
            if(tree[node][mid] > k) r = mid;
            else l = mid;
        }

        return r;
    }

    int query(int node, int l, int r, int queryL, int queryR, int queryVal)
    {
        if(queryL <= l && r <= queryR)
        {
            return binary(node, queryVal);
        }

        int res = 0;
        int mid = l + r >> 1;
        if(queryL <= mid) res += query(2 * node, l, mid, queryL, queryR, queryVal);
        if(mid + 1 <= queryR) res += query(2 * node + 1, mid + 1, r, queryL, queryR, queryVal);
        return res;
    }

    void build(int arr[])
    {
        build(1, 1, n, arr);
    }

    int query(int l, int r, int k)
    {
        return query(1, 1, n, l, r, k);
    }
};

MST tree;

void solve()
{
    std::cin >> n >> q;

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> a[i];
    }

    tree.build(a);
    for(int i = 1 ; i <= q ; ++i)
    {
        int intervalL, intervalR;
        std::cin >> intervalL >> intervalR;

        int l = -1, r = 2e5 + 1;
        while(l + 1 < r)
        {
            int mid = l + r >> 1;
            if(tree.query(intervalL, intervalR, mid) >= mid) r = mid;
            else l = mid;
        }

        std::cout << r << "\n";
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