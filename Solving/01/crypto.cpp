#include <bits/stdc++.h>

#define int long long

using namespace std;

const int MAXN = 3 * 1e5 + 10;
const int MOD  = 1e9 + 7;

int n;
int a[MAXN], b[MAXN], compressed[MAXN];
pair<int, int> toCompress[MAXN];

struct Fenwick
{
    
    int bit[MAXN];

    void set()
    {
        for(int i = 0 ; i <= n ; i++)
        {
            bit[i] = 0;
        }
    }

    void update(int idx, int val)
    {
        while(idx <= n)
        {
            bit[idx] += val;
            idx += idx & (-idx);
        }
    }

    int query(int idx)
    {
        int sum = 0;

        while(idx >= 1)
        {
            sum += bit[idx];
            idx -= idx & (-idx);
        }

        return sum;
    }
};

Fenwick tree;
int answer = 1;

void solve()
{
    cin >> n;

    for(int i = 1 ; i <= n ; ++i)
    {
        cin >> a[i];
        toCompress[i] = {a[i], i};
    }

    sort(toCompress + 1, toCompress + n + 1);

    int cnt = 0;
    for(int i = 1 ; i <= n ; ++i)
    {
        cnt += (toCompress[i].first != toCompress[i - 1].first);
        compressed[toCompress[i].second] = cnt;
    }

    b[1] = 1;

    for(int i = 2 ; i <= n ; ++i)
    {
        b[i] = ( b[i - 1] * i ) % MOD;
    }


    tree.set();

    for(int i = 1 ; i <= n ; ++i)
    {
        tree.update(i, +1);
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        int smaller = (tree.query(compressed[i]) - 1);
        answer += smaller * b[n - i];
        answer %= MOD;
        tree.update(compressed[i], -1);
    }

    cout << answer << "\n";
}

void fastIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

signed main()
{
    fastIO();
    solve();
}