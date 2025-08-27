#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;
const int MAXA = 3 + 1;

int n;
long long a[MAXN], b[MAXN], c[MAXN];
long long dp[MAXN][MAXA];

void solve()
{
    cin >> n;

    for(int i = 1 ; i <= n ; ++i)
    {
        cin >> a[i] >> b[i] >> c[i];
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        dp[i][1] = dp[i][2] = dp[i][3] = INT_MIN;
    }

    dp[1][1] = a[1];
    dp[1][2] = b[1];
    dp[1][3] = c[1];

    for(int i = 2 ; i <= n ; ++i)
    {
        dp[i][1] = max(dp[i - 1][2], dp[i - 1][3]) + a[i];
        dp[i][2] = max(dp[i - 1][1], dp[i - 1][3]) + b[i];
        dp[i][3] = max(dp[i - 1][1], dp[i - 1][2]) + c[i];
    }

    cout << max({dp[n][1], dp[n][2], dp[n][3]}) << "\n";
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