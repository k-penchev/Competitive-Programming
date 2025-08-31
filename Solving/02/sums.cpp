#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3005;

int n;
long long dp[MAXN];

void solve()
{
    cin >> n;

    dp[0] = 1;

    for(int c = 1 ; c <= n ; c *= 2)
    {
        for(int num = c ; num <= n ; ++num)
        {
            dp[num] += dp[num - c];
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