#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 2 * 1e5 + 10;

int n, q;
int a[MAXN];

struct Fenwick
{
    int bit[MAXN];

    Fenwick()
    {
        memset(bit, 0, sizeof(bit));
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
        int xorSum = 0;

        for(; idx >= 1 ; idx -= (idx & (-idx)))
        {
            xorSum ^= bit[idx];
        }

        return xorSum;
    }

    int range_query(int l, int r)
    {
        return query(r) ^ query(l - 1);
    }
};

Fenwick tree[2];

void solve()
{
    cin >> n >> q;

    for(int i = 1 ; i <= n ; ++i)
    {
        cin >> a[i];
        tree[(i % 2)].update(i, a[i]);
    }

    int qType, x, y;

    for(int i = 1 ; i <= q ; ++i)
    {
        cin >> qType >> x >> y;

        if(qType == 1)
        {
            int parity = x % 2;
            
            int old_value = tree[parity].range_query(x, x);

            int delta = old_value ^ y;
            
            tree[parity].update(x, delta);
        }
        else
        {
            int range = (y - x + 1);

            if(range % 2 == 0)
            {
                cout << "0" << "\n";
            }
            else
            {
                int parity = x % 2;

                cout << tree[parity].range_query(x, y) << "\n";
            }
        }
    }
}

void fastIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

signed main()
{
    fastIO();
    solve();
}