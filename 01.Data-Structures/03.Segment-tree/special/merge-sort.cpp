/*
    Applications:
    - Find number of smaller (bigger) elements than X in [L, R]
    - Find the largest (smallest) element, which is smaller (bigger) than X in [L, R] 
    - Find how many elements are in the range [X, Y] in [L, R]
    - Find the k-th smallest (biggest) element

    Advanced:
    - Inside each Node of the MST we can store:
      * Vector / Multiset (as implemented)
      * Fenwick
      * Treap
      * CHT
*/

#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>

const int MAXN = 1e5 + 10;

int n;
int a[MAXN];

struct MST
{
    // If we need to do updates, we should use std::multiset
    std::vector<int> tree[4 * MAXN];

    void build(int idx, int l, int r, int arr[])
    {
        if(l == r)
        {
            tree[idx].push_back(arr[l]);
            return;
        }

        int mid = l + r >> 1;
        build(2 * idx, l, mid, arr);
        build(2 * idx + 1, mid + 1, r, arr);

        int lPtr = 0, rPtr = 0;
        for(int i = 0 ; i < tree[2 * idx].size() + tree[2 * idx + 1].size() ; ++i)
        {
            if(lPtr == tree[2 * idx].size())
            {
                tree[idx].push_back(tree[2 * idx + 1][rPtr++]);
                continue;
            }

            if(rPtr == tree[2 * idx + 1].size())
            {
                tree[idx].push_back(tree[2 * idx][lPtr++]);
                continue;
            }

            if(tree[2 * idx][lPtr] <= tree[2 * idx + 1][rPtr])
            {
                tree[idx].push_back(tree[2 * idx][lPtr++]);
            }
            else
            {
                tree[idx].push_back(tree[2 * idx + 1][rPtr++]);
            }
        }
    }

    int binary(int idx, int k)
    {
        int l = -1, r = tree[idx].size();
        while(l + 1 < r)
        {
            int mid = l + r >> 1;
            if(tree[idx][mid] <= k) l = mid;
            else r = mid;
        }

        return l + 1;
    }

    int query(int idx, int l, int r, int queryL, int queryR, int queryVal)
    {
        if(queryL <= l && r <= queryR)
        {
            return binary(idx, queryVal);
        }

        int res = 0;
        int mid = l + r >> 1;
        if(queryL <= mid) res += query(2 * idx, l, mid, queryL, queryR, queryVal);
        if(queryR >= mid + 1) res += query(2 * idx + 1, mid + 1, r, queryL, queryR, queryVal);
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

    int findKth(int queryL, int queryR, int k)
    {
        assert(k <= (queryR - queryL + 1));

        int l = -1, r = 1e9 + 1;
        while(l + 1 < r)
        {
            int mid = l + r >> 1;
            if(query(queryL, queryR, mid) >= k) r = mid;
            else l = mid;
        }

        return r;
    }
};

MST tree;

void solve()
{
    std::cin >> n;

    for(int i = 1 ; i <= n ; ++i)
    {
        std::cin >> a[i];
    }

    tree.build(a);
    std::cout << tree.query(5, 10, 2) << "\n";
    std::cout << tree.findKth(3, 7, 3) << "\n";
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