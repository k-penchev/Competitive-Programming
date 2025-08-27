#include <bits/stdc++.h>

#define int long long

using namespace std;

const int MAXN = 2 * 1e5 + 10;

int n;
int a[MAXN];
int dp[MAXN];
pair<int, int> toCompress[MAXN];
int compressed[MAXN];

struct Fenwick
{
    int bit[MAXN];

    Fenwick()
    {
        memset(bit, 0, sizeof(bit));
    }

    void update(int idx, int value)
    {
        for(; idx <= n ; idx += (idx & (-idx)))
        {
            bit[idx] = max(bit[idx], value);
        }
    }

    int query(int idx)
    {
        int answer = 0;

        for(; idx >= 1 ; idx -= (idx & (-idx)))
        {
            answer = max(answer, bit[idx]);
        }

        return answer;
    }
};

Fenwick tree;

void solve()
{
    cin >> n;

    for(int i = 1 ; i <= n ; ++i)
    {
        cin >> a[i];
        toCompress[i] = {a[i], i};
        dp[i] = 1;
    }

    sort(toCompress + 1, toCompress + n + 1);

    int cnt = 1;

    for(int i = 1 ; i <= n ; ++i)
    {
        compressed[toCompress[i].second] = cnt;
        cnt += (toCompress[i].first != toCompress[i + 1].first);
    }

    int best = 0;

    for(int i = 1 ; i <= n ; ++i)
    {
        dp[i] = 1 + tree.query(compressed[i] - 1);

        tree.update(compressed[i], dp[i]);

        best = max(best, dp[i]);
    }

    cout << best << "\n";
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