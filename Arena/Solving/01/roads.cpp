#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;

int n, q;
int arr[MAXN];

struct SegmentTree
{
    int tree[4 * MAXN];

    void build(int idx, int low, int high, int a[])
    {
        if(low == high)
        {
            tree[idx] = a[low];
            return;
        }

        int mid = (low + high) / 2;
        int left = 2 * idx;
        int right = 2 * idx + 1;

        build(left, low, mid, a);
        build(right, mid + 1, high, a);

        tree[idx] = min(tree[left], tree[right]);
    }

    void update(int idx, int low, int high, int pos, int val)
    {
        if(low == high)
        {
            tree[idx] = val;
            return;
        }

        int mid = (low + high) / 2;
        int left = 2 * idx;
        int right = 2 * idx + 1;


        if(pos <= mid)
        {
            update(left, low, mid, pos, val);
        }
        else
        {
            update(right, mid + 1, high, pos, val);
        }

        tree[idx] = min(tree[left], tree[right]);
    }

    int query(int idx, int low, int high, int queryL, int queryR)
    {
        if(queryL > high || queryR < low)
        {
            return INT_MAX;
        }
        else if(queryL <= low && high <= queryR)
        {
            return tree[idx];
        }

        int mid = (low + high) / 2;
        int left = 2 * idx;
        int right = 2 * idx + 1;

        int le = query(left, low, mid, queryL, queryR);
        int ri = query(right, mid + 1, high, queryL, queryR);

        return min(le, ri);
    }

    void build(int a[])
    {
        build(1, 1, n, a);
    }

    void update(int pos, int val)
    {
        update(1, 1, n, pos, val);
    }

    int binary_left(int l, int r, int k)
    {
        int lPtr = l - 1, rPtr = r + 1;

        while(rPtr > lPtr + 1)
        {
            int mid = (lPtr + rPtr) / 2;

            if(query(1, 1, n, mid, r) >= k)
            {
                rPtr = mid;
            }
            else
            {
                lPtr = mid;
            }
        }

        return rPtr;
    }

    int binary_right(int l, int r, int k)
    {
        int lPtr = l - 1, rPtr = r + 1;

        while(rPtr > lPtr + 1)
        {
            int mid = (lPtr + rPtr) / 2;

            if(query(1, 1, n, l, mid) >= k)
            {
                rPtr = mid;
            }
            else
            {
                lPtr = mid;
            }
        }

        return rPtr;
    }

    int query(int q, int k)
    {
        int roads = 1;

        int left_index = binary_left(1, q, k);
        int right_index = binary_right(q, n, k);

        return roads;
    }
        
};

SegmentTree tree;

void solve()
{
    cin >> n >> q;

    for(int i = 1 ; i <= n ; ++i)
    {
        cin >> arr[i];
    }

    tree.build(arr);

    int type, x, y;

    for(int i = 1 ; i <= q ; ++i)
    {
        cin >> type >> x >> y;

        if(type == 1)
        {
            tree.update(x, y);
        }
        else
        {
            cout << tree.query(x, y) << "\n";
        }
    }
    
}

void fastIO()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

int main()
{
    fastIO();
    solve();
}