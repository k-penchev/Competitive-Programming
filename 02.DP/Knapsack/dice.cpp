#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 10;
const int MOD = 1e9 + 7;

int n;
int dp[MAXN];

void solve()
{
    cin >> n;

    dp[0] = 1;

    for(int s = 0 ; s < n ; ++s)
    {
        for(int dice = 1 ; dice <= 6 ; ++dice)
        {
            if(s + dice <= n)
            {
                dp[s + dice] = (dp[s + dice] + dp[s]) % MOD;
            }
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