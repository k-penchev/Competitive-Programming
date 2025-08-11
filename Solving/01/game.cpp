#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 1e5 + 10;
const int MAXQ = 2 * 1e6 + 10;
const int LOG = 17;
const int INF = 1e9;

int n, k, q;
int a[MAXN], length[MAXN], idx[MAXN];

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
                if(type == 1)
                    table[i][j] = gcd(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
                else if(type == 2)
                    table[i][j] = max(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
                else
                    table[i][j] = min(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
            
            }
        }
    }

    int query(int l, int r, int type)
    {
        --l, --r;
        int k = lg[r - l + 1];
        
        if(type == 1)
            return gcd(table[l][k], table[r - (1 << k) + 1][k]);
        else if(type == 2)
            return max(table[l][k], table[r - (1 << k) + 1][k]);
        else
            return min(table[l][k], table[r - (1 << k) + 1][k]);
    }
};

Sparse table_gcd, table_max, table_min;

int binary1(int l, int r)
{
    int lPtr = l - 1, rPtr = r + 1;

    while(rPtr > lPtr + 1)
    {
        int mid = (lPtr + rPtr) / 2;

        if(table_gcd.query(mid, r, 1) >= k)
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
    table_gcd.build(a, 1);
    

    for(int i = 1 ; i <= n ; ++i)
    {
        // i - 1 ; length[i - 1]
        int last = (i - 1 - length[i - 1] + 1);
        length[i] = binary1(last, i);
        idx[i] = i - length[i] + 1;
    }

    table_max.build(length, 2);
    table_min.build(idx, 3);
}


int binary2(int l, int r)
{
    int lPtr = l - 1, rPtr = r + 1;

    while(rPtr > lPtr + 1)
    {
        int mid = (lPtr + rPtr) / 2;

        if(table_min.query(mid, r, 3) <= l)
        {
            lPtr = mid;
        }
        else
        {
            rPtr = mid;
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
    int max_length = table_max.query(x + 1, r, 2);
    
    return max(max_length, x - l + 1);
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