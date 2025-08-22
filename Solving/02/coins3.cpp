#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

int n, x;
vector<int> coins;

void solve()
{
    cin >> n >> x;

    for(int i = 0 ; i < n ; ++i)
    {
        int coin; cin >> coin;
        coins.push_back(coin);
    }

    vector<int> dp(x + 1, 0);

    dp[0] = 1;

    for(int c : coins)
    {
        for(int s = 0 ; s < x ; ++s)
        {
            if(s + c <= x)
            {
                dp[s + c] = (dp[s] + dp[s + c]) % MOD;
            }
        }
    }

    cout << dp[x] << "\n";
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