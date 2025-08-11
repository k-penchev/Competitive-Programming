#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;

int n, q;
int a[MAXN];

struct Fenwick
{
    int bit[MAXN];

    void set()
    {
        for(int i = 0 ; i <= n ; ++i)
        {
            bit[i] = 0;
        }
    }

    void update(int idx, int val)
    {
        for(; idx <= n ; idx += (idx & (-idx)))
        {
            bit[idx] ^= val;
        }
    }

    int query(int idx)
    {
        int result = 0;

        for(; idx >= 1 ; idx -= (idx & (-idx)))
        {
            result ^= bit[idx];
        }

        return result;
    }


    int range_query(int l, int r)
    {
        return query(r) ^ query(l - 1);
    }
};

Fenwick tree;

void solve()
{
    cin >> n >> q;

    tree.set();

    for(int i = 1 ; i <= n ; ++i)
    {
        cin >> a[i];
        tree.update(i, a[i]);
    }

    char qType;
    int l, r, x;

    for(int i = 1 ; i <= q ; ++i)
    {
        cin >> qType >> l >> r;

        if(qType == '&')
        {
            cin >> x;

            for(int i = l ; i <= r ; ++i)
            {
                a[i] = a[i] & x;
                tree.update(i, a[i]);
            }
        }
        else if(qType == '|')
        {
            cin >> x;

            for(int i = l ; i <= r ; ++i)
            {
                a[i] = a[i] | x;
                tree.update(i, x);
            }
        }
        else
        {

        }

    }
}


void fastIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

int main()
{
    fastIO();
    solve();
    
    return 0;
}