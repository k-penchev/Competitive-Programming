#include <bits/stdc++.h>

#define int long long

using namespace std;

const int MAXN = 1e5 + 10; 

int n, q;

struct Fenwick
{
    int bit[MAXN];

    void reset()
    {
        for(int i = 1 ; i <= n ; ++i)
        {
            bit[i] = 0;
        }
    }

    void update(int idx, int val)
    {
        for(; idx <= n ; idx += (idx & (-idx)))
        {
            bit[idx] += val;
        }
    }

    int query(int idx)
    {
        int sum = 0;

        for(; idx >= 1 ; idx -= (idx & (-idx)))
        {
            sum += bit[idx];
        }

        return sum;
    }
};

int a[MAXN], b[MAXN], id[MAXN], answer[MAXN], pref[MAXN];
Fenwick tree;

void solve()
{
    cin >> n;
    
    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i];
        id[a[i]] = i;
    }

    for(int i = 1; i <= n; ++i)
    {
        cin >> b[i];
        b[i] = id[b[i]];
    }

    tree.reset();

    for(int i = 1 ; i <= n ; ++i)
    {
        answer[i] = i - tree.query(b[i]) - 1;
        tree.update(b[i], +1);
        pref[i] = pref[i - 1] + answer[i];
    }

    cout << "\n";

    cin >> q;

    for(int i = 1 ; i <= q ; ++i)
    {
        int l, r; cin >> l >> r;
        cout << pref[r] - pref[l - 1] << "\n";
    }

}

void fastIO()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

signed main()
{
    fastIO();
    solve();
}
