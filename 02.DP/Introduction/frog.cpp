#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;
const long long INF = 1e18;

int n;
long long h[MAXN];
long long dp[MAXN];

void solve()
{
    cin >> n;

    for(int i = 1 ; i <= n ; ++i)
    {
        cin >> h[i];
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        dp[i] = INF;
    }

    dp[1] = 0;

    for(int i = 2 ; i <= n ; ++i)
    {
        if(i - 1 >= 1)
        {
            dp[i] = min(dp[i], dp[i - 1] + abs(h[i] - h[i - 1]));
        }

        if(i - 2 >= 1)
        {
            dp[i] = min(dp[i], dp[i - 2] + abs(h[i] - h[i - 2]));
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