#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50;
const int MAXK = 50;

int k, n;
long long dp[MAXK][MAXN]; // last, len

void solve()
{
    cin >> k >> n;

    for(int last = 1 ; last <= k ; ++last)
    {
        dp[last][1] = 1;
    }

    for(int len = 1 ; len <= n ; ++len)
    {
        for(int last = 1 ; last <= k ; ++last)
        {
            for(int smaller = 1 ; smaller < last ; ++smaller)
            {
                dp[last][len] += dp[smaller][len - 1];
            }
        }
    }

    long long ans = 0;

    for(int last = 1 ; last <= k ; ++last)
    {
        ans += dp[last][n];
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