#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;
const int INF = 1e9;

int n;

void solve()
{
    cin >> n;

    int halfSum = n * (n + 1) / 2;
    int setSum = halfSum / 2;

    vector<vector<int>> dp(n + 1, vector<int>(setSum + 1));

    dp[0][0] = 1;

    for(int i = 1 ; i < n ; ++i)
    {
        for(int j = 0 ; j <= setSum ; ++j)
        {
            dp[i][j] += dp[i - 1][j];

            int prev = j - i;

            if(prev >= 0)
            {
                dp[i][j] += dp[i - 1][prev];
            }

            dp[i][j] %= MOD;
        }
    }

    cout << dp[n - 1][setSum] << "\n";
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