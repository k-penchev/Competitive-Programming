#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;
const long long INF = 1e18;

int n, k;
long long h[MAXN];
long long dp[MAXN];

void solve()
{
    cin >> n >> k;

    for(int i = 1 ; i <= n ; ++i)
    {
        cin >> h[i];
    }

    for(int i = 1 ; i <= n ; ++i)
    {
        dp[i] = INF;
    }

    dp[1] = 0;

    for(int i = 1 ; i <= n ; ++i)
    {
        int last = min(i + k, n);

        for(int j = i + 1 ; j <= last ; ++j)
        {
            dp[j] = min(dp[j], dp[i] + abs(h[i] - h[j]));
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