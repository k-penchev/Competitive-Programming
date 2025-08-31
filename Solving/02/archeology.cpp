#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500 + 5;
const int MOD = 1e9 + 7;

int n, l, r;
long long dp[2][MAXN * MAXN];
long long pref[2][MAXN * MAXN];

void precompute(int row)
{
    pref[row & 1][0] = dp[row & 1][0];

    for(int k = 1 ; k <= (row * (row - 1)) / 2 ; ++k)
    {
        pref[row & 1][k] = (pref[row & 1][k - 1] + dp[row & 1][k]) % MOD;
    }
}

void clear(int row)
{
    for(int col = 0 ; col < MAXN * MAXN ; ++col)
    {
        dp[row & 1][col] = 0;
    }
}

void solve()
{
    cin >> n >> l >> r;

    dp[0][0] = 1;

    for(int len = 1 ; len <= n ; ++len)
    {
        precompute(len - 1);
        clear(len);

        dp[len & 1][0] = 1;

        int Kprev = (len - 1) * (len - 2) / 2;

        for(int k = 1 ; k <= (len * (len - 1)) / 2 ; ++k)
        {
            int t = min(k, len - 1);

            int lower = k - t;
            int upper = min(k, Kprev);

            if(lower <= upper)
            {
                long long sum = (pref[(len - 1) & 1][upper] - (lower ? pref[(len - 1) & 1][lower - 1] : 0)) % MOD;
                
                if (sum < 0) sum += MOD;
                
                dp[len & 1][k] = (dp[len & 1][k] + sum) % MOD;
            }
                
        }
    }

    long long ans = 0;

    for(int k = l ; k <= r ; ++k)
    {
        ans = (ans + dp[n & 1][k]) % MOD;
    }

    cout << ans << "\n";
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
}