#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5;

int n, t;
int w[MAXN], v[MAXN];

void solve()
{
    cin >> n >> t;

    vector<vector<int>> dp(2, vector<int>(t + 1, 0));

    for(int i = 1 ; i <= n ; ++i)
    {
        cin >> w[i] >> v[i];
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        for(int j = 0 ; j <= t ; ++j)
        {
            dp[i & 1][j] = dp[(i - 1) & 1][j];

            if (j >= w[i])
            {
                dp[i & 1][j] = max(dp[i & 1][j], v[i] + dp[(i - 1) & 1][j - w[i]]);
            }
        }
    }


    cout << dp[n & 1][t] << "\n";
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