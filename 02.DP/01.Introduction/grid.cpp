#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e3 + 10;
const int INF = 1e9 + 10;
const int MOD = 1e9 + 7;

int n;
char grid[MAXN][MAXN];
long long dp[MAXN][MAXN];

void solve()
{
    cin >> n;

    for(int i = 1 ; i <= n ; ++i)
    {
        for(int j = 1 ; j <= n ; ++j)
        {
            cin >> grid[i][j];
        }
    }

    if(grid[1][1] == '*')
    {
        cout << "0" << "\n";
        return;
    }

    dp[1][1] = 1;

    for(int i = 1 ; i <= n ; ++i)
    {
        for(int j = 1 ; j <= n ; ++j)
        {
            if(grid[i][j] == '*') continue;

            if(grid[i][j + 1] != '*' && (j + 1) <= n)
                dp[i][j + 1] = (dp[i][j + 1] + dp[i][j]) % MOD;

            if(grid[i + 1][j] != '*' && (i + 1) <= n)
                dp[i + 1][j] = (dp[i + 1][j] + dp[i][j]) % MOD;
        }
    }

    cout << dp[n][n] << "\n";
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