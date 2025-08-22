#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 1e3 + 5;

int n;
char grid[MAXN][MAXN];
int dp[MAXN][MAXN];

void solve()
{
    cin >> n;

    for(int i = 0 ; i < n ; ++i)
    {
        for(int j = 0 ; j < n ; ++j)
        {
            cin >> grid[i][j];
        }
    }

    if(grid[0][0] == '*')
    {
        cout << "0" << "\n";
        exit(0);
    }

    dp[0][0] = 1;

    for(int i = 0 ; i < n ; ++i)
    {
        for(int j = 0 ; j < n ; ++j)
        {
            if(grid[i][j] == '*') continue;

            if(grid[i][j - 1] == '.' && j - 1 >= 0)
            {
                dp[i][j] = (dp[i][j] + dp[i][j - 1]) % MOD;
            }

            if(grid[i - 1][j] == '.' && i - 1 >= 0)
            {
                dp[i][j] = (dp[i][j] + dp[i - 1][j]) % MOD;
            }
        }
    }

    cout << dp[n - 1][n - 1] << "\n";
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