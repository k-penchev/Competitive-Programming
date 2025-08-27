#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2 * 1e5 + 10;
const int INF = 1e9;

int t, n;
int a[MAXN];
int dp[2][MAXN];

void solve()
{
    cin >> t;

    for(int i = 0 ; i < t ; ++i)
    {
        cin >> n;

        for(int j = 0 ; j <= n ; ++j)
        {
            a[j] = 0;
            dp[0][j] = dp[1][j] = INF;
        }

        for(int j = 0 ; j < n ; ++j)
        {
            cin >> a[j];
        }

        dp[1][0] = 0;

        for(int k = 0 ; k < n ; ++k)
        {
            dp[0][k + 1] = min(dp[0][k + 1], dp[1][k] + a[k]);
            dp[1][k + 1] = min(dp[1][k + 1], dp[0][k]);

            if(k + 2 <= n)
            {
                dp[0][k + 2] = min(dp[0][k + 2], dp[1][k] + a[k] + a[k + 1]);
                dp[1][k + 2] = min(dp[1][k + 2], dp[0][k]);
            }
        }

        cout << min(dp[0][n], dp[1][n]) << "\n";
    }
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