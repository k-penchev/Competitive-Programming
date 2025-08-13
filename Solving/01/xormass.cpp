#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 1e5 + 10;
const int MAXQ = 2 * 1e6 + 10;
const int MAX_LOG = 30;

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

Fenwick tree[MAX_LOG];

void addNum(int num, int idx)
{
    for(int j = 0 ; j < MAX_LOG ; ++j)
    {
        if(num & (1 << j))
        {
            tree[j].update(idx, +1);
        }
    }
}

void removeNum(int num, int idx)
{
    for(int j = 0 ; j < MAX_LOG ; ++j)
    {
        if(num & (1 << j))
        {
            tree[j].update(idx, -1);
        }
    }
}

void solve()
{
    cin >> n >> q;


    for(int i = 1 ; i <= n ; ++i)
    {
        cin >> a[i];
        addNum(a[i], i);
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
                removeNum(a[i], i);
                a[i] = a[i] & x;
                addNum(a[i], i);
            }
        }
        else if(qType == '|')
        {
            cin >> x;
            
            for(int i = l ; i <= r ; ++i)
            {
                removeNum(a[i], i);
                a[i] = a[i] | x;
                addNum(a[i], i);
            }
        }
        else
        {
            int answer = 0;

            for(int j = 0 ; j < MAX_LOG ; ++j)
            {
                int cnt1 = tree[j].query(r) - tree[j].query(l - 1);
                int cnt0 = (r - l + 1) - cnt1;
                answer += cnt0 * cnt1 * (1 << j);
            }

            cout << answer << "\n";
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
    
    return 0;
}