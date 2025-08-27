#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;
const int MAXM = 1e2 + 10;
const int MOD = 1e9 + 7;

int n, m;
int arr[MAXN];
int dp[MAXN][MAXM];
int answer = 0;

bool check(int x)
{
    return (1 <= x && x <= m);
}

void solve()
{
    cin >> n >> m;

    for(int i = 0 ; i < n ; ++i)
    {
        cin >> arr[i];
    }

    if(arr[0] == 0)
    {
        for(int i = 1 ; i <= m ; ++i)
        {
            dp[0][i] = 1;
        }
    }
    else
    {
        dp[0][arr[0]] = 1;
    }
    

    for(int i = 0 ; i <= n - 2 ; ++i)
    {
       for(int j = 1 ; j <= m ; ++j)
       {
            if(arr[i] == 0)
            {
                if(check(j - 1))
                    dp[i + 1][j - 1] = (dp[i][j] + dp[i + 1][j - 1]) % MOD;
                
                if(check(j - 1))
                    dp[i + 1][j + 0] = (dp[i][j] + dp[i + 1][j]) % MOD;
                
                if(check(j - 1))
                    dp[i + 1][j + 1] = (dp[i][j] + dp[i + 1][j + 1]) % MOD;
            }
       }
    }

    for(int i = 1 ; i <= m ; ++i)
    {
        answer += dp[n - 1][i];
    }

    cout << answer << "\n";
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