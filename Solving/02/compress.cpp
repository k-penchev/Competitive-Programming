#include <bits/stdc++.h>

using namespace std;

const int MAXN = 51;

int n, a;
long long dp[MAXN];

void solve()
{
    cin >> n >> a;

    dp[0] = 1;

    for(int i = 1 ; i <= n ; ++i)
    {
        for(int j = 1 ; j <= min(i, a) ; ++j)
        {
            dp[i] += dp[i - j];
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