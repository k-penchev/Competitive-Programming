#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 1e5 + 10;
const int MAXQ = 2 * 1e6 + 10;
const int LOG = 17;
const int INF = 1e9;

int n, k, q;
int a[MAXN], length[MAXN], idx[MAXN];

struct SegmentTree
{
    int tree[4 * MAXN];

    void build(int idx, int low, int high, int arr[])
    {
        if(low == high)
        {
            tree[idx] = arr[low];
            return;
        }

        int mid = (low + high) / 2;
        int left = 2 * idx;
        int right = 2 * idx + 1;
        
        build(left, low, mid, arr);
        build(right, mid + 1, high, arr);

        tree[idx] = max(tree[left], tree[right]);
    }

    void build(int arr[])
    {
        build(1, 1, n, arr);
    }

    int query(int idx, int low, int high, int queryL, int queryR)
    {
        if(queryL > high || queryR < low)
        {
            return INT_MIN;
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

        return max(le, ri);
    }

    int query(int l, int r)
    {
        return query(1, 1, n, l, r);
    }
};

struct Sparse
{
    int table[MAXN][LOG];
    int lg[MAXN];

    void build(int arr[], int type)
    {
        lg[1] = 0;

        for(int i = 2 ; i <= n ; ++i)
        {
            lg[i] = lg[i / 2] + 1;
        }

        for(int i = 0 ; i < n ; ++i)
        {
            table[i][0] = arr[i + 1];
        }

        for(int j = 1 ; (1 << j) <= n ; ++j)
        {
            for(int i = 0 ; i + (1 << j) - 1 < n ; ++i)
            {
                if(type == 0)
                    table[i][j] = gcd(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
                else
                    table[i][j] = min(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int query(int l, int r, int type)
    {
        --l, --r;
        int k = lg[r - l + 1];

        if(type == 0)
            return gcd(table[l][k], table[r - (1 << k) + 1][k]);
        else
            return min(table[l][k], table[r - (1 << k) + 1][k]);
    }
};

Sparse table_gcd, table_min;
SegmentTree seg_max;

int binary1(int l, int r)
{
    int lPtr = l - 1, rPtr = r + 1;

    while(rPtr > lPtr + 1)
    {
        int mid = (lPtr + rPtr) / 2;

        if(table_gcd.query(mid, r, 0) >= k)
        {
            rPtr = mid;
        }
        else
        {
            lPtr = mid;
        }
    }

    return r - lPtr;
}

void precompute()
{
    table_gcd.build(a, 0);

    for(int i = 1 ; i <= n ; ++i)
    {
        // i - 1 ; length[i - 1]
        int last = (i - 1 - length[i - 1] + 1);
        length[i] = binary1(last, i);
        idx[i] = i - length[i] + 1;
    }

    seg_max.build(length);
    table_min.build(idx, 1);
}

int binary2(int l, int r)
{
    int lPtr = l - 1, rPtr = r + 1;

    while(rPtr > lPtr + 1)
    {
        int mid = (lPtr + rPtr) / 2;

        if(table_min.query(mid, r, 1) > l)
        {
            rPtr = mid;
        }
        else
        {
            lPtr = mid;
        }
    }

    return lPtr;
}

int compute(int l, int r)
{
    if(l == r)
    {
        return ( (a[l] >= k) ? 1 : 0 );
    }

    int x = binary2(l, r);
    
    return max(x - l + 1, seg_max.query(x + 1, r));
}

void solve()
{
    cin >> n >> k;

    for(int i = 1 ; i <= n ; ++i)
    {
        cin >> a[i];
    }

    
    precompute();
    
    cin >> q;

    int l, r;

    for(int i = 1 ; i <= q ; ++i)
    {
        cin >> l >> r;
        cout << compute(l, r) << "\n";
    }
}

void fastIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

signed main()
{
    fastIO();
    solve();
}