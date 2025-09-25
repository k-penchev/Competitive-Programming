#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

int n;

void solve()
{
    cin >> n;

    vector<int> dp(n + 1, 0);

    dp[0] = 1;

    for(int s = 0 ; s < n ; ++s)
    {
        for(int j = 1 ; j <= 6 ; ++j)
        {
            if(s + j <= n)
            {
                dp[s + j] = (dp[s] + dp[s + j]) % MOD;
            }
        }
    }

    cout << dp[n] << "\n";
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